#pragma once
#include <graphics.h>
#include "Animation.h"
#include "tool.h"
#include <map>
#include <array>
#include "Camera.h"
#include "immmma.h"
#include "Room.h"

static const int  MAP_WIDTH = 5; //地图房间宽数
static const int MAP_HIGHT= 5; //地图房间高数
extern std::map<int, Room> room_map;//房间地图映射
extern IMAGE background; //背景图片
extern int background_pixel; //背景图片像素大小

class Map {
private:
	int tile_size = background_pixel; //地图格子大小
	std::array<std::array<int,MAP_WIDTH>,MAP_HIGHT> room; //地图房间数据

public:
	~Map() = default; //默认析构函数
	Map() {
		for (int i = 0; i < MAP_WIDTH; i++) {
			for (int j = 0; j < MAP_HIGHT; j++) {
				room[i][j] = RandomRange(0, 3); //初始化地图房间数据
			}
		}
	}

	void map_genegrate(){
		for (int i = 0; i < MAP_WIDTH; i++) {
			for(int j=0;j< MAP_HIGHT; j++) {
				 room[i][j] = RandomRange(0,3); //地图池随机选择
			}
		}
	}

	void map_render(const Camera& camera) {
		for (int i = 0; i < MAP_WIDTH; i++) {
			for (int j = 0; j < MAP_HIGHT; j++) {
				room_map[room[i][j]].room_draw(i * tile_size, j * tile_size,camera); //渲染地图房间
			}
		}
	}


};


