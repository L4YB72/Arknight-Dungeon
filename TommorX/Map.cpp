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



extern std::map<int, Room> room_map;//�����ͼӳ��
extern IMAGE background; //����ͼƬ
extern int background_pixel; //����ͼƬ���ش�С
extern bool is_debug;



Map:: ~Map() = default; //Ĭ����������

    Map::Map() {
        for (int room_x = 0; room_x < MAP_WIDTH / 8; room_x++) {
            for (int room_y = 0; room_y < MAP_HIGHT / 8; room_y++) {
                int room_id = RandomRange(0, 3); // ���ѡ�񷿼�ID
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
                case 0: // �յ�
                    break;
                case 1: // ǽ��ʯͷ
                    putimage_alpha(draw_x, draw_y, &img_stone);
                    break;
                case 2: // ����
                    putimage_alpha(draw_x, draw_y, &img_machine);
                    break;
                case 3: // �ҳ�
                    putimage_alpha(draw_x, draw_y, &img_dust);
                    break;
                case 4: // ʯͷ
                    putimage_alpha(draw_x, draw_y, &img_stone);
                    break;
                case 88:
                    outtextxy(draw_x, draw_y, _T("EXIT"));
                    break;
                case 787://chese
                    outtextxy(draw_x, draw_y, _T("CHESE"));
                    break;
                }
                
                //outtextxy(draw_x + 10, draw_y + 10, std::to_string(move_map[i][j])); // ��ʾ���Ӷ�����
                if (is_debug) {
                    char c = '1' + move_map[i][j];
                    outtextxy(draw_x + 10, draw_y + 10, c); // ��ʾ���Ӷ�����
                }
            }
        }
    }

    void Map::on_update(int delta, Vector2 player) {
        bfs(player); // ���µ�ͼ����ͼ
    }

    std::vector<std::vector<int>> Map::bfs(const Vector2& player) {
        // ��ʼ���������飬���и��ӵĴ��۳�ʼ��Ϊ���ֵ
        std::vector<std::vector<int>> cost_map(MAP_WIDTH, std::vector<int>(MAP_HIGHT, INT_MAX));

        // ���г�ʼ��
        std::queue<Vector2> queue;
        queue.push(player); // ����ҵ�ǰλ�ÿ�ʼ
        cost_map[player.x][player.y] = 0;  // �������λ�õĴ���Ϊ0

        // �������飬�����ƶ���������
        const std::vector<Vector2> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        // ��ʼBFS
        while (!queue.empty()) {
            Vector2 current = queue.front();
            queue.pop();

            // �����ĸ�����
            for (const auto& dir : directions) {
                Vector2 next(current.x + dir.x, current.y + dir.y);

                // ����Ƿ�Խ��
                if (next.x >= 0 && next.x < MAP_WIDTH && next.y >= 0 && next.y < MAP_HIGHT) {
                    // ����ǿ�ͨ����������δ���¹�����
                    if (map_data[next.x][next.y] != 1 && cost_map[next.x][next.y] == INT_MAX) {
                        cost_map[next.x][next.y] = cost_map[current.x][current.y] + 1;
                        queue.push(next); // ����λ�ü������
                    }
                }
            }
        }

        move_map = (cost_map);

        return cost_map; // ����������ͼ�Ĵ���ͼ
    }

    int Map::get_object(int x, int y) const {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HIGHT) {
            return map_data[x][y]; // ����ָ��λ�õĵ�ͼ����
        }
        return -1; // ���Խ�磬����-1
    }
    int Map::get_object(Vector2 block) const {
		int x = block.x;
		int y = block.y;
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HIGHT) {
            return map_data[x][y]; // ����ָ��λ�õĵ�ͼ����
        }
        return -1; // ���Խ�磬����-1
    }


    void Map::edit(Vector2 block, int val) {
		map_data[block.x][block.y] = val; // �޸�ָ��λ�õĵ�ͼ����
    }
    void Map::edit(int x, int y, int val) {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HIGHT) {
            map_data[x][y] = val; // �޸�ָ��λ�õĵ�ͼ����
        }
    }