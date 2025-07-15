#include "Enemy.h"


extern bool is_debug; // 是否开启debug模式


Enemy::Enemy() {
	current_animation = &animation_idle_right;
}// 默认构造函数
	
Enemy::~Enemy() = default;// 默认析构函数

	void Enemy:: on_load() { 
		target_block = current_block = Vector2(3, 3);
	} // 加载敌人资源


	 void Enemy:: on_update(int delta) {
		 current_animation->on_update(delta);
		 current_position = block_to_pixel(current_block, current_position); // 更新像素位置
		 std::cout << current_block.x << "aa" << current_position.y << std::endl; // 输出怪物位置
		 if (Hp <= 0 && on_dead_callback) {
			 on_dead_callback(); // 如果生命值小于等于0，调用死亡回调函数
			 on_dead_callback = nullptr; // 清空回调函数
		}
	 }

	// 更新敌人状态



	void Enemy::on_render(const Camera& camera) {
		current_animation->on_draw((int)current_position.x, (int)current_position.y, camera); // 渲染当前动画
		if (is_debug) {
			line(0, 0, current_position.x - camera.get_poisition().x, current_position.y - camera.get_poisition().y);
		}
	}
	// 渲染敌人



 void Enemy::on_unload() {} // 卸载敌人资源


 void Enemy::on_event(const ExMessage& msg) {}; // 处理事件

 //战斗


 void Enemy::set_on_dead_callback(std::function<void()> callback) {
	 on_dead_callback = callback;
}
