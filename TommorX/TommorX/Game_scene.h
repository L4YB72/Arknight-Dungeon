#pragma once
#include <graphics.h>
#include "Scene.h"
#include "Scene_manager.h"
#include "Player.h"
#include "Amiya.h"
#include "Camera.h"

extern Scene_manager scene_manager;
extern Camera main_camera;

extern IMAGE background; 
extern Player* player_1; //玩家1对象
extern Player* player_2; //玩家2对象
extern bool is_debug; //是否开启debug模式



class GameScene : public Scene {
private:
	IMAGE image_background; //背景图片

	int current_map_id = 0; //当前地图索引
	std::vector<Map> map_list; //地图列表
	Map* current_map = nullptr; //当前地图指针

	bool camera_shake = false; //相机抖动状态

public:
	GameScene() = default; //默认构造函数
	~GameScene() = default; //默认析构函数
	void on_load() { //加载场景
		map_list.clear(); //清空地图列表
		image_background = background; //设置背景图片
		for(int i=0;i<3;i++) {
			map_list.push_back(Map()); //添加地图到列表
		}
		current_map = &map_list[current_map_id]; //设置当前地图
		player_1->on_load();
		player_2->on_load();
	}

	void on_update(int delta) { //更新场景
		current_map = &map_list[current_map_id]; //设置当前地图
		player_1->on_update(delta); //更新玩家1
		player_2->on_update(delta); //更新玩家2
		main_camera.set_position(player_1->get_position()-Vector2(490,200)); //设置相机位置为玩家1的位置
		//if(camera_shake)
		//	main_camera.shake(1, 100); //抖动相机
		//camera_shake = false; //重置抖动状态
		//main_camera.on_update(delta); //更新相机状态
	}

	void on_render(const Camera& camera) { //渲染场景

		const Vector2& camera_position = camera.get_poisition(); //获取相机位置
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				putimage(i * image_background.getwidth() - camera_position.x, j * image_background.getheight() - camera_position.y, &image_background); //渲染背景图片
			}
		}
		settextcolor(WHITE); //设置文字颜色
		outtextxy(10, 10, _T("Game Scene is rendering..."));

		current_map->map_render(camera); //渲染当前地图
		player_1->on_render(camera); //渲染玩家1
		player_2->on_render(camera); //渲染玩家2

	}

	void on_unload() { //卸载场景
		std::cout << "Unloading Game Scene..." << std::endl;
	}

	void on_event(const ExMessage& msg) { //处理事件
		if (msg.message == WM_KEYDOWN) {
			camera_shake = true; //按下任意键时抖动相机
			if (msg.vkcode == VK_SPACE) {
				scene_manager.switch_to(Scene_manager::SceneType::Solo);//按下空格键切换到选择场景
			}
		}
		player_1->on_event(msg); //处理玩家1的事件
		player_2->on_event(msg); //处理玩家2的事件
	}

};