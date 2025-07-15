#pragma once
#include <graphics.h>
#include "Scene.h"
#include "Scene_manager.h"
#include "Player.h"
#include "Amiya.h"
#include "Camera.h"
#include "Enemy.h"
#include "B1.h"
#include "B2.h"
#include "DamageManager.h"
#include "Timer.h"
#include "ArmManager.h" 
#include "SkillManager.h"

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
	Timer operate_timer; //������ʱ��
	bool can_operate = true; //�Ƿ���Բ���

	bool camera_shake = false; //�������״̬

	bool update = false;

    Timer idle_timer; // �������Ƿ�ʱ��δ�����ļ�ʱ��
    float idle_time_threshold = 2000; // 2�벻����������Զ��ж�����λ�����룩

	std::vector<Enemy*> enemy_list;
	std::vector<Enemy*> enemy_back;

	DamageManager damage_manager; //�˺�������
	ArmManager arm_manager; //����������
	SkillManager skill_manager; //���ܹ�����
	bool choose_arm = false; //�Ƿ�ѡ������



public:
	GameScene() = default; //Ĭ�Ϲ��캯��
	~GameScene() = default; //Ĭ����������
	void on_load() { //���س���
		map_list.clear(); //��յ�ͼ�б�
		image_background = background; //���ñ���ͼƬ
		for(int i=0;i<3;i++) {
			map_list.push_back(Map()); //��� ��ͼ���б�
		}
		current_map = &map_list[current_map_id]; //���õ�ǰ��ͼ
		operate_timer.set_wait_time(200);
		operate_timer.set_callback([this]() { //������ʱ���ص�����
			this->can_operate = true;

		});
		player_1->on_load();
		player_1->set_arm(arm_manager.arm_list[0]);
		player_1->set_skill(skill_manager.skill_list[0]);
		enemy_list.clear(); //��յ����б�
	}


	void map_refresh() {
		static Vector2 last_player_room = player_1->get_room(); //��ȡ������ڷ���
		//std::cout << "PR" << player_1->get_room().x << player_1->get_room().y << std::endl;
		//std::cout << "LR" << last_player_room.x << last_player_room.y << std::endl;
		if (last_player_room == player_1->get_room()) {
			return;
		}
		else {
			enemy_list.clear(); //��յ����б�f
			
			int n = 0;
			for (int x1 = player_1->get_room().x * 8; x1 < player_1->get_room().x * 8 + 8; x1++) {
				for (int y1 = player_1->get_room().y * 8; y1 < player_1->get_room().y * 8 + 8; y1++) {
					if (current_map->get_object(x1, y1) == 99) {
						current_map->edit(x1, y1, 0); //��������ڵ�99
						int r = rand() % 3; // ����0~2�������
						Enemy* e = nullptr;
						if (r == 0) {
							e = new B1(current_map_id);
						}
						else if (r == 1) {
							e = new B2(current_map_id);
						}
						else {
							e = new B2(current_map_id);
						}
						e->on_load(x1, y1); //���ص���
						e->set_on_dead_callback([this, e]() mutable {
							auto it = std::find(enemy_list.begin(), enemy_list.end(), e);
							if (it != enemy_list.end()) {
								enemy_list.erase(it);
								enemy_back.push_back(e);
								player_1->player_money_add();
							}
							});
						enemy_list.push_back(e);
					}
				}
			}
			for (int i = 0; i < n; i++) {//���ݷ���ˢ�µ���
				
			}
		}
		last_player_room = player_1->get_room(); //�������������ڷ���
	}

	void on_update(int delta) { //���³���
		current_map = &map_list[current_map_id]; //���õ�ǰ��ͼ
		operate_timer.on_update(delta); //���²�����ʱ��
		if (current_map->get_object(player_1->get_real_block())==88) {
			current_map_id = (current_map_id + 1) % map_list.size(); //�������ڴ��͵㣬�л���ͼ
			player_1->down_stair(); //�����¥
			return; //ֱ�ӷ���
		}
		else if (current_map->get_object(player_1->get_real_block()) == 787) {
			current_map->edit((int)player_1->get_real_block().x, (int)player_1->get_real_block().y, 0); //��������ڵ�99
			choose_arm = true; //����ѡ������״̬
			arm_manager.type_roll(); //���ѡ����������
		}
		//����ˢ��
		map_refresh();
		for (auto& ee : enemy_list) {
			if (update && ee != nullptr) {
				ee->move(current_map); //�����ƶ�
			}
		}
		for (auto &ee : enemy_list) {
			//ee->on_update(delta); //���µ���			//���޸�
			if (update){
				damage_manager.deal(player_1, ee);
			}
		}

		player_1->on_update(delta, current_map); //�������1
		if(update)
			player_1->skill->cd_update(); //���¼�����ȴʱ��

		for (auto& ee : enemy_list) {	
			update = 1;
			if (update && ee != nullptr) {
				ee->on_update(delta); //���µ���			//���޸�
			}
		}
		main_camera.set_position(player_1->get_position() - Vector2(490, 200)); //�������λ��Ϊ���1��λ��
		current_map->on_update(delta, player_1->get_real_position()); //���µ�ǰ��ͼ
		update = false; //���ø���״̬
		for (auto it = enemy_back.begin(); it != enemy_back.end(); ) {
			delete* it; // ɾ���������ĵ���
			it = enemy_back.erase(it); // ���б���ɾ�������µ�����
		}

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

		for (auto&ee : enemy_list) {
			ee->on_render(camera);
		}

		if (choose_arm) {
			arm_manager.on_render(); //��Ⱦ����ѡ�����
		}

		//ui��Ⱦ
		player_1->on_ui_render(); //��Ⱦ���1��UI
		TCHAR levell[16];
		_stprintf_s(levell, _countof(levell), _T("LEVEL: %d"), current_map_id+1);
		outtextxy(10, 0, levell);
	}

	void on_unload() { //ж�س���
		
	}

	void on_event(const ExMessage& msg) { //�����¼�
		if (msg.message == WM_KEYDOWN) {
			camera_shake = true; //���������ʱ�������
			if (msg.vkcode == VK_SPACE) {
				scene_manager.switch_to(Scene_manager::SceneType::Solo);//���¿ո���л���ѡ�񳡾�
			}
			if (msg.vkcode == VK_ESCAPE && is_debug)
				current_map_id = (++current_map_id) % 3;
		}

		//������� 
		if (choose_arm == true) {
			if (msg.message == WM_KEYDOWN) {
				player_1->set_arm(arm_manager.choose_arm(&msg)); //ѡ������
				choose_arm = false;
			}
		}
		else {
			//if (idle_timer.get_elapsed_time() > idle_time_threshold) {
			//	update = true; //�����ҳ�ʱ��δ���������ø���״̬
			//	for (auto& ee : enemy_list) {
			//		ee->move(current_map); //�����Զ��ж�
			//	}
			//	idle_timer.restart(); //������ʱ��
			//}
			if (can_operate) {
				if (msg.message == WM_KEYDOWN) {
					update = true;
					player_1->on_event(msg);//���1�����¼�
					can_operate = false; //����Ϊ���ɲ���
					operate_timer.restart(); //����������ʱ��
				}
			}
		}
	}


};


