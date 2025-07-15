#include "B1.h"
#include "immmma.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Enemy.h"

extern Atlas B1_idle_right;
extern Atlas B1_idle_left;
extern Atlas B1_move_right;
extern Atlas B1_move_left;
extern Atlas B1_Attack;

B1::B1(int level) {
	animation_idle_right.set_atlas(&B1_idle_right); // 设置右侧待机动画
	animation_idle_left.set_atlas(&B1_idle_left); // 设置左侧待机动画
	animation_move_right.set_atlas(&B1_move_right); // 设置右侧移动动画
	animation_move_left.set_atlas(&B1_move_left); // 设置左侧移动动画

	animation_idle_right.set_interval(75); // 设置右侧待机动画间隔
	animation_idle_left.set_interval(75); // 设置左侧待机动画间隔
	animation_move_right.set_interval(75); // 设置右侧移动动画间隔
	animation_move_left.set_interval(75); // 设置左侧移动动画间隔
	current_animation = &animation_idle_right; // 初始化当前动画为右侧待机动画
	
	Hp = 10+1*level;

	attack_power = 1+0.5*level ; // 设置攻击力
}

B1::~B1() = default; // 默认析构函数


void B1::on_update(int delta) { // 更新状态
	Enemy::on_update(delta); // 调用基类更新方法
	outtextxy(30, 30, _T("B1 is loading..."));
}
void B1::on_render(const Camera& camera) { // 渲染玩家
	Enemy::on_render(camera); // 调用基类渲染方法
}


void  B1::attact() {  
    
      
}


void B1::move(Map* & map) {
    if (map->move_map.size() != MAP_WIDTH || map->move_map[0].size() != MAP_HIGHT)
        return; // move_map 未初始化，直接返回
    target_block = current_block;

    for (int i = 0; i < 2; i++) {
        Vector2 bbblock = current_block + move_direction[i];
        target_block = map->move_map[(int)bbblock.x][(int)bbblock.y] > map->move_map[(int)target_block.x][(int)target_block.y] ? target_block : bbblock;
    }
    target_position = block_to_pixel(target_block, target_position);
}