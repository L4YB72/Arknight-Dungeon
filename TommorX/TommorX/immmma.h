#pragma once
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
//

//
static IMAGE background;

//character
static Atlas Amiya_right_move;// Aimiya���ƶ���
static Atlas Amiya_left_move;// Aimiya���ƶ���
static Atlas Amiya_right_idle;// Aimiya�Ҵ�������
static Atlas Amiya_left_idle;// Aimiya���������

static Atlas Hei_right_move;// Aimiya���ƶ���
static Atlas Hei_left_move;// Aimiya���ƶ���
static Atlas Hei_right_idle;// Aimiya�Ҵ�������
static Atlas Hei_left_idle;// Aimiya���������




//item
static IMAGE img_dust;
static IMAGE img_crystal;
static IMAGE img_stone;
static IMAGE img_machine;



//platform
static std::vector<Platform> platform_list; //ƽ̨�б�

//Player
static Player* player_1 = nullptr; //��Ҷ���
static Player* player_2 = nullptr; //��Ҷ���






static int background_pixel = 480; //����ͼƬ���ش�С
static int block_pixel = (int)((double)background_pixel / 8); //��ͼ�����ش�С
static int item_pixel = (int)((double)background_pixel / 8); //��ƷͼƬ���ش�С
inline void load_game_resources() {
	loadimage(&background, _T("Image/res/bw.png"),background_pixel,background_pixel,1); //���ر���ͼƬ

	Amiya_right_move.add_image(_T("Image/amiya/%d@0.5x.png"), 10,300,300,1); //����Amiya����ͼƬ
	flip_Atlas(Amiya_right_move, Amiya_left_move); //��תAmiya����ͼƬΪ����

	loadimage(&img_dust, _T("Image/item/dust.png"), item_pixel, item_pixel, 1); //���ػҳ�ͼƬ
	loadimage(&img_crystal, _T("Image/item/crystal.png"), item_pixel, item_pixel, 1); //���ؾ���ͼƬ
	loadimage(&img_stone, _T("Image/item/stone.png"), item_pixel, item_pixel, 1); //����ʯͷͼƬ
	loadimage(&img_machine, _T("Image/item/machine.png"), item_pixel, item_pixel, 1); //���ػ���ͼƬ



}




//map
static std::map<int, Room> room_map;//�����ͼӳ��


//0 �� 1 ǽ 2 �ҳ� 3 ���� 4 ʯͷ
static std::vector<std::array<std::array<int, 8>, 8>> room_map_data = {
    std::array<std::array<int, 8>, 8>{ // Room 1
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 2, 2, 2, 2, 0, 1},
        std::array<int, 8>{1, 0, 2, 1, 3, 2, 0, 1},
        std::array<int, 8>{1, 0, 2, 3, 1, 2, 0, 1},
        std::array<int, 8>{1, 0, 2, 3, 2, 2, 0, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 3, 0, 1},
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1}
    },
    std::array<std::array<int, 8>, 8>{ // Room 2
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1},
        std::array<int, 8>{1, 1, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 2, 2, 2, 2, 0, 1},
        std::array<int, 8>{1, 0, 2, 0, 3, 2, 0, 1},
        std::array<int, 8>{1, 2, 2, 3, 0, 2, 0, 1},
        std::array<int, 8>{1, 0, 0, 2, 2, 0, 2, 1},
        std::array<int, 8>{1, 3, 0, 0, 0, 3, 0, 1},
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1}
    },
    std::array<std::array<int, 8>, 8>{ // Room 3
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 0, 2, 0, 2, 0, 1},
        std::array<int, 8>{1, 0, 2, 0, 3, 0, 0, 1},
        std::array<int, 8>{1, 0, 0, 3, 0, 2, 0, 1},
        std::array<int, 8>{1, 0, 2, 2, 0, 2, 0, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1}
    },
    std::array<std::array<int, 8>, 8>{ // Room 4
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 0, 1, 1, 1, 1, 0, 1},
        std::array<int, 8>{1, 0, 1, 1, 1, 1, 0, 1},
        std::array<int, 8>{1, 0, 1, 1, 1, 1, 0, 1},
        std::array<int, 8>{1, 0, 1, 1, 1, 1, 0, 1},
        std::array<int, 8>{1, 0, 0, 0, 0, 0, 0, 1},
        std::array<int, 8>{1, 1, 1, 1, 1, 1, 1, 1}
    }
};