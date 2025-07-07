#pragma once
#include <graphics.h>
#include "Animation.h"
#include "tool.h"
#include <map>
#include <array>
#include "Camera.h"
#include "immmma.h"
#include "Room.h"

static const int  MAP_WIDTH = 5; //��ͼ�������
static const int MAP_HIGHT= 5; //��ͼ�������
extern std::map<int, Room> room_map;//�����ͼӳ��
extern IMAGE background; //����ͼƬ
extern int background_pixel; //����ͼƬ���ش�С

class Map {
private:
	int tile_size = background_pixel; //��ͼ���Ӵ�С
	std::array<std::array<int,MAP_WIDTH>,MAP_HIGHT> room; //��ͼ��������

public:
	~Map() = default; //Ĭ����������
	Map() {
		for (int i = 0; i < MAP_WIDTH; i++) {
			for (int j = 0; j < MAP_HIGHT; j++) {
				room[i][j] = RandomRange(0, 3); //��ʼ����ͼ��������
			}
		}
	}

	void map_genegrate(){
		for (int i = 0; i < MAP_WIDTH; i++) {
			for(int j=0;j< MAP_HIGHT; j++) {
				 room[i][j] = RandomRange(0,3); //��ͼ�����ѡ��
			}
		}
	}

	void map_render(const Camera& camera) {
		for (int i = 0; i < MAP_WIDTH; i++) {
			for (int j = 0; j < MAP_HIGHT; j++) {
				room_map[room[i][j]].room_draw(i * tile_size, j * tile_size,camera); //��Ⱦ��ͼ����
			}
		}
	}


};


