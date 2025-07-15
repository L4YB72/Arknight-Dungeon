#include "Game_scene_solo.h"
#include <iostream>

// 外部变量声明
extern Camera main_camera;
extern Scene_manager scene_manager;
extern bool is_debug;
extern Player* player_1;
extern Player* player_2;
extern Atlas B1_idle_right;
extern Atlas Amiya_right_move;

GameSceneSolo::~GameSceneSolo() {
    // 清理分配的b1对象
    if (b1 != nullptr) {
        delete b1;
        b1 = nullptr;
    }
}

void GameSceneSolo::on_load() {
    // 创建B1敌人对象
    b1 = new B1();
}

void GameSceneSolo::on_update(int delta) {
    // 输出调试信息
    if (is_debug) {
        std::cout << "Solo scene update" << std::endl;
        std::cout << "Updating Player 1..." << std::endl;
        std::cout << "Updating Enemy" << std::endl;
    }

    // 更新敌人B1
    if (b1 != nullptr) {
        b1->on_update(delta);
    }
}

void GameSceneSolo::on_render(const Camera& camera) {
    // 显示调试文本
    if (is_debug) {
        settextcolor(RED);
        outtextxy(200, 200, _T("Deguging"));
    }

    // 渲染场景文本
    outtextxy(10, 10, _T("Solo Scene is rendering"));

    // 渲染敌人B1
    if (b1 != nullptr) {
        b1->on_render(camera);
    }

    // 调试输出
    if (is_debug) {
        std::cout << 999 << std::endl;
    }
}

void GameSceneSolo::on_unload() {
    // 清理资源（已在析构函数中处理）
}

void GameSceneSolo::on_event(const ExMessage& msg) {
    if (msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {
        case VK_SPACE:
            scene_manager.switch_to(Scene_manager::SceneType::Menu);
            break;
        case 'Q':
            is_debug = !is_debug;
            break;
        }
    }

    // 处理玩家事件
    if (player_1 != nullptr) {
        player_1->on_event(msg);
    }
    if (player_2 != nullptr) {
        player_2->on_event(msg);
    }
}