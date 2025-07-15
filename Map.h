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



constexpr int MAP_WIDTH = 40;
constexpr int MAP_HIGHT = 40;
extern std::map<int, Room> room_map;//房间地图映射
extern IMAGE background; //背景图片
extern int background_pixel; //背景图片像素大小
extern bool is_debug;

class Map {
private:
	int tile_size = background_pixel; //地图格子大小
	std::array<std::array<int,MAP_WIDTH>,MAP_HIGHT> map_data; //地图房间数据
   
 


public:
	~Map(); //默认析构函数

    Map();

	std::vector<std::vector<int>> move_map; // 地图二维数组（0 可通行，1 不可通行）
	
    void map_render(const Camera& camera);

    void on_update(int delta, Vector2 player);

    std::vector<std::vector<int>> bfs(const Vector2& player);
	
	int get_object(int x, int y) const;
	int get_object(Vector2 block) const;
	void edit(Vector2 block, int val);
	void edit(int x, int y, int val);

	

}; 

