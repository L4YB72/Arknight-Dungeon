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
	MenuScene() = default; //默认构造函数
	~MenuScene() = default; //默认析构函数

	virtual void on_load(){//加载场景
	std::cout << "Loading Menu Scene..." << std::endl;

	//test
	image_background = background; //设置背景图片
	animation_Amiya_right_move.set_atlas(&Amiya_right_move); //设置动画图集
	animation_Amiya_left_move.set_atlas(&Amiya_left_move); //设置动画图集
	animation_Amiya_right_move.set_loop(true); //设置循环播放
	animation_Amiya_left_move.set_loop(true); //设置循环播放
	animation_Amiya_right_move.set_interval(700); //设置帧间隔时间
	animation_Amiya_left_move.set_interval(100); //设置帧间隔时间
	animation_Amiya_right_move.set_on_finished_callback(
		[]()
		{
			std::cout << "Amiya right move animation finished." << std::endl;
			scene_manager.switch_to(Scene_manager::SceneType::Game); //动画完成后切换到游戏场景
		}
	);
	timer.set_callback([] {
		std::cout << "Shot!" << std::endl;
		});
	timer.set_wait_time(1000);
	timer.set_one_shot(false);

	//test

	}
	virtual void on_update(int delta){ //更新场景
		std::cout << "Updating Menu Scene..." << std::endl;

		//test
		animation_Amiya_right_move.on_update(delta); //更新动画状态
		animation_Amiya_left_move.on_update(delta); //更新动画状态
		camera.on_update(delta); //更新相机位置
		timer.on_update(delta);
		//test
	}
	virtual void on_render(const Camera& camera){//渲染场景
		std::cout << "Rendering Menu Scene..." << std::endl;
		outtextxy(10, 10, _T("Menu Scene is rendering..."));

		//test
		const Vector2& camera_position = camera.get_poisition(); //获取相机位置
		for(int i=-1;i<4;i++) {
			for(int j=-1;j<4;j++) {
				putimage(i*image_background.getwidth() - camera_position.x, j * image_background.getheight() - camera_position.y, &image_background); //渲染背景图片
			}
		}
		animation_Amiya_right_move.on_draw((100 - camera_position.x), (100 - camera_position.y),camera); //渲染动画
		animation_Amiya_left_move.on_draw(200, 100,camera); //渲染动画
		putimage_alpha(0,0, &img_dust); //渲染灰尘图片

		//test

	}
	virtual void on_unload(){//卸载场景
		std::cout << "Unloading Menu Scene..." << std::endl;
	}
	virtual void on_event(const ExMessage& msg) override {
		if (msg.message == WM_KEYDOWN) {
			camera.shake(10, 1000); //按下任意键时抖动相机
			if (msg.vkcode == VK_SPACE) {
				scene_manager.switch_to(Scene_manager::SceneType::Select);//按下空格键切换到选择场景
			}
		}
	}
private:

	//test
	Timer timer;
	Camera camera; //创建相机对象
	Animation animation_Amiya_right_move;
	Animation animation_Amiya_left_move;
	IMAGE image_background; //背景图片
	//test

};