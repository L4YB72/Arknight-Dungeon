#pragma once
#include "Scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* select_scene;
extern Scene* solo_scene;

class Scene_manager {
private:
	Scene* current_scene = nullptr; //当前场景指针
public:
	enum class SceneType {
		Menu,
		Select,
		Game,
		Solo
	};

	static Scene_manager* instance; //单例模式
	Scene_manager() = default; //默认构造函数
	~Scene_manager() = default; //默认析构函数	

	void set_current_sceen(Scene* scene) { //设置当前场景
		current_scene = scene;
		current_scene->on_load(); //加载场景
	}

	void switch_to(SceneType type) {
		current_scene->on_unload();
		switch (type) {
		case SceneType::Menu:
			current_scene = menu_scene; //切换到菜单场景
			break;
		case SceneType::Game:
			current_scene = game_scene; //切换到游戏场景
			break;
		case SceneType::Select:
			current_scene = select_scene; //切换到选择场景
			break;
		case SceneType::Solo:
			current_scene = solo_scene; //切换到单人场景
			break;

		default:
			break;
		}
		current_scene->on_load();
	}

	void on_update(int delta) { //更新当前场景
		if (current_scene) {
			current_scene->on_update(delta);
		}
	}

	void on_render(const Camera& camera) { //渲染当前场景
			if (current_scene) {
				current_scene->on_render(camera);
			}
		}

	void on_event(const ExMessage& msg) { //处理事件
		if (current_scene) {
			current_scene->on_event(msg);
		}
	}


};