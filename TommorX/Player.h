#pragma once
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Platform.h"
#include "Timer.h"
#include "Camera.h"
#include <iostream>
#include <vector>
#include "Arm.h"
#include "LongKnife.h"
#include "Skill.h"
class Map;

extern std::vector<Platform> platform_list;
extern int background_pixel;
extern int block_pixel;
extern Camera main_camera;
extern bool is_debug;
extern Vector2 player_target_position;

class Player {
public:
    Player();
    virtual ~Player();

    virtual void on_load();
    virtual void on_update(int delta,Map* map);
    virtual void on_render(const Camera& camera);
    void virtual on_ui_render();
    virtual void on_unload();
    virtual void on_event(const ExMessage& msg);


    enum class PlayerId {
        P1,
        P2
    };

    void set_id(PlayerId id);
    void on_move(float distance);
    const Vector2& get_position() const;

    Vector2 get_real_position() const;
    Vector2 get_real_block() const;
    Vector2 get_room() const;
    void set_real_target_block(Vector2 vec);
    void set_target_block(Vector2 vec);
    bool have_attacked = false;

protected:
    Vector2 position;
    Animation animation_idle_right;
    Animation animation_idle_left;
    Animation animation_move_right;
    Animation animation_move_left;
    Animation animation_attack_right;
    Animation animation_attack_left;
    Animation* current_animation = nullptr;

    PlayerId player_id = PlayerId::P1;
    bool is_right_key_down = false;
    bool is_left_key_down = false;
    bool is_up_key_down = false;
    bool is_down_key_down = false;
    bool can_move = true;
    bool is_facing_right = true;
    const float speed = 1.0f;

    //重力模块
    const float gravity = 1e-3f;
    const float run_speed = 0.5f;
    const float jump_speed = -0.5f;
    Vector2 velocity = { 0.0f, 0.0f };
    Vector2 size = { 0.0f, 0.0f };
    void move_and_collide(int delta);
    void on_jump();

    //走格子模块
private:
    Vector2 current_block;
    Vector2 target_block;
    Vector2 target_position;
    const int block_size = block_pixel;
    const double block_velocity = 0.5;
public:
    void down_stair();

protected:
    void position_format(Vector2& poisition);
    double real_y = 0;

    void move_to_block(int delta);

private:
    Vector2 delta_position = Vector2(184 + 50, 180 + 223 - 50) * 0.6;
    Vector2 real_position = delta_position + position;
    Vector2 real_tagert_position = delta_position + target_position;
    Vector2 real_block = pixel_to_block(real_position, real_block);
    Vector2 real_target_block = pixel_to_block(target_position, real_block);


//怪物交互
	friend class DamageManager; // 声明友元类DamageManager
	friend class Skill; // 声明友元类Skill
	int max_hp = 100; //玩家最大血量
    int Hp = 100;//玩家血量
	int attack_power = 0; //玩家攻击力
    float defence = 0;
    std::vector<Vector2> attach_range = { {0,0} };//玩家攻击范围
	Arm* arm = nullptr; //玩家武器
    int arm_attack_power();

public:
	void set_arm(Arm* new_arm);
    void set_skill(Skill* new_skill);
    void attach_range_cal();


//技能
    Skill* skill;
    void add_attack_power(int value);

    void subtract_attack_power(int value);

    int get_attack_power() const;

    void add_defence(int value);

    void sub_subtract_defence(int value);

//其他
private:
    int money = 0;
public:
    void player_money_add(int delta = 1);

};