#pragma once
#include <graphics.h>
#include "Scene.h"
#include "Scene_manager.h"
#include "Platform.h"
#include "immmma.h"
#include <iostream>

extern Scene_manager scene_manager;
extern bool is_debug; // 是否开启debug模式
extern Player* player_1; //玩家1对象
extern Player* player_2; //玩家2对象

class GameSceneSolo : public Scene {
	//private
public:
	GameSceneSolo() = default; //默认构造函数
	~GameSceneSolo() = default; //默认析构函数
	void on_load() { //加载场景
		
	}
	void on_update(int delta) { //更新场景
		std::cout << "Solo scene update" << std::endl;
		player_1->on_update(delta); //更新玩家1
		std::cout << "Updating Player 1..." << std::endl;
		player_2->on_update(delta); //更新玩家2
	}
	void on_render(const Camera& camera) { //渲染场景
		//putimage_alpha(camera, 0, 0, img); //渲染背景图片
		if (is_debug) {
			settextcolor(RED);
			outtextxy(200, 200, _T("Deguging"));
		}
		outtextxy(10, 10, _T("Solo Scene is rendering"));
		player_1->on_render(camera);//渲染玩家1
		player_2->on_render(camera);//渲染玩家2
	}
	void on_unload() { //卸载场景

	}
	void on_event(const ExMessage& msg) { //处理事件
		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode) {
			case(VK_SPACE):
				scene_manager.switch_to(Scene_manager::SceneType::Menu); //按下ESC键切换到菜单场景
				break;
			case('Q'):
				is_debug = !is_debug;
				break;
			}
		}
		player_1->on_event(msg); //处理玩家1的事件
		player_2->on_event(msg); //处理玩家2的事件
	}

};