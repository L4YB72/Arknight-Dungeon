//#include <graphics.h>
//#include "Amiya.h"
//
//
//bool is_move_up=false, is_move_down=false, is_move_left=false, is_move_right=false;
//extern Amiya amiya;
//
//void move_detact(const ExMessage& msg) {
//	if (msg.message == WM_KEYDOWN) {
//		switch (msg.vkcode) {
//		case('W'):is_move_up = true; break;
//		case('S'):is_move_down = true; break;
//		case('A'):is_move_left = true; break;
//		case('D'):is_move_right = true; break;
//		}
//	}
//	else if (msg.message == WM_KEYUP) {
//		switch (msg.vkcode) {
//		case('W'):is_move_up = false; break;
//		case('S'):is_move_down = false; break;
//		case('A'):is_move_left = false; break;
//		case('D'):is_move_right = false; break;
//		}
//	}
//
//}
//
//void move_activate() {
//	if (is_move_up)
//		amiya.y -= amiya.speed;
//	if (is_move_down)
//		amiya.y += amiya.speed;
//	if (is_move_left)
//		amiya.x -= amiya.speed;
//	if (is_move_right)
//		amiya.x += amiya.speed;
//}