#pragma once
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"
#include "Player.h"

extern Atlas Hei_right_move;// Aimiya���ƶ���
extern Atlas Hei_left_move;// Aimiya���ƶ���
extern Atlas Hei_right_idle;// Aimiya�Ҵ�������
extern Atlas Hei_left_idle;// Aimiya���������

class Hei : public Player {
private:
public:
	Hei() = default;
	~Hei() = default;

	void on_update(int delta) {
		Player::on_update(delta); // ���û�����·���
	} // �������״̬
	void on_render(const Camera& camera) { // ��Ⱦ���
		Player::on_render(camera); // ���û�����Ⱦ����
	} 

};