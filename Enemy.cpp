#include "Enemy.h"


extern bool is_debug; // �Ƿ���debugģʽ


Enemy::Enemy() {
	current_animation = &animation_idle_right;
}// Ĭ�Ϲ��캯��
	
Enemy::~Enemy() = default;// Ĭ����������

	void Enemy:: on_load() { 
		target_block = current_block = Vector2(3, 3);
	} // ���ص�����Դ


	 void Enemy:: on_update(int delta) {
		 current_animation->on_update(delta);
		 current_position = block_to_pixel(current_block, current_position); // ��������λ��
		 std::cout << current_block.x << "aa" << current_position.y << std::endl; // �������λ��
		 if (Hp <= 0 && on_dead_callback) {
			 on_dead_callback(); // �������ֵС�ڵ���0�����������ص�����
			 on_dead_callback = nullptr; // ��ջص�����
		}
	 }

	// ���µ���״̬



	void Enemy::on_render(const Camera& camera) {
		current_animation->on_draw((int)current_position.x, (int)current_position.y, camera); // ��Ⱦ��ǰ����
		if (is_debug) {
			line(0, 0, current_position.x - camera.get_poisition().x, current_position.y - camera.get_poisition().y);
		}
	}
	// ��Ⱦ����



 void Enemy::on_unload() {} // ж�ص�����Դ


 void Enemy::on_event(const ExMessage& msg) {}; // �����¼�

 //ս��


 void Enemy::set_on_dead_callback(std::function<void()> callback) {
	 on_dead_callback = callback;
}
