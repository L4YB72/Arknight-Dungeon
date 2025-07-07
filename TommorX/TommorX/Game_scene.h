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
extern Player* player_1; //���1����
extern Player* player_2; //���2����
extern bool is_debug; //�Ƿ���debugģʽ



class GameScene : public Scene {
private:
	IMAGE image_background; //����ͼƬ

	int current_map_id = 0; //��ǰ��ͼ����
	std::vector<Map> map_list; //��ͼ�б�
	Map* current_map = nullptr; //��ǰ��ͼָ��

	bool camera_shake = false; //�������״̬

public:
	GameScene() = default; //Ĭ�Ϲ��캯��
	~GameScene() = default; //Ĭ����������
	void on_load() { //���س���
		map_list.clear(); //��յ�ͼ�б�
		image_background = background; //���ñ���ͼƬ
		for(int i=0;i<3;i++) {
			map_list.push_back(Map()); //��ӵ�ͼ���б�
		}
		current_map = &map_list[current_map_id]; //���õ�ǰ��ͼ
		player_1->on_load();
		player_2->on_load();
	}

	void on_update(int delta) { //���³���
		current_map = &map_list[current_map_id]; //���õ�ǰ��ͼ
		player_1->on_update(delta); //�������1
		player_2->on_update(delta); //�������2
		main_camera.set_position(player_1->get_position()-Vector2(490,200)); //�������λ��Ϊ���1��λ��
		//if(camera_shake)
		//	main_camera.shake(1, 100); //�������
		//camera_shake = false; //���ö���״̬
		//main_camera.on_update(delta); //�������״̬
	}

	void on_render(const Camera& camera) { //��Ⱦ����

		const Vector2& camera_position = camera.get_poisition(); //��ȡ���λ��
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				putimage(i * image_background.getwidth() - camera_position.x, j * image_background.getheight() - camera_position.y, &image_background); //��Ⱦ����ͼƬ
			}
		}
		settextcolor(WHITE); //����������ɫ
		outtextxy(10, 10, _T("Game Scene is rendering..."));

		current_map->map_render(camera); //��Ⱦ��ǰ��ͼ
		player_1->on_render(camera); //��Ⱦ���1
		player_2->on_render(camera); //��Ⱦ���2

	}

	void on_unload() { //ж�س���
		std::cout << "Unloading Game Scene..." << std::endl;
	}

	void on_event(const ExMessage& msg) { //�����¼�
		if (msg.message == WM_KEYDOWN) {
			camera_shake = true; //���������ʱ�������
			if (msg.vkcode == VK_SPACE) {
				scene_manager.switch_to(Scene_manager::SceneType::Solo);//���¿ո���л���ѡ�񳡾�
			}
		}
		player_1->on_event(msg); //�������1���¼�
		player_2->on_event(msg); //�������2���¼�
	}

};