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
extern bool is_debug; //是否开启debug模式


class Player {
public:
	Player() {
		current_animation = &animation_idle_right; // 初始化当前动画为右侧待机动画
	}
	~Player() = default; // 默认析构函数
	virtual void on_load() { // 加载玩家资源
		move_timer.set_wait_time(300);
		move_timer.set_callback([this]() {
			can_move = true; // 允许玩家操作
			});
		target_position = position = Vector2(0,0); // 初始化玩家位置为屏幕中心
		target_block = current_block = Vector2(0,0); // 初始化目标格子和当前格子
	
	}
	/*
	//virtual void on_update(int delta) {// 更新玩家状态
	//	int direction = is_right_key_down - is_left_key_down; // 计算方向
	//	if (direction != 0) {
	//		is_facing_right = direction > 0; // 根据方向设置是否面向右侧 
	//		current_animation = &(is_facing_right ? animation_move_right : animation_move_left); // 设置当前动画
	//		float distance = direction* speed * delta ; // 计算移动距离
	//		on_move(distance); // 移动玩家
	//	}
	//	else {
	//		current_animation = &(is_facing_right ? animation_idle_right : animation_idle_left); // 如果没有按键，设置待机动画
	//	}
	//	current_animation->on_update(delta); // 更新当前动画
	//	move_and_collide(delta);// 移动玩家 
	//}
	*/

	virtual void on_update(int delta) {// 更新玩家状态
		move_timer.on_update(delta); // 更新定时器
		if (can_move) {
			if (is_up_key_down) {
				target_block = current_block + Vector2(0, -1); // 上键按下，向上移动一个格子
				move_timer.restart(); // 重置定时器
				can_move = false; // 玩家不可操作
			}
			if (is_down_key_down){
				target_block = current_block + Vector2(0, 1); // 下键按下，向下移动一个格子
				move_timer.restart(); // 重置定时器
				can_move = false; // 玩家不可操作
			}
			if (is_left_key_down) {
				target_block = current_block + Vector2(-1, 0); // 左键按下，向左移动一个格子
				move_timer.restart(); // 重置定时器
				can_move = false; // 玩家不可操作
			}
			if (is_right_key_down) {
				target_block = current_block + Vector2(1, 0);// 右键按下，向右移动一个格子
				move_timer.restart(); // 重置定时器
				can_move = false; // 玩家不可操作
			}
			target_position = block_to_pixel(target_block, target_position); // 格子转像素位置

		}
		move_to_block(delta); // 移动到目标格子
		current_animation->on_update(delta);
	
	}
	
	virtual void on_render(const Camera& camera) {// 渲染玩家
		//std::cout << position.x << position.y << std::endl;
		//std::cout << target_position.x << target_position.y << std::endl;
		std::cout << real_position.x<< real_position.y  << std::endl;
		std::cout << real_block.x<<real_block.y<< std::endl;
		current_animation->on_draw( (int)position.x, (int)position.y, camera); // 渲染当前动画
		if (is_debug) {
			line(0, 0, real_position.x-camera.get_poisition().x,real_position.y-camera.get_poisition().y);
		}
	}
	virtual void on_unload() {} // 卸载玩家资源
	virtual void on_event(const ExMessage& msg) {// 处理事件
		switch (msg.message)
		{
		case(WM_KEYDOWN):
			switch (msg.vkcode) {
			case('A'):
				is_left_key_down = true; // 左键按下
				break;
			case('D'):
				is_right_key_down = true; // 右键按下
				break;
			case('W'):
				is_up_key_down = true; // 上键按下
				break;
			case('S'):
				is_down_key_down = true; // 下键按下
			case('P'):

			default:
				break;
			}
			break;
		case(WM_KEYUP):
			switch (msg.vkcode) {
			case('A'):
				is_left_key_down = false; // 左键按下
				break;
			case('D'):
				is_right_key_down = false; // 右键按下
				break;
			case('W'):
				is_up_key_down = false; // 上键按下
				break;
			case('S'):
				is_down_key_down = false; // 下键按下
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
		this->player_id = id; // 设置玩家ID
	}

	void on_move(float distance) {
		position.x += distance; // 设置玩家位置
	}

	const Vector2& get_position() const {
		return position; // 获取玩家位置
	}

protected:
	Vector2 position; // 玩家位置
	Animation animation_idle_right; // 右侧待机动画
	Animation animation_idle_left; // 左侧待机动画
	Animation animation_move_right; // 右侧移动动画
	Animation animation_move_left; // 左侧移动动画
	Animation* current_animation = nullptr; // 当前动画指针
	PlayerId player_id = PlayerId::P1; // 玩家ID
	bool is_right_key_down = false; // 右键是否按下
	bool is_left_key_down = false; // 左键是否按下
	bool is_up_key_down = false; // 上键是否按下
	bool is_down_key_down = false; // 下键是否按下
	bool can_move = true; // 玩家是否可操作
	bool is_facing_right = true; // 是否面向右侧
	const float speed = 1.0f; // 玩家移动速度

	//重力模块
	const float gravity = 1e-3f; // 重力加速度
	const float run_speed = 0.5f; // 跳跃速度
	const float jump_speed = -0.5f; // 跳跃速度
	Vector2 velocity = { 0.0f, 0.0f }; // 玩家速度
	Vector2 size = { 0.0f, 0.0f }; // 玩家大小
	void move_and_collide(int delta) {
		velocity.y += gravity * (float)delta; // 应用重力
		position += velocity * (float)delta; // 更新位置

		if (velocity.y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.collision_shape; // 获取平台矩形
				bool is_colliding = (position.x + size.x > shape.left && position.x < shape.right &&
					position.y + size.y > shape.y && position.y < shape.y + 10); // 检测碰撞
				if (is_colliding) {
					float delta_position_y = velocity.y * delta; // 计算碰撞距离
					float last_tick_y = position.y + size.y - delta_position_y; // 记录上次位置
					if(last_tick_y <=  shape.y) {
						position.y = shape.y - size.y; // 碰撞后调整位置
						velocity.y = 0; // 重置速度
						break; // 退出循环
					} else {
						position.y -= delta_position_y; // 没有碰撞，继续移动
					}
				}
			}
		}
	}
	void on_jump() {
		if (velocity.y == 0)
			velocity.y += jump_speed; // 设置跳跃速度
	}

	//走格子模块
private:
	Vector2 current_block; // 当前格子位置
	Vector2 target_block; // 目标格子位置
	Vector2 target_position; // 目标像素位置
	const int block_size = block_pixel; // 格子大小
	const double block_velocity = 0.5; // 移动格子速度
	Timer move_timer; // 定时器

protected:

	void position_format(Vector2& poisition) {
		position.x = position.x / block_pixel * block_pixel - 0.5 * size.x; // 格子位置格式化
		position.y = position.y / block_pixel * block_pixel  - 0.5 * size.y; // 格子位置格式化
	}
	double real_y = 0;
	Vector2 block_to_pixel(Vector2& block,Vector2& pixel) {//0.5 * block_size
		pixel.x = block.x * block_size +  - 0.5 * size.x; // 格子转像素
		pixel.y = block.y * block_size +- 0.5 * size.y+real_y; // 格子转像素
		return pixel; // 返回像素位置
	}

	Vector2 pixel_to_block(Vector2& pixel, Vector2& block) {// 像素转格子
		block.x = (pixel.x + 0.5 * size.x) / block_size; // 像素转格子
		block.y = (pixel.y + 0.5 * size.y) / block_size; // 像素转格子
		return block; // 返回格子位置
	}

	void move_to_block(int delta) {
		if ((position - target_position).length() >= 1000) {
			Vector2 dirition = (target_position - position).normalized(); // 计算方向向量;
			position += dirition * block_velocity * delta; // 移动玩家位置

			//main_camera.shake(10,delta);
		}
		else {
			position = target_position;
			current_block = target_block; // 更新当前格子位置
		}

		real_position = delta_position + position;
		real_block =Vector2( (int)real_position.x / 60,(int)real_position.y/60);
	}

	//游戏效果
	protected:
		Vector2 delta_position=Vector2(184+50,180+223-50)*0.6;
		Vector2 real_position = delta_position + position;
		Vector2 real_block = Vector2(0, 0);

/*
line(0,0, position.x+180 - main_camera.get_poisition().x,
					  position.y+180 +223- main_camera.get_poisition().y);
*/


};