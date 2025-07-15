#include "Enemy.h"

extern bool is_debug; // 是否开启debug模式

//战斗
bool have_attacked = false;
bool can_attack = true;

Enemy::Enemy(int level) {
	current_animation = &animation_idle_right;
	can_move = true;
}// 默认构造函数
	
Enemy::~Enemy() = default;// 默认析构函数

	void Enemy:: on_load(int x,int y) { 
		target_block = current_block = Vector2(x,y);
		target_position = current_position = block_to_pixel(current_block, target_position); // 将格子位置转换为像素位置
	} // 加载敌人资源


void Enemy:: on_update(int delta) {
	current_animation->on_update(delta);
	//current_position = block_to_pixel(current_block, current_position); // 更新像素位置
	if (Hp <= 0 && on_dead_callback) {
		on_dead_callback(); // 如果生命值小于等于0，调用死亡回调函数
		on_dead_callback = nullptr; // 清空回调函数
	}
	if (!have_attacked&&!ready_to_attack) {// ||改成了&&
		move_to_block(delta);
	}
	else
		target_block = current_block;
	//std::cout << "attcked?" << have_attacked << std::endl;
}

	// 更新敌人状态



	void Enemy::on_render(const Camera& camera) {
		current_animation->on_draw((int)current_position.x, (int)current_position.y, camera); // 渲染当前动画
		



		if (is_debug) {
			char hhp = '0' + Hp;
			//outtextxy(target_position.x - camera.get_poisition().x, target_position.y - camera.get_poisition().y, _T("TTP"));
			outtextxy(current_position.x - camera.get_poisition().x, current_position.y-camera.get_poisition().y, hhp);
		}
	}
	// 渲染敌人



 void Enemy::on_unload() {} // 卸载敌人资源


 void Enemy::on_event(const ExMessage& msg) {}; // 处理事件




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
