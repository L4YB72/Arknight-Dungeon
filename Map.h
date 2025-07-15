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
extern std::map<int, Room> room_map;//�����ͼӳ��
extern IMAGE background; //����ͼƬ
extern int background_pixel; //����ͼƬ���ش�С
extern bool is_debug;

class Map {
private:
	int tile_size = background_pixel; //��ͼ���Ӵ�С
	std::array<std::array<int,MAP_WIDTH>,MAP_HIGHT> map_data; //��ͼ��������
   
 


public:
	~Map(); //Ĭ����������

    Map();

	std::vector<std::vector<int>> move_map; // ��ͼ��ά���飨0 ��ͨ�У�1 ����ͨ�У�
	
    void map_render(const Camera& camera);

    void on_update(int delta, Vector2 player);

    std::vector<std::vector<int>> bfs(const Vector2& player);
	
	int get_object(int x, int y) const;
	int get_object(Vector2 block) const;
	void edit(Vector2 block, int val);
	void edit(int x, int y, int val);

	

}; 

