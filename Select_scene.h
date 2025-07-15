#pragma once
#include <graphics.h>
#include "Scene.h"
#include "Scene_manager.h"
#include "Platform.h"
#include "immmma.h"
#include "tool.h"
#include "Amiya.h"
#include "Hei.h"
#include "string"
extern Scene_manager scene_manager;
extern Player* player_1; //��Ҷ���
extern Player* player_2; //��Ҷ���


class SelectScene : public Scene {
private:
	enum class PlayerType {
		Amiya = 0,
		Hei,
		Invalid
	};

	PlayerType player_type_1 = PlayerType::Amiya; //Ĭ�����ΪAmiya

	bool is_player1_left_down = false; //����Ƿ������
	bool is_player1_right_down = false; //����Ƿ����Ҽ�

public:
	SelectScene() = default; //Ĭ�Ϲ��캯��
	~SelectScene() = default; //Ĭ����������
	void on_load() { //���س���

	}
	void on_update(int delta) { //���³���

	}
	void on_render(const Camera& camera) { //��Ⱦ����
		std::cout << "Rendering Select Scene..." << std::endl;
		outtextxy_shaded(10, 10, _T("Select Scene is rendering..."));
		switch (player_type_1) {
		default:
			break;
		}
		for (int i = 0; i <= 1280; i+=50) {
			for(int j=0;j<= 720; j+=50) {
				outtextxy(i, j, _T("a")); //��Ⱦ�ո�
			}
		}
	}
	void on_unload() { //ж�س���
		switch (player_type_1) {
		case(PlayerType::Amiya):
			player_1 = new Amiya(); //����Amiya��Ҷ���;
			break;
		case(PlayerType::Hei):
			player_1 = new Hei(); //����Hei��Ҷ���;
			break;  
		}
		player_1->set_id(Player::PlayerId::P1); //�������ID
		player_2 = new Amiya(); //�����ڶ�����Ҷ���
		player_2->set_id(Player::PlayerId::P2); //���õڶ������ID

	}

	void on_event(const ExMessage& msg) { //�����¼�
		switch (msg.message) {
		case(WM_KEYDOWN):
			switch (msg.vkcode) {
			case(WM_KEYDOWN):
				switch (msg.vkcode)
			case('A'):
				is_player1_left_down = true; //��Ұ������
				break;
			case('D'):
				is_player1_right_down = true; //��Ұ����Ҽ�
				break;
			case(VK_SPACE):
				std::cout << "Switching to Game Scene..." << std::endl;
				scene_manager.switch_to(Scene_manager::SceneType::Game); //���¿ո���л����˵�����
				break;
			default:
				break;
			}
			break;

		case(WM_KEYUP):
			switch (msg.vkcode) {
			case('A'):
				is_player1_left_down = false; //����ɿ����
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)(player_type_1)-1) % (int)PlayerType::Invalid);
				break;
			case('D'):
				is_player1_right_down = false; //����ɿ��Ҽ�
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)(player_type_1)+1) % (int)PlayerType::Invalid);
				break;
			default:
				break;
			}
			break;
		}
	}

};