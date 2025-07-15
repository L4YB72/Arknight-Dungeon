#include "Menu_scene.h"
#include <iostream>
#include "Scene_manager.h"

// 外部变量声明
extern Atlas Amiya_right_move;
extern Atlas Amiya_left_move;
extern IMAGE background;
extern IMAGE img_dust;
extern Scene_manager scene_manager;

void MenuScene::on_load() {
    std::cout << "Loading Menu Scene..." << std::endl;

    // 设置背景图片
    image_background = background;

    // 设置动画图集
    animation_Amiya_right_move.set_atlas(&Amiya_right_move);
    animation_Amiya_left_move.set_atlas(&Amiya_left_move);

    // 设置动画属性
    animation_Amiya_right_move.set_loop(true);
    animation_Amiya_left_move.set_loop(true);
    animation_Amiya_right_move.set_interval(700);
    animation_Amiya_left_move.set_interval(100);

    // 设置动画完成回调
    animation_Amiya_right_move.set_on_finished_callback([]() {
        std::cout << "Amiya right move animation finished." << std::endl;
        scene_manager.switch_to(Scene_manager::SceneType::Game); // 动画完成后切换到游戏场景
        });

    // 设置定时器
    timer.set_callback([] {
        std::cout << "Shot!" << std::endl;
        });
    timer.set_wait_time(1000);
    timer.set_one_shot(false);
}

void MenuScene::on_update(int delta) {
    std::cout << "Updating Menu Scene..." << std::endl;

    // 更新动画状态
    animation_Amiya_right_move.on_update(delta);
    animation_Amiya_left_move.on_update(delta);

    // 更新相机位置
    camera.on_update(delta);

    // 更新定时器
    timer.on_update(delta);
}

void MenuScene::on_render(const Camera& camera) {
    std::cout << "Rendering Menu Scene..." << std::endl;
    outtextxy(10, 10, _T("Menu Scene is rendering..."));

    // 获取相机位置
    const Vector2& camera_position = camera.get_poisition();

    // 渲染背景图片
    for (int i = -1; i < 4; i++) {
        for (int j = -1; j < 4; j++) {
            putimage(i * image_background.getwidth() - camera_position.x,
                j * image_background.getheight() - camera_position.y,
                &image_background);
        }
    }

    // 渲染动画
    animation_Amiya_right_move.on_draw(100 - camera_position.x, 100 - camera_position.y, camera);
    animation_Amiya_left_move.on_draw(200 - camera_position.x, 100 - camera_position.y, camera);

    // 渲染灰尘图片
    putimage_alpha(0, 0, &img_dust);
}

void MenuScene::on_unload() {
    std::cout << "Unloading Menu Scene..." << std::endl;
}

void MenuScene::on_event(const ExMessage& msg) {
    if (msg.message == WM_KEYDOWN) {
        // 相机抖动
        this->camera.shake(10, 1000);

        // 空格键切换到选择场景
        if (msg.vkcode == VK_SPACE) {
            scene_manager.switch_to(Scene_manager::SceneType::Select);
        }
    }
}