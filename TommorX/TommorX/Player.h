#pragma once
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Platform.h"
#include "immmma.h"
#include "Timer.h"
#include "Camera.h"
#include <iostream>

extern std::vector<Platform> platform_list;
extern int background_pixel;
extern int block_pixel;
extern Camera main_camera;
extern bool is_debug; //�Ƿ���debugģʽ


class Player {
public:
	Player() {
		current_animation = &animation_idle_right; // ��ʼ����ǰ����Ϊ�Ҳ��������
	}
	~Player() = default; // Ĭ����������
	virtual void on_load() { // ���������Դ
		move_timer.set_wait_time(300);
		move_timer.set_callback([this]() {
			can_move = true; // ������Ҳ���
			});
		target_position = position = Vector2(0,0); // ��ʼ�����λ��Ϊ��Ļ����
		target_block = current_block = Vector2(0,0); // ��ʼ��Ŀ����Ӻ͵�ǰ����
	
	}
	/*
	//virtual void on_update(int delta) {// �������״̬
	//	int direction = is_right_key_down - is_left_key_down; // ���㷽��
	//	if (direction != 0) {
	//		is_facing_right = direction > 0; // ���ݷ��������Ƿ������Ҳ� 
	//		current_animation = &(is_facing_right ? animation_move_right : animation_move_left); // ���õ�ǰ����
	//		float distance = direction* speed * delta ; // �����ƶ�����
	//		on_move(distance); // �ƶ����
	//	}
	//	else {
	//		current_animation = &(is_facing_right ? animation_idle_right : animation_idle_left); // ���û�а��������ô�������
	//	}
	//	current_animation->on_update(delta); // ���µ�ǰ����
	//	move_and_collide(delta);// �ƶ���� 
	//}
	*/

	virtual void on_update(int delta) {// �������״̬
		move_timer.on_update(delta); // ���¶�ʱ��
		if (can_move) {
			if (is_up_key_down) {
				target_block = current_block + Vector2(0, -1); // �ϼ����£������ƶ�һ������
				move_timer.restart(); // ���ö�ʱ��
				can_move = false; // ��Ҳ��ɲ���
			}
			if (is_down_key_down){
				target_block = current_block + Vector2(0, 1); // �¼����£������ƶ�һ������
				move_timer.restart(); // ���ö�ʱ��
				can_move = false; // ��Ҳ��ɲ���
			}
			if (is_left_key_down) {
				target_block = current_block + Vector2(-1, 0); // ������£������ƶ�һ������
				move_timer.restart(); // ���ö�ʱ��
				can_move = false; // ��Ҳ��ɲ���
			}
			if (is_right_key_down) {
				target_block = current_block + Vector2(1, 0);// �Ҽ����£������ƶ�һ������
				move_timer.restart(); // ���ö�ʱ��
				can_move = false; // ��Ҳ��ɲ���
			}
			target_position = block_to_pixel(target_block, target_position); // ����ת����λ��

		}
		move_to_block(delta); // �ƶ���Ŀ�����
		current_animation->on_update(delta);
	
	}
	
	virtual void on_render(const Camera& camera) {// ��Ⱦ���
		//std::cout << position.x << position.y << std::endl;
		//std::cout << target_position.x << target_position.y << std::endl;
		std::cout << real_position.x<< real_position.y  << std::endl;
		std::cout << real_block.x<<real_block.y<< std::endl;
		current_animation->on_draw( (int)position.x, (int)position.y, camera); // ��Ⱦ��ǰ����
		if (is_debug) {
			line(0, 0, real_position.x-camera.get_poisition().x,real_position.y-camera.get_poisition().y);
		}
	}
	virtual void on_unload() {} // ж�������Դ
	virtual void on_event(const ExMessage& msg) {// �����¼�
		switch (msg.message)
		{
		case(WM_KEYDOWN):
			switch (msg.vkcode) {
			case('A'):
				is_left_key_down = true; // �������
				break;
			case('D'):
				is_right_key_down = true; // �Ҽ�����
				break;
			case('W'):
				is_up_key_down = true; // �ϼ�����
				break;
			case('S'):
				is_down_key_down = true; // �¼�����
			case('P'):

			default:
				break;
			}
			break;
		case(WM_KEYUP):
			switch (msg.vkcode) {
			case('A'):
				is_left_key_down = false; // �������
				break;
			case('D'):
				is_right_key_down = false; // �Ҽ�����
				break;
			case('W'):
				is_up_key_down = false; // �ϼ�����
				break;
			case('S'):
				is_down_key_down = false; // �¼�����
				break;
			default:
				break;
			}
		default:
			break;
		}
	} 

	enum class PlayerId {
		P1,
		P2
	};

	void set_id(PlayerId id) {
		this->player_id = id; // �������ID
	}

	void on_move(float distance) {
		position.x += distance; // �������λ��
	}

	const Vector2& get_position() const {
		return position; // ��ȡ���λ��
	}

protected:
	Vector2 position; // ���λ��
	Animation animation_idle_right; // �Ҳ��������
	Animation animation_idle_left; // ����������
	Animation animation_move_right; // �Ҳ��ƶ�����
	Animation animation_move_left; // ����ƶ�����
	Animation* current_animation = nullptr; // ��ǰ����ָ��
	PlayerId player_id = PlayerId::P1; // ���ID
	bool is_right_key_down = false; // �Ҽ��Ƿ���
	bool is_left_key_down = false; // ����Ƿ���
	bool is_up_key_down = false; // �ϼ��Ƿ���
	bool is_down_key_down = false; // �¼��Ƿ���
	bool can_move = true; // ����Ƿ�ɲ���
	bool is_facing_right = true; // �Ƿ������Ҳ�
	const float speed = 1.0f; // ����ƶ��ٶ�

	//����ģ��
	const float gravity = 1e-3f; // �������ٶ�
	const float run_speed = 0.5f; // ��Ծ�ٶ�
	const float jump_speed = -0.5f; // ��Ծ�ٶ�
	Vector2 velocity = { 0.0f, 0.0f }; // ����ٶ�
	Vector2 size = { 0.0f, 0.0f }; // ��Ҵ�С
	void move_and_collide(int delta) {
		velocity.y += gravity * (float)delta; // Ӧ������
		position += velocity * (float)delta; // ����λ��

		if (velocity.y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.collision_shape; // ��ȡƽ̨����
				bool is_colliding = (position.x + size.x > shape.left && position.x < shape.right &&
					position.y + size.y > shape.y && position.y < shape.y + 10); // �����ײ
				if (is_colliding) {
					float delta_position_y = velocity.y * delta; // ������ײ����
					float last_tick_y = position.y + size.y - delta_position_y; // ��¼�ϴ�λ��
					if(last_tick_y <=  shape.y) {
						position.y = shape.y - size.y; // ��ײ�����λ��
						velocity.y = 0; // �����ٶ�
						break; // �˳�ѭ��
					} else {
						position.y -= delta_position_y; // û����ײ�������ƶ�
					}
				}
			}
		}
	}
	void on_jump() {
		if (velocity.y == 0)
			velocity.y += jump_speed; // ������Ծ�ٶ�
	}

	//�߸���ģ��
private:
	Vector2 current_block; // ��ǰ����λ��
	Vector2 target_block; // Ŀ�����λ��
	Vector2 target_position; // Ŀ������λ��
	const int block_size = block_pixel; // ���Ӵ�С
	const double block_velocity = 0.5; // �ƶ������ٶ�
	Timer move_timer; // ��ʱ��

protected:

	void position_format(Vector2& poisition) {
		position.x = position.x / block_pixel * block_pixel - 0.5 * size.x; // ����λ�ø�ʽ��
		position.y = position.y / block_pixel * block_pixel  - 0.5 * size.y; // ����λ�ø�ʽ��
	}
	double real_y = 0;
	Vector2 block_to_pixel(Vector2& block,Vector2& pixel) {//0.5 * block_size
		pixel.x = block.x * block_size +  - 0.5 * size.x; // ����ת����
		pixel.y = block.y * block_size +- 0.5 * size.y+real_y; // ����ת����
		return pixel; // ��������λ��
	}

	Vector2 pixel_to_block(Vector2& pixel, Vector2& block) {// ����ת����
		block.x = (pixel.x + 0.5 * size.x) / block_size; // ����ת����
		block.y = (pixel.y + 0.5 * size.y) / block_size; // ����ת����
		return block; // ���ظ���λ��
	}

	void move_to_block(int delta) {
		if ((position - target_position).length() >= 1000) {
			Vector2 dirition = (target_position - position).normalized(); // ���㷽������;
			position += dirition * block_velocity * delta; // �ƶ����λ��

			//main_camera.shake(10,delta);
		}
		else {
			position = target_position;
			current_block = target_block; // ���µ�ǰ����λ��
		}

		real_position = delta_position + position;
		real_block =Vector2( (int)real_position.x / 60,(int)real_position.y/60);
	}

	//��ϷЧ��
	protected:
		Vector2 delta_position=Vector2(184+50,180+223-50)*0.6;
		Vector2 real_position = delta_position + position;
		Vector2 real_block = Vector2(0, 0);

/*
line(0,0, position.x+180 - main_camera.get_poisition().x,
					  position.y+180 +223- main_camera.get_poisition().y);
*/


};