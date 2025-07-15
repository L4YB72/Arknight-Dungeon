#pragma once
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Player.h"

extern Atlas Amiya_right_move; // Aimiya���ƶ���
extern Atlas Amiya_left_move; // Aimiya���ƶ���
extern Atlas Amiya_right_idle; // Aimiya�Ҵ�������
extern Atlas Amiya_left_idle; // Aimiya���������
extern Atlas Amiya_right_attack; // Aimiya�ҹ�������
extern Atlas Amiya_left_attack;  // Aimiya�󹥻�����


class Map; // ǰ������Map��


class Amiya : public Player {
private:

public:
	Amiya() {
		animation_move_right.set_atlas(&Amiya_right_move); // 
		animation_move_left.set_atlas(&Amiya_left_move); // �������ƶ���
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

		animation_idle_right.set_atlas(&Amiya_right_idle); // �����Ҵ�������
		animation_idle_left.set_atlas(&Amiya_left_idle); // �������������

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


		animation_move_right.set_interval(75);// �������ƶ������
		animation_move_left.set_interval(75); // �������ƶ������
		animation_idle_right.set_interval(75); // �����Ҵ����������
		animation_idle_left.set_interval(75); // ����������������

		size.x = 0.0f; // ������ҿ��
		size.y = 0.0f; // ������Ҹ߶�
	} 
	~Amiya() = default; // Ĭ����������

	void on_update(int delta,Map* map) { // �������״̬
		Player::on_update(delta,map); // ���û�����·���
		outtextxy(30, 30, _T("Amiya is loading..."));
	}
	void on_render(const Camera& camera) { // ��Ⱦ���
		Player::on_render(camera); // ���û�����Ⱦ����
	}

};