//#include <graphics.h>
//#include <string>
//#include "Anmi.h"
//#include "Amiya.h"
//#include "Operate.h"
//#include <iostream>
//
//
//extern Amiya amiya;
//extern const int AMIYA_ANIM_NUM;
////游戏阶段
//enum Stage {
//	Manu = 0
//};
//
//
//void init_amiya() {
//	initgraph(1280, 720, EX_SHOWCONSOLE | EX_NOCLOSE);//初始化画布
//	amiya.speed = 10;
//	amiya.x = 0;
//	amiya.y = 0;
//}
//
//int main() {
//	//初始化
//	bool running = true;
//
//	init_amiya();
//
//	ExMessage msg;//消息
//	//背景图
//	IMAGE img_background;
//	loadimage(&img_background, _T("Image/res/bw.png"), 600, 600, true);
//
//	//游戏主循环
//	BeginBatchDraw();
//	while (running) {
//		DWORD start_time = GetTickCount();
//
//		//获取操作
//		while (peekmessage(&msg)) {
//			if (msg.message == WM_KEYDOWN) {
//				switch (msg.vkcode) {
//				case(VK_ESCAPE):exit(0);
//				}
//			}
//			move_detact(msg);
//		}
//		//修改信息
//		move_activate();
//
//		//渲染图片
//
//
//		cleardevice();
//		load_background(img_background);//加载地板
//		DrawAnimation();
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
