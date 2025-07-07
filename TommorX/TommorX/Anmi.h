//#pragma once
//#include <graphics.h>
//#include <vector>
//#include <iostream>
//#include "Camera.h"
//extern void putimage_alpha(int x, int y, IMAGE* img);
//extern void load_background(const IMAGE& img_background);
//extern void DrawAmiya(int x, int y, int delta);
//
//
//struct Animate {
//	//private
//	std::vector<IMAGE*> frame_list; //����֡����
//	DWORD interval_ms ;//֡���
//	DWORD timer = 0;//��ʱ��
//	int idx_frame = 0;//��ǰ֡����
//
//	//public
//	Animate(LPCTSTR path, int num, DWORD interval) {
//		interval_ms = interval;
//
//		TCHAR path_file[256];
//		for (size_t i = 0; i < num; i++) {
//			_stprintf_s(path_file, path, i);
//			IMAGE* frame = new IMAGE();
//			loadimage(frame, path_file);
//			frame_list.push_back(frame);
//		}
//	}
//	Animate(const std::vector<IMAGE*>& frames, DWORD interval) {
//		frame_list = frames;
//		interval_ms = interval;
//	}
//
//	~Animate() {
//		for (size_t i = 0; i < frame_list.size(); i++) {
//			delete frame_list[i];
//		}
//	}
//
//	void Play(int x, int y, DWORD delta) {
//		timer += delta;
//		std::cout << delta<<std::endl;
//		if (timer >= interval_ms) {
//			idx_frame = (++idx_frame) % frame_list.size();
//			timer = 0;
//		}
//
//		putimage_alpha(x, y, frame_list[idx_frame]);
//
//	}
//
//};
//void DrawAnimation();
//
////extern struct Amiya