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


class Amiya : public Player {
private:

public:
	Amiya() {
		animation_move_right.set_atlas(&Amiya_right_move); // �������ƶ���
		animation_move_left.set_atlas(&Amiya_left_move); // �������ƶ���
		animation_idle_right.set_atlas(&Amiya_right_move); // �����Ҵ�������
		animation_idle_left.set_atlas(&Amiya_left_move); // �������������

		animation_move_right.set_interval(75);// �������ƶ������
		animation_move_left.set_interval(75); // �������ƶ������
		animation_idle_right.set_interval(75); // �����Ҵ����������
		animation_idle_left.set_interval(75); // ����������������

		size.x = 0.0f; // ������ҿ��
		size.y = 0.0f; // ������Ҹ߶�
	} 
	~Amiya() = default; // Ĭ����������

	void on_update(int delta) { // �������״̬
		Player::on_update(delta); // ���û�����·���
		outtextxy(30, 30, _T("Amiya is loading..."));
	}
	void on_render(const Camera& camera) { // ��Ⱦ���
		Player::on_render(camera); // ���û�����Ⱦ����
	}

};