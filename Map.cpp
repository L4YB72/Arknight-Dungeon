 #pragma once
#include <graphics.h>
#include "Animation.h"
#include "tool.h"
#include <map>
#include <array>
#include <queue>
#include <vector>
#include <limits.h>
#include <string>
#include "Camera.h"
#include "immmma.h"
#include "Room.h"
#include "Vector2.h"



extern std::map<int, Room> room_map;//房间地图映射
extern IMAGE background; //背景图片
extern int background_pixel; //背景图片像素大小
extern bool is_debug;



Map:: ~Map() = default; //默认析构函数

    Map::Map() {
        for (int room_x = 0; room_x < MAP_WIDTH / 8; room_x++) {
            for (int room_y = 0; room_y < MAP_HIGHT / 8; room_y++) {
                int room_id = RandomRange(0, 3); // 随机选择房间ID
                Room& room = room_map[room_id];
                for (int block_x = 0; block_x < 8; block_x++) {
                    for (int block_y = 0; block_y < 8; block_y++) {
                        int global_x = room_x * 8 + block_x;
                        int global_y = room_y * 8 + block_y;
                        map_data[global_x][global_y] = room.room_block_object( block_y,block_x);
                    }
                }
            }
        } 
        for (int i = 0,  j = 0; j < MAP_WIDTH; j++)
            map_data[i][j] = 1;
        for (int i = MAP_HIGHT-1 ,  j = 0; j < MAP_WIDTH;j++)
            map_data[i][j] = 1;
        for (int i = 0,  j = 0; i < MAP_WIDTH; i++)
            map_data[i][j] = 1;
        for (int i = 0,  j = MAP_WIDTH-1; i < MAP_HIGHT; i++)
            map_data[i][j] = 1;


        int ex, ey;
        ey = RandomRange(0, MAP_HIGHT - 1);
        ex = RandomRange(0, MAP_WIDTH - 1);
        while (get_object(ex, ey) == 1) {
            ey = RandomRange(0, MAP_HIGHT - 1);
            ex = RandomRange(0, MAP_WIDTH - 1);
        }
        map_data[ex][ey] = 88;


        
		

        
    }



    void Map::map_render(const Camera& camera) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            for (int j = 0; j < MAP_HIGHT; j++) {
                int obj = map_data[i][j];/*
                int pixel_delta_x = (background_pixel / 8 - item_pixel) / 2 + 2;
                int pixel_delta_y = (background_pixel / 8 - item_pixel) / 2 + 2 - camera.get_poisition().y;*/
                int draw_x = i * (background_pixel / 8) - camera.get_poisition().x;
                int draw_y = j * (background_pixel / 8) - camera.get_poisition().y;
                switch (obj) {
                case 0: // 空地
                    break;
                case 1: // 墙或石头
                    putimage_alpha(draw_x, draw_y, &img_stone);
                    break;
                case 2: // 机器
                    putimage_alpha(draw_x, draw_y, &img_machine);
                    break;
                case 3: // 灰尘
                    putimage_alpha(draw_x, draw_y, &img_dust);
                    break;
                case 4: // 石头
                    putimage_alpha(draw_x, draw_y, &img_stone);
                    break;
                case 88:
                    outtextxy(draw_x, draw_y, _T("EXIT"));
                    break;
                case 787://chese
                    outtextxy(draw_x, draw_y, _T("CHESE"));
                    break;
                }
                
                //outtextxy(draw_x + 10, draw_y + 10, std::to_string(move_map[i][j])); // 显示格子对象编号
                if (is_debug) {
                    char c = '1' + move_map[i][j];
                    outtextxy(draw_x + 10, draw_y + 10, c); // 显示格子对象编号
                }
            }
        }
    }

    void Map::on_update(int delta, Vector2 player) {
        bfs(player); // 更新地图代价图
    }

    std::vector<std::vector<int>> Map::bfs(const Vector2& player) {
        // 初始化代价数组，所有格子的代价初始化为最大值
        std::vector<std::vector<int>> cost_map(MAP_WIDTH, std::vector<int>(MAP_HIGHT, INT_MAX));

        // 队列初始化
        std::queue<Vector2> queue;
        queue.push(player); // 从玩家当前位置开始
        cost_map[player.x][player.y] = 0;  // 玩家所在位置的代价为0

        // 方向数组，用于移动上下左右
        const std::vector<Vector2> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        // 开始BFS
        while (!queue.empty()) {
            Vector2 current = queue.front();
            queue.pop();

            // 遍历四个方向
            for (const auto& dir : directions) {
                Vector2 next(current.x + dir.x, current.y + dir.y);

                // 检查是否越界
                if (next.x >= 0 && next.x < MAP_WIDTH && next.y >= 0 && next.y < MAP_HIGHT) {
                    // 如果是可通行区域且尚未更新过代价
                    if (map_data[next.x][next.y] != 1 && cost_map[next.x][next.y] == INT_MAX) {
                        cost_map[next.x][next.y] = cost_map[current.x][current.y] + 1;
                        queue.push(next); // 将新位置加入队列
                    }
                }
            }
        }

        move_map = (cost_map);

        return cost_map; // 返回整个地图的代价图
    }

    int Map::get_object(int x, int y) const {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HIGHT) {
            return map_data[x][y]; // 返回指定位置的地图对象
        }
        return -1; // 如果越界，返回-1
    }
    int Map::get_object(Vector2 block) const {
		int x = block.x;
		int y = block.y;
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HIGHT) {
            return map_data[x][y]; // 返回指定位置的地图对象
        }
        return -1; // 如果越界，返回-1
    }


    void Map::edit(Vector2 block, int val) {
		map_data[block.x][block.y] = val; // 修改指定位置的地图对象
    }
    void Map::edit(int x, int y, int val) {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HIGHT) {
            map_data[x][y] = val; // 修改指定位置的地图对象
        }
    }