//#include <graphics.h>
//#include <string>
//#include "Anmi.h"
//#include "Amiya.h"
//#include "Operate.h"
//#include <iostream>
//#include "Scene.h"
//#include "menu_scene.h"
//
////��Ϸ�׶�
//enum Stage {
//	Manu = 0
//};
//
//
///*
//{
//
//	init_amiya();
//	ExMessage msg;//��Ϣ
//	//����ͼ
//	IMAGE img_background;
//	loadimage(&img_background, _T("Image/res/bw.png"), 600, 600, true);
//
//}
//*/
//
//
//
//int main() {
//	//��ʼ��
//	bool running = true;
//	initgraph(1280, 720, EX_SHOWCONSOLE | EX_NOCLOSE);//��ʼ������
//
//
//	//��Ϸ��ѭ��
//	BeginBatchDraw();
//	Scene* scene = new MenuScene(); //�������� 
//
//	while (running) {
//		DWORD start_time = GetTickCount();
//
//		//��ȡ����
//		while (peekmessage(&msg)) {
//			scene->on_event(msg); //�����¼�
//		}
//		//�޸���Ϣ
//		scene->on_update(); //���³���
//		//��ȾͼƬ
//
//
//		cleardevice();
//		scene->on_render(); //��Ⱦ����
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
