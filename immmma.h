#pragma once
#pragma comment(lib,"Winmm.LIB")
#include <windows.h>
#include <mmsystem.h>
#include "Player.h"
#include <vector>
#include <iostream>
#include <graphics.h>
#include <map>
#include <array>
#include "Atlas.h"
#include "tool.h"
#include "Platform.h"
#include "Map.h"
#include "Room.h"

// ȫ����Դ����
extern IMAGE background;

// character
extern Atlas Amiya_right_move; // Aimiya���ƶ���
extern Atlas Amiya_left_move;  // Aimiya���ƶ���
extern Atlas Amiya_right_idle; // Aimiya�Ҵ�������
extern Atlas Amiya_left_idle;  // Aimiya���������

extern Atlas Hei_right_move;   // Hei���ƶ���
extern Atlas Hei_left_move;    // Hei���ƶ���
extern Atlas Hei_right_idle;   // Hei�Ҵ�������
extern Atlas Hei_left_idle;    // Hei���������

extern IMAGE img_B1;
extern Atlas B1_idle_right;
extern Atlas B1_idle_left;
extern Atlas B1_move_right;
extern Atlas B1_move_left;
extern Atlas B1_Attack;

// item
extern IMAGE img_dust;
extern IMAGE img_crystal;
extern IMAGE img_stone;
extern IMAGE img_machine;

// platform
extern std::vector<Platform> platform_list; // ƽ̨�б�

//// Player

extern int background_pixel; // ����ͼƬ���ش�С
extern int block_pixel;      // ��ͼ�����ش�С
extern int item_pixel;       // ��ƷͼƬ���ش�С



// ��Դ���غ�������
void load_game_resources();

// map
extern std::map<int, Room> room_map; // �����ͼӳ��

// 0 �� 1 ǽ 2 �ҳ� 3 ���� 4 ʯͷ
extern std::vector<std::array<std::array<int, 8>, 8>> room_map_data;