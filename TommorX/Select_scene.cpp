#include "Select_scene.h"
#include "tool.h" // 用于outtextxy_shaded
#include <iostream>

// 外部变量定义
extern Scene_manager scene_manager;
extern Player* player_1;
extern Player* player_2;

void SelectScene::on_load() {
    // 加载逻辑
}

void SelectScene::on_update(int delta) {
    // 更新逻辑
}

void SelectScene::on_render(const Camera& camera) {
    std::cout << "Rendering Select Scene..." << std::endl;
    outtextxy_shaded(10, 10, _T("Select Scene is rendering..."));

    for (int i = 0; i <= 1280; i += 50) {
        for (int j = 0; j <= 720; j += 50) {
            outtextxy(i, j, _T("a")); // 渲染字符 'a'
        }
    }
}

void SelectScene::on_unload() {
    // 在卸载场景时创建玩家对象
    switch (player_type_1) {
    case PlayerType::Amiya:
        player_1 = new Amiya(); // 创建Amiya玩家对象
        break;
    case PlayerType::Hei:
        player_1 = new Hei(); // 创建Hei玩家对象
        break;
    default:
        // 处理无效类型，可以设置默认值或抛出异常
        player_1 = new Amiya();
        break;
    }

    player_1->set_id(Player::PlayerId::P1); // 设置玩家ID

    // 创建第二个玩家对象
    player_2 = new Amiya();
    player_2->set_id(Player::PlayerId::P2);
}

void SelectScene::on_event(const ExMessage& msg) {
    if (msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {
        case 'A':
            is_player1_left_down = true; // 玩家按下左键
            break;
        case 'D':
            is_player1_right_down = true; // 玩家按下右键
            break;
        case VK_SPACE:
            std::cout << "Switching to Game Scene..." << std::endl;
            scene_manager.switch_to(Scene_manager::SceneType::Game); // 切换到游戏场景
            break;
        default:
            break;
        }
    }
    else if (msg.message == WM_KEYUP) {
        switch (msg.vkcode) {
        case 'A':
            is_player1_left_down = false; // 玩家松开左键
            // 左键松开时切换到上一个角色
            player_type_1 = static_cast<PlayerType>(
                (static_cast<int>(player_type_1) - 1 + static_cast<int>(PlayerType::Invalid)
                    ) % static_cast<int>(PlayerType::Invalid));
            break;
        case 'D':
            is_player1_right_down = false; // 玩家松开右键
            // 右键松开时切换到下一个角色
            player_type_1 = static_cast<PlayerType>(
                (static_cast<int>(player_type_1) + 1) % static_cast<int>(PlayerType::Invalid)
                );
            break;
        default:
            break;
        }
    }
}