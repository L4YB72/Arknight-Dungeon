#include "Player.h"
#include "Map.h"
#include "Common_Amiya.h"

Player::Player() {
    current_animation = &animation_idle_right;
}

Player::~Player() = default;

void Player::on_load() {
 
    target_position = position = Vector2(0, 0);
    target_block = current_block = Vector2(0, 0);
}

void Player::on_update(int delta,Map* current_map) {
    if(!have_attacked){
        
        int object = 0;

       
        if (current_map->get_object(real_target_block.x, real_target_block.y) != 1)
        {
        }
        else
        {
			target_block = current_block; //如果目标格子是墙，则不移动
        }
       
        target_position = block_to_pixel(target_block, target_position);

        real_tagert_position = delta_position + target_position;
    }
    else{
		target_block = current_block; //如果攻击，则不移动
   
    }
   
    
    if(!have_attacked)
    {
        move_to_block(delta);
    }
        //current_animation = is_facing_right ? &animation_attack_left :&animation_attack_right;
    real_target_block = pixel_to_block(real_tagert_position, real_target_block);
	
    current_animation->on_update(delta);
    have_attacked = false;
}

void Player::on_render(const Camera& camera) {
    current_animation->on_draw((int)position.x, (int)position.y, camera);
    if (is_debug) {
        line(0, 0, real_position.x - camera.get_poisition().x, real_position.y - camera.get_poisition().y);
        char hhp = '0' + Hp;
		outtextxy(40,40, hhp);
        outtextxy(real_tagert_position.x-camera.get_poisition().x, real_tagert_position.y-camera.get_poisition().y, _T("nihao"));
        TCHAR money_str[4];
        _stprintf_s(money_str, _countof(money_str), _T("%d"), money);
        outtextxy(50, 50, money_str);
    }
}

void Player::on_ui_render() {
	setbkmode(TRANSPARENT); // 设置背景透明
    // 血量
    TCHAR hp_str[16];
    _stprintf_s(hp_str, _countof(hp_str), _T("HP: %d"), Hp);
    outtextxy(10, 20, hp_str);

    // 武器
    TCHAR weapon_str[32];
    if (arm) {
        // 假设 arm_type 枚举有 ToString 方法或你可以自己实现
        _stprintf_s(weapon_str, _countof(weapon_str), _T("Weapon: %s"), Arm::ToString(arm->type));
    }
    else {
        _tcscpy_s(weapon_str, _T("Weapon: None"));
    }
    outtextxy(10, 40, weapon_str);

    // 金币
    TCHAR money_str[16];
    _stprintf_s(money_str, _countof(money_str), _T("Coins: %d"), money);
    outtextxy(10, 60, money_str);
}

void Player::on_unload() {}

void Player::on_event(const ExMessage& msg) {
    int object = 0;
    if (have_attacked == true) {
        have_attacked = false;
        can_move = false;
        return;
    }
    switch (msg.message)
    {
    case(WM_KEYDOWN):
        switch (msg.vkcode) {
        case('A'):
			target_block = current_block + Vector2(-1, 0);
            is_facing_right = 1;
            break;
        case('D'):
			target_block = current_block + Vector2(1, 0);
            is_facing_right = 0;
            break;
        case('W'):
			target_block = current_block + Vector2(0, -1);
            break;
        case('S'):
			target_block = current_block + Vector2(0, 1);
            break;
        case('F'):
			skill->on_effect(this);
			break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    target_position = block_to_pixel(target_block, target_position);
    real_tagert_position = delta_position + target_position;
    real_target_block = pixel_to_block(real_tagert_position, real_target_block);
}

void Player::set_id(PlayerId id) {
    this->player_id = id;
}

void Player::on_move(float distance) {
    position.x += distance;
}

const Vector2& Player::get_position() const {
    return position;
}

Vector2 Player::get_real_position() const {
    return real_block;
}

Vector2 Player::get_real_block() const {
    return real_block; 
}

void Player::set_real_target_block(Vector2 vec) {
    real_target_block = vec;
}
void Player::set_target_block(Vector2 vec) {
    target_block = vec;
}

//void Player::move_and_collide(int delta) {
//    velocity.y += gravity * (float)delta;
//    position += velocity * (float)delta;
//
//    if (velocity.y > 0) {
//        for (const Platform& platform : platform_list) {
//            const Platform::CollisionShape& shape = platform.collision_shape;
//            bool is_colliding = (position.x + size.x > shape.left && position.x < shape.right &&
//                position.y + size.y > shape.y && position.y < shape.y + 10);
//            if (is_colliding) {
//                float delta_position_y = velocity.y * delta;
//                float last_tick_y = position.y + size.y - delta_position_y;
//                if (last_tick_y <= shape.y) {
//                    position.y = shape.y - size.y;
//                    velocity.y = 0;
//                    break;
//                }
//                else {
//                    position.y -= delta_position_y;
//                }
//            }
//        }
//    }
//}

void Player::on_jump() {
    if (velocity.y == 0)
        velocity.y += jump_speed;
}
 

void Player::position_format(Vector2& poisition) {
    position.x = position.x / block_pixel * block_pixel - 0.5 * size.x;
    position.y = position.y / block_pixel * block_pixel - 0.5 * size.y;
}

void Player::move_to_block(int delta) {
    if ((position - target_position).length() >= 20) {
        current_animation =is_facing_right ? &animation_move_left : &animation_move_right;
        Vector2 dirition = (target_position - position).normalized();
        position += dirition * block_velocity * delta;
    }
    else {
        position = target_position;
        current_block = target_block;
    }

    real_position = delta_position + position;
    pixel_to_block(real_position,real_block);
}

Vector2 Player::get_room() const {
    return Vector2((int)(real_block.x/8),(int)(real_block.y/8));
}
void Player::player_money_add(int delta) {
    money += delta;
}

void Player::attach_range_cal() {
    attach_range.clear();
    attach_range.push_back(Vector2(0, 0));
    
    
    if (arm != nullptr) {
        arm->get_range(real_target_block - real_block);
        Vector2 dir = target_block - current_block;
        for (auto& block : arm->get_range(dir)) {
            attach_range.push_back(block);
		std::cout << block.x << block.y << "attckrangeggg" << std::endl;
        }
    }
    
    for (auto& block : attach_range) {
        std::cout << "Attack range: " << block.x << "," << block.y << std::endl;
    }
}

void Player::set_arm(Arm* new_arm) {
	arm = new_arm;
}

void Player::set_skill(Skill* new_skill) {
    skill = new_skill;
}

int Player::arm_attack_power() {
    return arm->damage;
}

void Player::down_stair() {
    if (Hp <= max_hp/2)
        Hp = max_hp/2;
}


void Player::add_attack_power(int value) {
    attack_power += value;
    
}

void Player::subtract_attack_power(int value) {
    attack_power -= value;
}

int Player::get_attack_power() const {
    return attack_power;
}

void Player::add_defence(int value) {
    defence += value;

}

void Player::sub_subtract_defence(int value){
    defence -= value;
}