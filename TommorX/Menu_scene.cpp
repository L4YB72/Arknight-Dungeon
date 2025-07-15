#include "Menu_scene.h"
#include <iostream>
#include "Scene_manager.h"

// �ⲿ��������
extern Atlas Amiya_right_move;
extern Atlas Amiya_left_move;
extern IMAGE background;
extern IMAGE img_dust;
extern Scene_manager scene_manager;

void MenuScene::on_load() {
    std::cout << "Loading Menu Scene..." << std::endl;

    // ���ñ���ͼƬ
    image_background = background;

    // ���ö���ͼ��
    animation_Amiya_right_move.set_atlas(&Amiya_right_move);
    animation_Amiya_left_move.set_atlas(&Amiya_left_move);

    // ���ö�������
    animation_Amiya_right_move.set_loop(true);
    animation_Amiya_left_move.set_loop(true);
    animation_Amiya_right_move.set_interval(700);
    animation_Amiya_left_move.set_interval(100);

    // ���ö�����ɻص�
    animation_Amiya_right_move.set_on_finished_callback([]() {
        std::cout << "Amiya right move animation finished." << std::endl;
        scene_manager.switch_to(Scene_manager::SceneType::Game); // ������ɺ��л�����Ϸ����
        });

    // ���ö�ʱ��
    timer.set_callback([] {
        std::cout << "Shot!" << std::endl;
        });
    timer.set_wait_time(1000);
    timer.set_one_shot(false);
}

void MenuScene::on_update(int delta) {
    std::cout << "Updating Menu Scene..." << std::endl;

    // ���¶���״̬
    animation_Amiya_right_move.on_update(delta);
    animation_Amiya_left_move.on_update(delta);

    // �������λ��
    camera.on_update(delta);

    // ���¶�ʱ��
    timer.on_update(delta);
}

void MenuScene::on_render(const Camera& camera) {
    std::cout << "Rendering Menu Scene..." << std::endl;
    outtextxy(10, 10, _T("Menu Scene is rendering..."));

    // ��ȡ���λ��
    const Vector2& camera_position = camera.get_poisition();

    // ��Ⱦ����ͼƬ
    for (int i = -1; i < 4; i++) {
        for (int j = -1; j < 4; j++) {
            putimage(i * image_background.getwidth() - camera_position.x,
                j * image_background.getheight() - camera_position.y,
                &image_background);
        }
    }

    // ��Ⱦ����
    animation_Amiya_right_move.on_draw(100 - camera_position.x, 100 - camera_position.y, camera);
    animation_Amiya_left_move.on_draw(200 - camera_position.x, 100 - camera_position.y, camera);

    // ��Ⱦ�ҳ�ͼƬ
    putimage_alpha(0, 0, &img_dust);
}

void MenuScene::on_unload() {
    std::cout << "Unloading Menu Scene..." << std::endl;
}

void MenuScene::on_event(const ExMessage& msg) {
    if (msg.message == WM_KEYDOWN) {
        // �������
        this->camera.shake(10, 1000);

        // �ո���л���ѡ�񳡾�
        if (msg.vkcode == VK_SPACE) {
            scene_manager.switch_to(Scene_manager::SceneType::Select);
        }
    }
}