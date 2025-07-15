//#include <graphics.h>
//#include <string>
//#include "Anmi.h"
//#include "Amiya.h"
//#include "Operate.h"
//#include <iostream>
//#include "Scene.h"
//#include "menu_scene.h"
//
////游戏阶段
//enum Stage {
//	Manu = 0
//};
//
//
///*
//{
//
//	init_amiya();
//	ExMessage msg;//消息
//	//背景图
//	IMAGE img_background;
//	loadimage(&img_background, _T("Image/res/bw.png"), 600, 600, true);
//
//}
//*/
//
//
//
//int main() {
//	//初始化
//	bool running = true;
//	initgraph(1280, 720, EX_SHOWCONSOLE | EX_NOCLOSE);//初始化画布
//
//
//	//游戏主循环
//	BeginBatchDraw();
//	Scene* scene = new MenuScene(); //创建场景 
//
//	while (running) {
//		DWORD start_time = GetTickCount();
//
//		//获取操作
//		while (peekmessage(&msg)) {
//			scene->on_event(msg); //处理事件
//		}
//		//修改信息
//		scene->on_update(); //更新场景
//		//渲染图片
//
//
//		cleardevice();
//		scene->on_render(); //渲染场景
//
//
//
//		FlushBatchDraw();
//
//		DWORD end_time = GetTickCount();
//		DWORD delta_time = end_time - start_time;
//		std::cout << "{}" << delta_time << std::endl;
//		if (delta_time < 1000 / 61) {
//			Sleep(1000 / 61 - delta_time);//每秒61帧，性能优化
//		}
//	}
//
//	EndBatchDraw();
//}
//
//
//
//
