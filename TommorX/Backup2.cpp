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
////��Ϸ�׶�
//enum Stage {
//	Manu = 0
//};
//
//
//void init_amiya() {
//	initgraph(1280, 720, EX_SHOWCONSOLE | EX_NOCLOSE);//��ʼ������
//	amiya.speed = 10;
//	amiya.x = 0;
//	amiya.y = 0;
//}
//
//int main() {
//	//��ʼ��
//	bool running = true;
//
//	init_amiya();
//
//	ExMessage msg;//��Ϣ
//	//����ͼ
//	IMAGE img_background;
//	loadimage(&img_background, _T("Image/res/bw.png"), 600, 600, true);
//
//	//��Ϸ��ѭ��
//	BeginBatchDraw();
//	while (running) {
//		DWORD start_time = GetTickCount();
//
//		//��ȡ����
//		while (peekmessage(&msg)) {
//			if (msg.message == WM_KEYDOWN) {
//				switch (msg.vkcode) {
//				case(VK_ESCAPE):exit(0);
//				}
//			}
//			move_detact(msg);
//		}
//		//�޸���Ϣ
//		move_activate();
//
//		//��ȾͼƬ
//
//
//		cleardevice();
//		load_background(img_background);//���صذ�
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
//			Sleep(1000 / 61 - delta_time);//ÿ��61֡�������Ż�
//		}
//	}
//
//	EndBatchDraw();
//}
//
//
//
//
