#include "B2.h"
#include "immmma.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Enemy.h"

extern Atlas B2_idle_right;
extern Atlas B2_idle_left;
extern Atlas B2_move_right;
extern Atlas B2_move_left;
extern Atlas B2_Attack;

extern Atlas B2_right_attack;
extern Atlas B2_left_attack;


B2::B2(int level) {
    animation_idle_right.set_atlas(&B2_idle_right);
    animation_idle_left.set_atlas(&B2_idle_left);

    animation_move_right.set_atlas(&B2_move_right);
    animation_move_left.set_atlas(&B2_move_left);
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


    animation_attack_right.set_atlas(&B2_right_attack);
    animation_attack_left.set_atlas(&B2_left_attack);
    animation_attack_left.set_loop(false);
    animation_attack_right.set_loop(false);

    animation_attack_right.set_on_finished_callback([this]() {
        current_animation = &animation_idle_right;
        animation_attack_right.reset();
        });
    animation_attack_left.set_on_finished_callback([this]() {
        current_animation = &animation_idle_left;
        animation_attack_left.reset();
        });

    B2::delta_position = Vector2(-25,-35);

    animation_idle_right.set_interval(75);
    animation_idle_left.set_interval(75);
    animation_move_right.set_interval(75);
    animation_move_left.set_interval(75);
    animation_attack_right.set_interval(75);
    animation_attack_left.set_interval(75);


    current_animation = &animation_idle_right;
    
    

    Hp = 10 + 1 * level;
    attack_power = 1 + 0.5 * level;
}

B2::~B2() = default;

void B2::on_update(int delta) {
    Enemy::on_update(delta);
    outtextxy(30, 30, _T("B2 is loading..."));
}

void B2::on_render(const Camera& camera) {
    Enemy::on_render(camera);
}

void B2::attact() {
    // 攻击逻辑（待实现）
}

//void B2::Get_P_Block();

//void B2::move(Map*& map) {
//    if (map->move_map.size() != MAP_WIDTH || map->move_map[0].size() != MAP_HIGHT)
//        return; // move_map 未初始化，直接返回
//
//   
//    Vector2 player_pos = player_1->get_real_block(); // 假设 player 有这个方法
//
//    Vector2 current_pos = current_block;
//
//    // 计算朝向玩家的最佳方向
//    Vector2 direction = { 0, 0 };
//    if (player_pos.x > current_pos.x) direction = { 1, 0 };  // 向右
//    else if (player_pos.x < current_pos.x) direction = { -1, 0 }; // 向左
//    else if (player_pos.y > current_pos.y) direction = { 0, 1 };  // 向下
//    else if (player_pos.y < current_pos.y) direction = { 0, -1 }; // 向上
//
//    // 检查目标位置是否可移动（防止越界或撞墙）
//    Vector2 next_block = current_pos + direction;
//    if (next_block.x >= 0 && next_block.x < MAP_WIDTH &&
//        next_block.y >= 0 && next_block.y < MAP_HIGHT) {
//        target_block = next_block;
//        target_position = block_to_pixel(target_block, target_position);
//    }
//
//    // 调试输出
//    std::cout << "B2 moving from (" << current_block.x << ", " << current_block.y
//        << ") to (" << target_block.x << ", " << target_block.y << ")" << std::endl;
//}




void B2::move(Map*& map) {
    if (map->move_map.size() != MAP_WIDTH || map->move_map[0].size() != MAP_HIGHT)
        return; // move_map 未初始化，直接返回
    target_block = current_block;

    for (int i = 0; i < 4; i++) {
        Vector2 bbblock = current_block + move_direction[i];
        target_block = map->move_map[(int)bbblock.x][(int)bbblock.y] > map->move_map[(int)target_block.x][(int)target_block.y] ? target_block : bbblock;
    }
    if (target_block.x - current_block.x > 0)
    {
        is_facing_right = true;
        current_animation = &animation_move_right;
    }
    else if (target_block.x - current_block.x < 0)
    {
        is_facing_right = false;
        current_animation = &animation_move_left;
    }
    target_position = block_to_pixel(target_block, target_position);
}