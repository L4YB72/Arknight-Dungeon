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
static Atlas Amiya_right_move;// Aimiya右移动画
static Atlas Amiya_left_move;// Aimiya左移动画
static Atlas Amiya_right_idle;// Aimiya右待机动画
static Atlas Amiya_left_idle;// Aimiya左待机动画

static Atlas Hei_right_move;// Aimiya右移动画
static Atlas Hei_left_move;// Aimiya左移动画
static Atlas Hei_right_idle;// Aimiya右待机动画
static Atlas Hei_left_idle;// Aimiya左待机动画




//item
static IMAGE img_dust;
static IMAGE img_crystal;
static IMAGE img_stone;
static IMAGE img_machine;



//platform
static std::vector<Platform> platform_list; //平台列表

//Player
static Player* player_1 = nullptr; //玩家对象
static Player* player_2 = nullptr; //玩家对象






static int background_pixel = 480; //背景图片像素大小
static int block_pixel = (int)((double)background_pixel / 8); //地图块像素大小
static int item_pixel = (int)((double)background_pixel / 8); //物品图片像素大小
inline void load_game_resources() {
	loadimage(&background, _T("Image/res/bw.png"),background_pixel,background_pixel,1); //加载背景图片

	Amiya_right_move.add_image(_T("Image/amiya/%d@0.5x.png"), 10,300,300,1); //加载Amiya右移图片
	flip_Atlas(Amiya_right_move, Amiya_left_move); //翻转Amiya右移图片为左移

	loadimage(&img_dust, _T("Image/item/dust.png"), item_pixel, item_pixel, 1); //加载灰尘图片
	loadimage(&img_crystal, _T("Image/item/crystal.png"), item_pixel, item_pixel, 1); //加载晶体图片
	loadimage(&img_stone, _T("Image/item/stone.png"), item_pixel, item_pixel, 1); //加载石头图片
	loadimage(&img_machine, _T("Image/item/machine.png"), item_pixel, item_pixel, 1); //加载机器图片



}




//map
static std::map<int, Room> room_map;//房间地图映射


//0 空 1 墙 2 灰尘 3 机器 4 石头
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