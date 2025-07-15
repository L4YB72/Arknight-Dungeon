#include <graphics.h>
#include <string>
//#include "Anmi.h"
//#include "Amiya.h"
//#include "Operate.h"

#include <iostream>
#include "Scene.h"
#include "Menu_scene.h"
#include "Game_scene.h"
#include "Game_scene_solo.h"
#include "Select_scene.h"
#include "Scene_manager.h"
#include "immmma.h"
#include "Map.h"
#include <stdlib.h>
#include <time.h>
#include <chrono>

bool is_debug = false; //是否开启debug模式

//游戏阶段
enum Stage {
	Menu = 0
};

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* select_scene = nullptr;
Scene* solo_scene = nullptr;
Scene_manager scene_manager;

//Player



Camera main_camera; //主摄像机

int main() {
	//初始化
	bool running = true;
	initgraph(1920,1080, EX_SHOWCONSOLE | EX_NOCLOSE);//初始化画布
	Scene* scene = new MenuScene(); //创建场景 
	ExMessage msg;//消息
	load_game_resources(); //加载游戏资源

	srand(time(NULL)); 
	room_map_generate();

	//游戏主循环
	BeginBatchDraw();
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	select_scene = new SelectScene(); 
	solo_scene = new GameSceneSolo();
	scene_manager.set_current_sceen(menu_scene);

	scene->on_load(); //加载场景

	while (running) {
		DWORD start_time = GetTickCount();

		//获取操作
		while (peekmessage(&msg)) {
			scene_manager.on_event(msg); //处理事件
		}
		//修改信息
		
		//
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		int delta_tick_time = current_tick_time - last_tick_time;
		last_tick_time = current_tick_time;

		scene_manager.on_update(delta_tick_time); //更新场景

		//渲染图片


		cleardevice();

		scene_manager.on_render(main_camera); //渲染场景

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 61) {
			Sleep(1000 / 61 - delta_time);//每秒61帧，性能优化
		}
	}

	EndBatchDraw();
}




