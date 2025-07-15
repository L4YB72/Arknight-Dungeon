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
extern Player* player_1; //玩家1对象
extern Player* player_2; //玩家2对象
extern bool is_debug; //是否开启debug模式    




class GameScene : public Scene {
private:
	IMAGE image_background; //背景图片

	int current_map_id = 0; //当前地图索引
	std::vector<Map> map_list; //地图列表
	Map* current_map = nullptr; //当前地图指针
	Timer operate_timer; //操作计时器
	bool can_operate = true; //是否可以操作

	bool camera_shake = false; //相机抖动状态

	bool update = false;

    Timer idle_timer; // 检测玩家是否长时间未操作的计时器
    float idle_time_threshold = 2000; // 2秒不操作后怪物自动行动（单位：毫秒）

	std::vector<Enemy*> enemy_list;
	std::vector<Enemy*> enemy_back;

	DamageManager damage_manager; //伤害管理器
	ArmManager arm_manager; //武器管理器
	SkillManager skill_manager; //技能管理器
	bool choose_arm = false; //是否选择武器



public:
	GameScene() = default; //默认构造函数
	~GameScene() = default; //默认析构函数
	void on_load() { //加载场景
		map_list.clear(); //清空地图列表
		image_background = background; //设置背景图片
		for(int i=0;i<3;i++) {
			map_list.push_back(Map()); //添加 地图到列表
		}
		current_map = &map_list[current_map_id]; //设置当前地图
		operate_timer.set_wait_time(200);
		operate_timer.set_callback([this]() { //操作计时器回调函数
			this->can_operate = true;

		});
		player_1->on_load();
		player_1->set_arm(arm_manager.arm_list[0]);
		player_1->set_skill(skill_manager.skill_list[0]);
		enemy_list.clear(); //清空敌人列表
	}


	void map_refresh() {
		static Vector2 last_player_room = player_1->get_room(); //获取玩家所在房间
		//std::cout << "PR" << player_1->get_room().x << player_1->get_room().y << std::endl;
		//std::cout << "LR" << last_player_room.x << last_player_room.y << std::endl;
		if (last_player_room == player_1->get_room()) {
			return;
		}
		else {
			enemy_list.clear(); //清空敌人列表f
			
			int n = 0;
			for (int x1 = player_1->get_room().x * 8; x1 < player_1->get_room().x * 8 + 8; x1++) {
				for (int y1 = player_1->get_room().y * 8; y1 < player_1->get_room().y * 8 + 8; y1++) {
					if (current_map->get_object(x1, y1) == 99) {
						current_map->edit(x1, y1, 0); //清除房间内的99
						int r = rand() % 3; // 生成0~2的随机数
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
						e->on_load(x1, y1); //加载敌人
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
			for (int i = 0; i < n; i++) {//根据房间刷新敌人
				
			}
		}
		last_player_room = player_1->get_room(); //更新最后玩家所在房间
	}

	void on_update(int delta) { //更新场景
		current_map = &map_list[current_map_id]; //设置当前地图
		operate_timer.on_update(delta); //更新操作计时器
		if (current_map->get_object(player_1->get_real_block())==88) {
			current_map_id = (current_map_id + 1) % map_list.size(); //如果玩家在传送点，切换地图
			player_1->down_stair(); //玩家下楼
			return; //直接返回
		}
		else if (current_map->get_object(player_1->get_real_block()) == 787) {
			current_map->edit((int)player_1->get_real_block().x, (int)player_1->get_real_block().y, 0); //清除房间内的99
			choose_arm = true; //设置选择武器状态
			arm_manager.type_roll(); //随机选择武器类型
		}
		//操作刷新
		map_refresh();
		for (auto& ee : enemy_list) {
			if (update && ee != nullptr) {
				ee->move(current_map); //敌人移动
			}
		}
		for (auto &ee : enemy_list) {
			//ee->on_update(delta); //更新敌人			//待修改
			if (update){
				damage_manager.deal(player_1, ee);
			}
		}

		player_1->on_update(delta, current_map); //更新玩家1
		if(update)
			player_1->skill->cd_update(); //更新技能冷却时间

		for (auto& ee : enemy_list) {	
			update = 1;
			if (update && ee != nullptr) {
				ee->on_update(delta); //更新敌人			//待修改
			}
		}
		main_camera.set_position(player_1->get_position() - Vector2(490, 200)); //设置相机位置为玩家1的位置
		current_map->on_update(delta, player_1->get_real_position()); //更新当前地图
		update = false; //重置更新状态
		for (auto it = enemy_back.begin(); it != enemy_back.end(); ) {
			delete* it; // 删除已死亡的敌人
			it = enemy_back.erase(it); // 从列表中删除并更新迭代器
		}

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

		for (auto&ee : enemy_list) {
			ee->on_render(camera);
		}

		if (choose_arm) {
			arm_manager.on_render(); //渲染武器选择界面
		}

		//ui渲染
		player_1->on_ui_render(); //渲染玩家1的UI
		TCHAR levell[16];
		_stprintf_s(levell, _countof(levell), _T("LEVEL: %d"), current_map_id+1);
		outtextxy(10, 0, levell);
	}

	void on_unload() { //卸载场景
		
	}

	void on_event(const ExMessage& msg) { //处理事件
		if (msg.message == WM_KEYDOWN) {
			camera_shake = true; //按下任意键时抖动相机
			if (msg.vkcode == VK_SPACE) {
				scene_manager.switch_to(Scene_manager::SceneType::Solo);//按下空格键切换到选择场景
			}
			if (msg.vkcode == VK_ESCAPE && is_debug)
				current_map_id = (++current_map_id) % 3;
		}

		//操作检测 
		if (choose_arm == true) {
			if (msg.message == WM_KEYDOWN) {
				player_1->set_arm(arm_manager.choose_arm(&msg)); //选择武器
				choose_arm = false;
			}
		}
		else {
			//if (idle_timer.get_elapsed_time() > idle_time_threshold) {
			//	update = true; //如果玩家长时间未操作，设置更新状态
			//	for (auto& ee : enemy_list) {
			//		ee->move(current_map); //敌人自动行动
			//	}
			//	idle_timer.restart(); //重启计时器
			//}
			if (can_operate) {
				if (msg.message == WM_KEYDOWN) {
					update = true;
					player_1->on_event(msg);//玩家1处理事件
					can_operate = false; //设置为不可操作
					operate_timer.restart(); //重启操作计时器
				}
			}
		}
	}


};


