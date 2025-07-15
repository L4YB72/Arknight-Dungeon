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
	animation_idle_right.set_atlas(&B1_idle_right); // �����Ҳ��������
	animation_idle_left.set_atlas(&B1_idle_left); // ��������������
	animation_move_right.set_atlas(&B1_move_right); // �����Ҳ��ƶ�����
	animation_move_left.set_atlas(&B1_move_left); // ��������ƶ�����

	animation_idle_right.set_interval(75); // �����Ҳ�����������
	animation_idle_left.set_interval(75); // �����������������
	animation_move_right.set_interval(75); // �����Ҳ��ƶ��������
	animation_move_left.set_interval(75); // ��������ƶ��������
	current_animation = &animation_idle_right; // ��ʼ����ǰ����Ϊ�Ҳ��������
	
	Hp = 10+1*level;

	attack_power = 1+0.5*level ; // ���ù�����
}

B1::~B1() = default; // Ĭ����������


void B1::on_update(int delta) { // ����״̬
	Enemy::on_update(delta); // ���û�����·���
	outtextxy(30, 30, _T("B1 is loading..."));
}
void B1::on_render(const Camera& camera) { // ��Ⱦ���
	Enemy::on_render(camera); // ���û�����Ⱦ����
}


void  B1::attact() {  
    
      
}


void B1::move(Map* & map) {
    if (map->move_map.size() != MAP_WIDTH || map->move_map[0].size() != MAP_HIGHT)
        return; // move_map δ��ʼ����ֱ�ӷ���
    target_block = current_block;

    for (int i = 0; i < 2; i++) {
        Vector2 bbblock = current_block + move_direction[i];
        target_block = map->move_map[(int)bbblock.x][(int)bbblock.y] > map->move_map[(int)target_block.x][(int)target_block.y] ? target_block : bbblock;
    }
    target_position = block_to_pixel(target_block, target_position);
}