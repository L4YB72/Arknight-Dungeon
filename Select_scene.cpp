#include "Select_scene.h"
#include "tool.h" // ����outtextxy_shaded
#include <iostream>

// �ⲿ��������
extern Scene_manager scene_manager;
extern Player* player_1;
extern Player* player_2;

void SelectScene::on_load() {
    // �����߼�
}

void SelectScene::on_update(int delta) {
    // �����߼�
}

void SelectScene::on_render(const Camera& camera) {
    std::cout << "Rendering Select Scene..." << std::endl;
    outtextxy_shaded(10, 10, _T("Select Scene is rendering..."));

    for (int i = 0; i <= 1280; i += 50) {
        for (int j = 0; j <= 720; j += 50) {
            outtextxy(i, j, _T("a")); // ��Ⱦ�ַ� 'a'
        }
    }
}

void SelectScene::on_unload() {
    // ��ж�س���ʱ������Ҷ���
    switch (player_type_1) {
    case PlayerType::Amiya:
        player_1 = new Amiya(); // ����Amiya��Ҷ���
        break;
    case PlayerType::Hei:
        player_1 = new Hei(); // ����Hei��Ҷ���
        break;
    default:
        // ������Ч���ͣ���������Ĭ��ֵ���׳��쳣
        player_1 = new Amiya();
        break;
    }

    player_1->set_id(Player::PlayerId::P1); // �������ID

    // �����ڶ�����Ҷ���
    player_2 = new Amiya();
    player_2->set_id(Player::PlayerId::P2);
}

void SelectScene::on_event(const ExMessage& msg) {
    if (msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {
        case 'A':
            is_player1_left_down = true; // ��Ұ������
            break;
        case 'D':
            is_player1_right_down = true; // ��Ұ����Ҽ�
            break;
        case VK_SPACE:
            std::cout << "Switching to Game Scene..." << std::endl;
            scene_manager.switch_to(Scene_manager::SceneType::Game); // �л�����Ϸ����
            break;
        default:
            break;
        }
    }
    else if (msg.message == WM_KEYUP) {
        switch (msg.vkcode) {
        case 'A':
            is_player1_left_down = false; // ����ɿ����
            // ����ɿ�ʱ�л�����һ����ɫ
            player_type_1 = static_cast<PlayerType>(
                (static_cast<int>(player_type_1) - 1 + static_cast<int>(PlayerType::Invalid)
                    ) % static_cast<int>(PlayerType::Invalid));
            break;
        case 'D':
            is_player1_right_down = false; // ����ɿ��Ҽ�
            // �Ҽ��ɿ�ʱ�л�����һ����ɫ
            player_type_1 = static_cast<PlayerType>(
                (static_cast<int>(player_type_1) + 1) % static_cast<int>(PlayerType::Invalid)
                );
            break;
        default:
            break;
        }
    }
}