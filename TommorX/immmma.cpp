#include "immmma.h"
#pragma comment(lib,"Winmm.LIB")
#include <vector>
#include <iostream>
#include <graphics.h>
#include <map>
#include <array>
#include "Atlas.h"
#include "tool.h"
#include "Platform.h"
#include "Player.h"
#include "Map.h"
#include "Room.h"



IMAGE background;

// character
Atlas Amiya_right_move; // Aimiya���ƶ���
Atlas Amiya_left_move;  // Aimiya���ƶ���
Atlas Amiya_right_idle; // Aimiya�Ҵ�������
Atlas Amiya_left_idle;  // Aimiya���������
Atlas Amiya_right_attack; // Aimiya�ҹ�������
Atlas Amiya_left_attack;  // Aimiya�󹥻�����


Atlas Hei_right_move;   // Hei���ƶ���
Atlas Hei_left_move;    // Hei���ƶ���
Atlas Hei_right_idle;   // Hei�Ҵ�������
Atlas Hei_left_idle;    // Hei���������


Atlas B1_idle_right;
Atlas B1_idle_left;
Atlas B1_move_right;
Atlas B1_move_left;
Atlas B1_right_Attack;
Atlas B1_left_Attack;

Atlas B2_idle_right;
Atlas B2_idle_left;
Atlas B2_move_right;
Atlas B2_move_left;
Atlas B2_right_attack;
Atlas B2_left_attack;



// item
IMAGE img_dust;
IMAGE img_crystal;
IMAGE img_stone;
IMAGE img_machine;

// platform
std::vector<Platform> platform_list; // ƽ̨�б�

// Player
Player* player_1 = nullptr; // ��Ҷ���
Player* player_2 = nullptr; // ��Ҷ���

int background_pixel = 480; // ����ͼƬ���ش�С
int block_pixel = (int)((double)background_pixel / 8); // ��ͼ�����ش�С
int item_pixel = (int)((double)background_pixel / 8); // ��ƷͼƬ���ش�С

// ��Դ���غ���ʵ��
void load_game_resources() {
    loadimage(&background, _T("Image/res/bw.png"), background_pixel, background_pixel, 1); // ���ر���ͼƬ

    Amiya_right_move.add_image(_T("Image/amiya/%d@0.5x.png"), 10, 300, 300, 1); // ����Amiya����ͼƬ
    flip_Atlas(Amiya_right_move, Amiya_left_move); // ��תAmiya����ͼƬΪ����
    Amiya_right_idle.add_image(_T("Image/amiya/idle/ͼ�� %d.png"), 9, 300, 300, 1); // ����Amiya����ͼƬ
    flip_Atlas(Amiya_right_idle, Amiya_left_idle); // ��תAmiya����ͼƬΪ����
    Amiya_right_attack.add_image(_T("Image/amiya/attack/ͼ�� %d.png"), 9, 300, 300, 1); // ����Amiya����ͼƬ
    flip_Atlas(Amiya_right_attack, Amiya_left_attack); // ��תAmiya����ͼƬΪ����

    loadimage(&img_dust, _T("Image/item/dust.png"), item_pixel, item_pixel, 1); // ���ػҳ�ͼƬ
    loadimage(&img_crystal, _T("Image/item/crystal.png"), item_pixel, item_pixel, 1); // ���ؾ���ͼƬ
    loadimage(&img_stone, _T("Image/item/stone.png"), item_pixel, item_pixel, 1); // ����ʯͷͼƬ
    loadimage(&img_machine, _T("Image/item/machine.png"), item_pixel, item_pixel, 1); // ���ػ���ͼƬ

    B1_idle_right.add_image(_T("Image/B1/B1_Attack_%d.png"), 3, 60, 60, 1); // ����B1�Ҵ���ͼƬ
    flip_Atlas(B1_idle_right, B1_idle_left); // ��תB1�Ҵ���ͼƬΪ�����
    B1_move_right.add_image(_T("Image/B1/B1_Move_%d.png"), 3, 60, 60, 1); // ����B1���ƶ�ͼƬ
    flip_Atlas(B1_move_right, B1_move_left); // ��תB1���ƶ�ͼƬΪ���ƶ�

    B2_idle_right.add_image(_T("Image/B2/idle/B2_idle_%d.png"), 12,120,120,1); // ����B2�Ҵ���ͼƬ
    flip_Atlas(B2_idle_right, B2_idle_left); // ��תB2�Ҵ���ͼƬΪ�����

    B2_move_right.add_image(_T("Image/B2/move/B2_move_%d.png"), 12, 120, 120, 1); // ����B2���ƶ�ͼƬ
    flip_Atlas(B2_move_right, B2_move_left); // ��תB2���ƶ�ͼƬΪ���ƶ�
        
    B2_right_attack.add_image(_T("Image/B2/attack/B2_attack_%d.png"), 15, 120, 120,1); // ����B2����ͼƬ
    flip_Atlas(B2_right_attack, B2_left_attack);
    

    //Sound
    mciSendString(_T("open Sound/finish_01.wav type waveaudio alias Next_level"), NULL, 0, NULL);//��һ����Ч

}

// map
std::map<int, Room> room_map; // �����ͼӳ��

// 0 �� 1 ǽ 2 �ҳ� 3 ���� 4 ʯͷ
std::vector<std::array<std::array<int, 8>, 8>> room_map_data = {
    std::array<std::array<int, 8>, 8>{ // Room 1
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 2, 2, 99, 2, 0, 1},
        std::array<int, 8>{0, 0, 2, 1, 3, 2, 0, 0},
        std::array<int, 8>{0, 0, 2, 3, 1, 2, 0, 0},
        std::array<int, 8>{1, 0, 99, 3, 2, 2, 0, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 3, 0, 1},
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1, 1}
    },
    std::array<std::array<int, 8>, 8>{ // Room 2
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1, 1},
        std::array<int, 8>{1, 1, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 2, 2, 2, 2, 0, 1},
        std::array<int, 8>{0, 0, 2, 0, 3, 2, 99, 0},
        std::array<int, 8>{0, 2, 2, 3, 0, 2, 0, 0},
        std::array<int, 8>{1, 0, 99, 2, 2, 0, 2, 1},
        std::array<int, 8>{1, 3, 0, 0, 0, 3, 0, 1},
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1, 1}
    },
    std::array<std::array<int, 8>, 8>{ // Room 3
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1,  1},
        std::array<int, 8>{1, 0, 0, 0, 99, 0, 0, 1},
        std::array<int, 8>{1, 0, 0, 2, 0, 2, 0,  1},
        std::array<int, 8>{0, 0, 2, 0, 3, 0, 0,  0},
        std::array<int, 8>{0, 0, 99, 3, 0, 2, 0, 0},
        std::array<int, 8>{1, 0, 2, 2, 0, 2, 0,  1},
        std::array<int, 8>{1, 0, 0, 0, 0, 99, 0, 1},
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1,  1}
    },
    std::array<std::array<int, 8>, 8>{ // Room 4
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1, 1},
        std::array<int, 8>{1, 787, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 1, 1, 1, 1, 0, 1},
        std::array<int, 8>{0, 99, 1, 1, 1, 1, 0, 0},
        std::array<int, 8>{0, 0, 1, 1, 1, 1, 0, 0},
        std::array<int, 8>{1, 0, 1, 1, 1, 1, 0, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 99, 1},
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1, 1}
    }
};

std::vector<std::array<std::array<int, 8>, 8>> exit_map_data = {
    std::array<std::array<int, 8>, 8>{
        std::array<int,8> {1,1,1,0,0,1,1,1},
        std::array<int, 8>{1, 1, 1, 0, 0, 1, 1, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 2, 2, 99, 2, 0, 1},
        std::array<int, 8>{0, 99, 2, 88, 3, 2, 0, 0},
        std::array<int, 8>{0, 0, 2, 3, 1, 2, 0, 0},
        std::array<int, 8>{1, 0, 99, 3, 2, 2, 99, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 3, 0, 1}
}
};
