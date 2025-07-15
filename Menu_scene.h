#pragma once
#include "Scene.h"
#include <iostream>
#include <graphics.h>
#include "Scene_manager.h"
#include "Animation.h"
#include "Atlas.h"
#include "Camera.h"
#include "Timer.h"
#include "Map.h"

//test
extern Atlas Amiya_right_move;
extern Atlas Amiya_left_move;
extern IMAGE background;
extern IMAGE img_dust;
extern IMAGE img_crystal;
extern IMAGE img_stone;
extern IMAGE ig_machine;

//test

extern Scene_manager scene_manager;

class MenuScene : public Scene {
public:
	MenuScene() = default; //Ĭ�Ϲ��캯��
	~MenuScene() = default; //Ĭ����������

	virtual void on_load(){//���س���
	std::cout << "Loading Menu Scene..." << std::endl;

	//test
	image_background = background; //���ñ���ͼƬ
	animation_Amiya_right_move.set_atlas(&Amiya_right_move); //���ö���ͼ��
	animation_Amiya_left_move.set_atlas(&Amiya_left_move); //���ö���ͼ��
	animation_Amiya_right_move.set_loop(true); //����ѭ������
	animation_Amiya_left_move.set_loop(true); //����ѭ������
	animation_Amiya_right_move.set_interval(700); //����֡���ʱ��
	animation_Amiya_left_move.set_interval(100); //����֡���ʱ��
	animation_Amiya_right_move.set_on_finished_callback(
		[]()
		{
			std::cout << "Amiya right move animation finished." << std::endl;
			scene_manager.switch_to(Scene_manager::SceneType::Game); //������ɺ��л�����Ϸ����
		}
	);
	timer.set_callback([] {
		std::cout << "Shot!" << std::endl;
		});
	timer.set_wait_time(1000);
	timer.set_one_shot(false);

	//test

	}
	virtual void on_update(int delta){ //���³���
		std::cout << "Updating Menu Scene..." << std::endl;

		//test
		animation_Amiya_right_move.on_update(delta); //���¶���״̬
		animation_Amiya_left_move.on_update(delta); //���¶���״̬
		camera.on_update(delta); //�������λ��
		timer.on_update(delta);
		//test
	}
	virtual void on_render(const Camera& camera){//��Ⱦ����
		std::cout << "Rendering Menu Scene..." << std::endl;
		outtextxy(10, 10, _T("Menu Scene is rendering..."));

		//test
		const Vector2& camera_position = camera.get_poisition(); //��ȡ���λ��
		for(int i=-1;i<4;i++) {
			for(int j=-1;j<4;j++) {
				putimage(i*image_background.getwidth() - camera_position.x, j * image_background.getheight() - camera_position.y, &image_background); //��Ⱦ����ͼƬ
			}
		}
		animation_Amiya_right_move.on_draw((100 - camera_position.x), (100 - camera_position.y),camera); //��Ⱦ����
		animation_Amiya_left_move.on_draw(200, 100,camera); //��Ⱦ����
		putimage_alpha(0,0, &img_dust); //��Ⱦ�ҳ�ͼƬ

		//test

	}
	virtual void on_unload(){//ж�س���
		std::cout << "Unloading Menu Scene..." << std::endl;
	}
	virtual void on_event(const ExMessage& msg) override {
		if (msg.message == WM_KEYDOWN) {
			camera.shake(10, 1000); //���������ʱ�������
			if (msg.vkcode == VK_SPACE) {
				scene_manager.switch_to(Scene_manager::SceneType::Select);//���¿ո���л���ѡ�񳡾�
			}
		}
	}
private:

	//test
	Timer timer;
	Camera camera; //�����������
	Animation animation_Amiya_right_move;
	Animation animation_Amiya_left_move;
	IMAGE image_background; //����ͼƬ
	//test

};