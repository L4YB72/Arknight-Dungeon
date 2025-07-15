#pragma once
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Player.h"

extern Atlas Hei_right_move;// Aimiya右移动画
extern Atlas Hei_left_move;// Aimiya左移动画
extern Atlas Hei_right_idle;// Aimiya右待机动画
extern Atlas Hei_left_idle;// Aimiya左待机动画

class Map; // 前向声明Map类

class Hei : public Player {
private:
public:
	Hei() = default;
	~Hei() = default;

	void on_update(int delta,Map* map) {
		Player::on_update(delta,map); // 调用基类更新方法
	} // 更新玩家状态
	void on_render(const Camera& camera) { // 渲染玩家
		Player::on_render(camera); // 调用基类渲染方法
	} 

};