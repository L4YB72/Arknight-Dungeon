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
Atlas Amiya_right_move; // Aimiya右移动画
Atlas Amiya_left_move;  // Aimiya左移动画
Atlas Amiya_right_idle; // Aimiya右待机动画
Atlas Amiya_left_idle;  // Aimiya左待机动画
Atlas Amiya_right_attack; // Aimiya右攻击动画
Atlas Amiya_left_attack;  // Aimiya左攻击动画


Atlas Hei_right_move;   // Hei右移动画
Atlas Hei_left_move;    // Hei左移动画
Atlas Hei_right_idle;   // Hei右待机动画
Atlas Hei_left_idle;    // Hei左待机动画


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
std::vector<Platform> platform_list; // 平台列表

// Player
Player* player_1 = nullptr; // 玩家对象
Player* player_2 = nullptr; // 玩家对象

int background_pixel = 480; // 背景图片像素大小
int block_pixel = (int)((double)background_pixel / 8); // 地图块像素大小
int item_pixel = (int)((double)background_pixel / 8); // 物品图片像素大小

// 资源加载函数实现
void load_game_resources() {
    loadimage(&background, _T("Image/res/bw.png"), background_pixel, background_pixel, 1); // 加载背景图片

    Amiya_right_move.add_image(_T("Image/amiya/%d@0.5x.png"), 10, 300, 300, 1); // 加载Amiya右移图片
    flip_Atlas(Amiya_right_move, Amiya_left_move); // 翻转Amiya右移图片为左移
    Amiya_right_idle.add_image(_T("Image/amiya/idle/图层 %d.png"), 9, 300, 300, 1); // 加载Amiya右移图片
    flip_Atlas(Amiya_right_idle, Amiya_left_idle); // 翻转Amiya右移图片为左移
    Amiya_right_attack.add_image(_T("Image/amiya/attack/图层 %d.png"), 9, 300, 300, 1); // 加载Amiya右移图片
    flip_Atlas(Amiya_right_attack, Amiya_left_attack); // 翻转Amiya右移图片为左移

    loadimage(&img_dust, _T("Image/item/dust.png"), item_pixel, item_pixel, 1); // 加载灰尘图片
    loadimage(&img_crystal, _T("Image/item/crystal.png"), item_pixel, item_pixel, 1); // 加载晶体图片
    loadimage(&img_stone, _T("Image/item/stone.png"), item_pixel, item_pixel, 1); // 加载石头图片
    loadimage(&img_machine, _T("Image/item/machine.png"), item_pixel, item_pixel, 1); // 加载机器图片

    B1_idle_right.add_image(_T("Image/B1/B1_Attack_%d.png"), 3, 60, 60, 1); // 加载B1右待机图片
    flip_Atlas(B1_idle_right, B1_idle_left); // 翻转B1右待机图片为左待机
    B1_move_right.add_image(_T("Image/B1/B1_Move_%d.png"), 3, 60, 60, 1); // 加载B1右移动图片
    flip_Atlas(B1_move_right, B1_move_left); // 翻转B1右移动图片为左移动

    B2_idle_right.add_image(_T("Image/B2/idle/B2_idle_%d.png"), 12,120,120,1); // 加载B2右待机图片
    flip_Atlas(B2_idle_right, B2_idle_left); // 翻转B2右待机图片为左待机

    B2_move_right.add_image(_T("Image/B2/move/B2_move_%d.png"), 12, 120, 120, 1); // 加载B2右移动图片
    flip_Atlas(B2_move_right, B2_move_left); // 翻转B2右移动图片为左移动
        
    B2_right_attack.add_image(_T("Image/B2/attack/B2_attack_%d.png"), 15, 120, 120,1); // 加载B2攻击图片
    flip_Atlas(B2_right_attack, B2_left_attack);
    

    //Sound
    mciSendString(_T("open Sound/finish_01.wav type waveaudio alias Next_level"), NULL, 0, NULL);//下一关音效

}

// map
std::map<int, Room> room_map; // 房间地图映射

// 0 空 1 墙 2 灰尘 3 机器 4 石头
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
