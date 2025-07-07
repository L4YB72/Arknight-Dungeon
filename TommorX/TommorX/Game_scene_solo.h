#pragma once
#include <graphics.h>
#include "Scene.h"
#include "Scene_manager.h"
#include "Platform.h"
#include "immmma.h"
#include <iostream>

extern Scene_manager scene_manager;
extern bool is_debug; // �Ƿ���debugģʽ
extern Player* player_1; //���1����
extern Player* player_2; //���2����

class GameSceneSolo : public Scene {
	//private
public:
	GameSceneSolo() = default; //Ĭ�Ϲ��캯��
	~GameSceneSolo() = default; //Ĭ����������
	void on_load() { //���س���
		
	}
	void on_update(int delta) { //���³���
		std::cout << "Solo scene update" << std::endl;
		player_1->on_update(delta); //�������1
		std::cout << "Updating Player 1..." << std::endl;
		player_2->on_update(delta); //�������2
	}
	void on_render(const Camera& camera) { //��Ⱦ����
		//putimage_alpha(camera, 0, 0, img); //��Ⱦ����ͼƬ
		if (is_debug) {
			settextcolor(RED);
			outtextxy(200, 200, _T("Deguging"));
		}
		outtextxy(10, 10, _T("Solo Scene is rendering"));
		player_1->on_render(camera);//��Ⱦ���1
		player_2->on_render(camera);//��Ⱦ���2
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