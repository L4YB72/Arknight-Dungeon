#pragma once
#include "graphics.h"
#include "immmma.h"
#include <map>
#include <array>


enum class Object {
	empty = 0,
	wall,
	dust,
	machine,
	stone,

};


extern IMAGE background;//背景图片
extern IMAGE img_dust;
extern IMAGE img_crystal;
extern IMAGE img_stone;
extern IMAGE img_machine;
extern int background_pixel; //背景图片像素大小
extern int item_pixel; //物品图片像素大小

class Room {
private:
	int tile_size = background_pixel/8;
	int block_num = 8;
	std::array<std::array<int,8>,8> room_data; //房间格子数据
	int species = 0;

public:
	Room() = default;
	~Room() = default;
	Room(std::array<std::array<int,8>,8> data) {
		for (int i = 0; i < block_num; i++) {
			for (int j = 0; j < block_num; j++) {
				room_data[i][j] = data[i][j]; //构造房间格子数据
			}
		}
	}

	void room_draw(int room_poi_x, int room_poi_y,const Camera& camera) {
		for (int i = 0; i < block_num; i++) {
			for (int j = 0; j < block_num; j++) {
				int pixel_delta_x =  (background_pixel / 8 - item_pixel) / 2+2-camera.get_poisition().x; //计算像素偏移量
				int pixel_delta_y =  (background_pixel / 8 - item_pixel) / 2+2-camera.get_poisition().y; //计算像素偏移量
				switch (room_data[i][j]) {
				case 0: //空格
					break;
				case 1: //墙
					putimage_alpha(room_poi_x + i * tile_size+pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_stone); //渲染石头图片
					break;
				case 2: //机器
					putimage_alpha(room_poi_x + i * tile_size + pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_machine); //渲染机器图片
					break;
				case 3: //灰尘
					putimage_alpha(room_poi_x + i * tile_size + pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_dust); //渲染灰尘图片
					break;
				case 4: //石头
					putimage_alpha(room_poi_x + i * tile_size + pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_stone); //渲染石头图片
					break;
				}
			}
		}
	}

};



extern std::vector<std::array<std::array<int, 8>, 8> > room_map_data; //房间数据
extern std::map<int, Room> room_map;//房间地图映射
const int map_num = 4;//地图房间数量

inline void room_map_generate() {
	for (int i = 0; i < map_num; i++) {
		room_map.insert({ i, Room(std::array<std::array<int, 8>, 8>(room_map_data[i])) }); //插入房间数据到房间映射
	}
}

