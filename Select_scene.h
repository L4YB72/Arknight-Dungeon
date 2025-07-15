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
extern Player* player_1; //玩家对象
extern Player* player_2; //玩家对象


class SelectScene : public Scene {
private:
	enum class PlayerType {
		Amiya = 0,
		Hei,
		Invalid
	};

	PlayerType player_type_1 = PlayerType::Amiya; //默认玩家为Amiya

	bool is_player1_left_down = false; //玩家是否按下左键
	bool is_player1_right_down = false; //玩家是否按下右键

public:
	SelectScene() = default; //默认构造函数
	~SelectScene() = default; //默认析构函数
	void on_load() { //加载场景

	}
	void on_update(int delta) { //更新场景

	}
	void on_render(const Camera& camera) { //渲染场景
		std::cout << "Rendering Select Scene..." << std::endl;
		outtextxy_shaded(10, 10, _T("Select Scene is rendering..."));
		switch (player_type_1) {
		default:
			break;
		}
		for (int i = 0; i <= 1280; i+=50) {
			for(int j=0;j<= 720; j+=50) {
				outtextxy(i, j, _T("a")); //渲染空格
			}
		}
	}
	void on_unload() { //卸载场景
		switch (player_type_1) {
		case(PlayerType::Amiya):
			player_1 = new Amiya(); //创建Amiya玩家对象;
			break;
		case(PlayerType::Hei):
			player_1 = new Hei(); //创建Hei玩家对象;
			break;  
		}
		player_1->set_id(Player::PlayerId::P1); //设置玩家ID
		player_2 = new Amiya(); //创建第二个玩家对象
		player_2->set_id(Player::PlayerId::P2); //设置第二个玩家ID

	}

	void on_event(const ExMessage& msg) { //处理事件
		switch (msg.message) {
		case(WM_KEYDOWN):
			switch (msg.vkcode) {
			case(WM_KEYDOWN):
				switch (msg.vkcode)
			case('A'):
				is_player1_left_down = true; //玩家按下左键
				break;
			case('D'):
				is_player1_right_down = true; //玩家按下右键
				break;
			case(VK_SPACE):
				std::cout << "Switching to Game Scene..." << std::endl;
				scene_manager.switch_to(Scene_manager::SceneType::Game); //按下空格键切换到菜单场景
				break;
			default:
				break;
			}
			break;

		case(WM_KEYUP):
			switch (msg.vkcode) {
			case('A'):
				is_player1_left_down = false; //玩家松开左键
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)(player_type_1)-1) % (int)PlayerType::Invalid);
				break;
			case('D'):
				is_player1_right_down = false; //玩家松开右键
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)(player_type_1)+1) % (int)PlayerType::Invalid);
				break;
			default:
				break;
			}
			break;
		}
	}

};