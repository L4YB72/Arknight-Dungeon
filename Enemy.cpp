#include "Enemy.h"

extern bool is_debug; // �Ƿ���debugģʽ

//ս��
bool have_attacked = false;
bool can_attack = true;

Enemy::Enemy(int level) {
	current_animation = &animation_idle_right;
	can_move = true;
}// Ĭ�Ϲ��캯��
	
Enemy::~Enemy() = default;// Ĭ����������

	void Enemy:: on_load(int x,int y) { 
		target_block = current_block = Vector2(x,y);
		target_position = current_position = block_to_pixel(current_block, target_position); // ������λ��ת��Ϊ����λ��
	} // ���ص�����Դ


void Enemy:: on_update(int delta) {
	current_animation->on_update(delta);
	//current_position = block_to_pixel(current_block, current_position); // ��������λ��
	if (Hp <= 0 && on_dead_callback) {
		on_dead_callback(); // �������ֵС�ڵ���0�����������ص�����
		on_dead_callback = nullptr; // ��ջص�����
	}
	if (!have_attacked&&!ready_to_attack) {// ||�ĳ���&&
		move_to_block(delta);
	}
	else
		target_block = current_block;
	//std::cout << "attcked?" << have_attacked << std::endl;
}

	// ���µ���״̬



	void Enemy::on_render(const Camera& camera) {
		current_animation->on_draw((int)current_position.x, (int)current_position.y, camera); // ��Ⱦ��ǰ����
		



		if (is_debug) {
			char hhp = '0' + Hp;
			//outtextxy(target_position.x - camera.get_poisition().x, target_position.y - camera.get_poisition().y, _T("TTP"));
			outtextxy(current_position.x - camera.get_poisition().x, current_position.y-camera.get_poisition().y, hhp);
		}
	}
	// ��Ⱦ����



 void Enemy::on_unload() {} // ж�ص�����Դ


 void Enemy::on_event(const ExMessage& msg) {}; // �����¼�




 void Enemy::set_on_dead_callback(std::function<void()> callback) {
	 on_dead_callback = callback;
}


 void Enemy::move_to_block(int delta) {
	 if ((target_position- current_position).length() >= 10) {
		 Vector2 dirition = (target_position- current_position).normalized();
		 current_position += dirition * block_velocity * delta;
	 }
	 else {
		 current_position = target_position;
		 current_block = target_block;
	 }
 }
