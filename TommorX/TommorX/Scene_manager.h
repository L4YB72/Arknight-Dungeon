#pragma once
#include "Scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* select_scene;
extern Scene* solo_scene;

class Scene_manager {
private:
	Scene* current_scene = nullptr; //��ǰ����ָ��
public:
	enum class SceneType {
		Menu,
		Select,
		Game,
		Solo
	};

	static Scene_manager* instance; //����ģʽ
	Scene_manager() = default; //Ĭ�Ϲ��캯��
	~Scene_manager() = default; //Ĭ����������	

	void set_current_sceen(Scene* scene) { //���õ�ǰ����
		current_scene = scene;
		current_scene->on_load(); //���س���
	}

	void switch_to(SceneType type) {
		current_scene->on_unload();
		switch (type) {
		case SceneType::Menu:
			current_scene = menu_scene; //�л����˵�����
			break;
		case SceneType::Game:
			current_scene = game_scene; //�л�����Ϸ����
			break;
		case SceneType::Select:
			current_scene = select_scene; //�л���ѡ�񳡾�
			break;
		case SceneType::Solo:
			current_scene = solo_scene; //�л������˳���
			break;

		default:
			break;
		}
		current_scene->on_load();
	}

	void on_update(int delta) { //���µ�ǰ����
		if (current_scene) {
			current_scene->on_update(delta);
		}
	}

	void on_render(const Camera& camera) { //��Ⱦ��ǰ����
			if (current_scene) {
				current_scene->on_render(camera);
			}
		}

	void on_event(const ExMessage& msg) { //�����¼�
		if (current_scene) {
			current_scene->on_event(msg);
		}
	}


};