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

// 全局资源声明
extern IMAGE background;

// character
extern Atlas Amiya_right_move; // Aimiya右移动画
extern Atlas Amiya_left_move;  // Aimiya左移动画
extern Atlas Amiya_right_idle; // Aimiya右待机动画
extern Atlas Amiya_left_idle;  // Aimiya左待机动画

extern Atlas Hei_right_move;   // Hei右移动画
extern Atlas Hei_left_move;    // Hei左移动画
extern Atlas Hei_right_idle;   // Hei右待机动画
extern Atlas Hei_left_idle;    // Hei左待机动画

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
extern std::vector<Platform> platform_list; // 平台列表

//// Player

extern int background_pixel; // 背景图片像素大小
extern int block_pixel;      // 地图块像素大小
extern int item_pixel;       // 物品图片像素大小



// 资源加载函数声明
void load_game_resources();

// map
extern std::map<int, Room> room_map; // 房间地图映射

// 0 空 1 墙 2 灰尘 3 机器 4 石头
extern std::vector<std::array<std::array<int, 8>, 8>> room_map_data;