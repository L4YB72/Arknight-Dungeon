#pragma once
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Player.h"

extern Atlas Amiya_right_move; // Aimiya右移动画
extern Atlas Amiya_left_move; // Aimiya左移动画
extern Atlas Amiya_right_idle; // Aimiya右待机动画
extern Atlas Amiya_left_idle; // Aimiya左待机动画
extern Atlas Amiya_right_attack; // Aimiya右攻击动画
extern Atlas Amiya_left_attack;  // Aimiya左攻击动画


class Map; // 前向声明Map类


class Amiya : public Player {
private:

public:
	Amiya() {
		animation_move_right.set_atlas(&Amiya_right_move); // 
		animation_move_left.set_atlas(&Amiya_left_move); // 设置左移动画
		animation_move_right.set_loop(false);
		animation_move_left.set_loop(false);
		animation_move_right.set_on_finished_callback([this]() {
			current_animation = &animation_idle_right;
			animation_move_right.reset();
		});
		animation_move_left.set_on_finished_callback([this]() {
			current_animation = &animation_idle_left;
			animation_move_left.reset();
		});

		animation_idle_right.set_atlas(&Amiya_right_idle); // 设置右待机动画
		animation_idle_left.set_atlas(&Amiya_left_idle); // 设置左待机动画

		animation_attack_right.set_atlas(&Amiya_right_attack);
		animation_attack_left.set_atlas(&Amiya_left_attack);
		animation_attack_right.set_loop(false);
		animation_attack_left.set_loop(false);
		animation_attack_right.set_on_finished_callback([this]() {
			current_animation = &animation_idle_right;
			animation_attack_right.reset();
			});
		animation_attack_left.set_on_finished_callback([this]() {
			current_animation = &animation_idle_left;
			animation_attack_left.reset();
			});


		animation_move_right.set_interval(75);// 设置右移动画间隔
		animation_move_left.set_interval(75); // 设置左移动画间隔
		animation_idle_right.set_interval(75); // 设置右待机动画间隔
		animation_idle_left.set_interval(75); // 设置左待机动画间隔

		size.x = 0.0f; // 设置玩家宽度
		size.y = 0.0f; // 设置玩家高度
	} 
	~Amiya() = default; // 默认析构函数

	void on_update(int delta,Map* map) { // 更新玩家状态
		Player::on_update(delta,map); // 调用基类更新方法
		outtextxy(30, 30, _T("Amiya is loading..."));
	}
	void on_render(const Camera& camera) { // 渲染玩家
		Player::on_render(camera); // 调用基类渲染方法
	}

};