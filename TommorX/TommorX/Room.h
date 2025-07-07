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


extern IMAGE background;//����ͼƬ
extern IMAGE img_dust;
extern IMAGE img_crystal;
extern IMAGE img_stone;
extern IMAGE img_machine;
extern int background_pixel; //����ͼƬ���ش�С
extern int item_pixel; //��ƷͼƬ���ش�С

class Room {
private:
	int tile_size = background_pixel/8;
	int block_num = 8;
	std::array<std::array<int,8>,8> room_data; //�����������
	int species = 0;

public:
	Room() = default;
	~Room() = default;
	Room(std::array<std::array<int,8>,8> data) {
		for (int i = 0; i < block_num; i++) {
			for (int j = 0; j < block_num; j++) {
				room_data[i][j] = data[i][j]; //���췿���������
			}
		}
	}

	void room_draw(int room_poi_x, int room_poi_y,const Camera& camera) {
		for (int i = 0; i < block_num; i++) {
			for (int j = 0; j < block_num; j++) {
				int pixel_delta_x =  (background_pixel / 8 - item_pixel) / 2+2-camera.get_poisition().x; //��������ƫ����
				int pixel_delta_y =  (background_pixel / 8 - item_pixel) / 2+2-camera.get_poisition().y; //��������ƫ����
				switch (room_data[i][j]) {
				case 0: //�ո�
					break;
				case 1: //ǽ
					putimage_alpha(room_poi_x + i * tile_size+pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_stone); //��ȾʯͷͼƬ
					break;
				case 2: //����
					putimage_alpha(room_poi_x + i * tile_size + pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_machine); //��Ⱦ����ͼƬ
					break;
				case 3: //�ҳ�
					putimage_alpha(room_poi_x + i * tile_size + pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_dust); //��Ⱦ�ҳ�ͼƬ
					break;
				case 4: //ʯͷ
					putimage_alpha(room_poi_x + i * tile_size + pixel_delta_x, room_poi_y + j * tile_size + pixel_delta_y, &img_stone); //��ȾʯͷͼƬ
					break;
				}
			}
		}
	}

};



extern std::vector<std::array<std::array<int, 8>, 8> > room_map_data; //��������
extern std::map<int, Room> room_map;//�����ͼӳ��
const int map_num = 4;//��ͼ��������

inline void room_map_generate() {
	for (int i = 0; i < map_num; i++) {
		room_map.insert({ i, Room(std::array<std::array<int, 8>, 8>(room_map_data[i])) }); //���뷿�����ݵ�����ӳ��
	}
}

