#pragma once
#include <graphics.h>
#include "Scene.h"
#include "Scene_manager.h"
#include "Platform.h"
#include "immmma.h"
#include <iostream>
#include "Enemy.h"
#include "B1.h"

extern Camera main_camera;
extern Scene_manager scene_manager;
extern bool is_debug; // �Ƿ���debugģʽ
extern Player* player_1; //���1����
extern Player* player_2; //���2����
extern Atlas Amiya_right_idle;

extern Atlas B1_idle_right;

extern Atlas Amiya_right_move;


class GameSceneSolo : public Scene {

private:
	B1* b1;
public:
	GameSceneSolo() = default; //Ĭ�Ϲ��캯��
	~GameSceneSolo() = default; //Ĭ����������
	void on_load() { //���س���
		

	}
	void on_update(int delta) { //���³���
		

	}
	void on_render(const Camera& camera) { //��Ⱦ����
		putimage(10, 10, Amiya_right_idle.get_image(1));
	
	}
	void on_unload() { //ж�س���

	}
	void on_event(const ExMessage& msg) { //�����¼�
		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode) {
			case(VK_SPACE):
				scene_manager.switch_to(Scene_manager::SceneType::Menu); //����ESC���л����˵�����
				break;
			case('Q'):
				is_debug = !is_debug;
				break;
			}
		}
		player_1->on_event(msg); //�������1���¼�
		player_2->on_event(msg); //�������2���¼�
	}

};