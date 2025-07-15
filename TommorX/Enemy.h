#pragma once
#include <iostream>
#include "Camera.h"
#include "graphics.h"
#include "Vector2.h"
#include "Animation.h"
#include "immmma.h"
#include "Map.h"
#include <functional>
#include "DamageManager.h"
#include "Timer.h"

class Enemy {
private:
	
public:
	
	Enemy(int level=0); // 默认构造函数;
	~Enemy(); // 默认析构函数

	virtual void on_load(int x,int y); // 加载敌人资源

	virtual void on_update(int delta);
 // 更新敌人状态

	virtual void on_render(const Camera& camera);
 // 渲染敌人

	virtual void on_unload(); // 卸载敌人资源

	virtual void on_event(const ExMessage& msg); // 处理事件
	virtual void move(Map* &map)=0; // 移动方法
	void move_to_block(int delta);

protected:
	Vector2 current_block; // 敌人位置
	Vector2 current_position; // 敌人像素位置
	Vector2 delta_position;

	Animation animation_idle_right; // 右侧待机动画
	Animation animation_idle_left; // 左侧待机动画
	Animation animation_move_right; // 右侧移动动画
	Animation animation_move_left; // 左侧移动动画
	Animation animation_attack_right;
	Animation animation_attack_left;


	Animation* current_animation = nullptr; // 当前动画指针
	



	//走格子模块
	Vector2 target_block; // 目标格子位置
	Vector2 target_position; // 目标像素位置
	const int block_size = block_pixel; // 格子大小
	const double block_velocity = 0.5; // 移动格子速度
	Timer move_timer;
	bool can_move;
	bool is_facing_right = true;//是否面向右侧
	

	//战斗
friend class DamageManager; // 声明友元类DamageManager
protected:
	bool have_attacked = false; // 是否正在攻击
	bool ready_to_attack = false;
	bool remote_ready_to_attack =false;
	virtual void attact() = 0;// 攻击方法
	int attack_power = 100; // 攻击力
	int Hp = 100;// 生命值
	std::function<void()> on_dead_callback; // 死亡回调函数


	
public:
	void set_on_dead_callback(std::function<void()> callback);

	

};