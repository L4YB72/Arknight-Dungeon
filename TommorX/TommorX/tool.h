#pragma once
#include <graphics.h>
#include "Atlas.h"
#include "Camera.h"


// 翻转图片（Y轴反转/上下镜像）
inline void flip_imageY(IMAGE* src, IMAGE* rst) {
	int w = src->getwidth();
	int h = src->getheight();
	Resize(rst, w, h); //调整目标图片大小
	DWORD* src_data = GetImageBuffer(src);
	DWORD* rst_data = GetImageBuffer(rst);
	for(int y=0;y<h;y++) {
		for (int x = 0; x < w; x++) {
			rst_data[y * w + x] = src_data[(h - 1 - y) * w + x]; //Y轴反转
		}
	}
}
// 翻转图片（X轴反转/左右镜像）
inline void flip_imageX(IMAGE* src, IMAGE* rst) {
	int w = src->getwidth();
	int h = src->getheight();
	Resize(rst, w, h); //调整目标图片大小
	DWORD* src_data = GetImageBuffer(src);
	DWORD* rst_data = GetImageBuffer(rst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			rst_data[y * w + x] = src_data[y * w + (w - 1 - x)]; //X轴反转
		}
	}
}


// 反转Atlas图集
inline void flip_Atlas(Atlas& src, Atlas& rst) {
	for (int i = 0; i < src.get_size(); i++) {
		IMAGE img_flipped;
		flip_imageX(src.get_image(i), &img_flipped);
		rst.add_image(img_flipped);
	}
}

//透明通道图片
#pragma comment(lib,"MSIMG32.LIB")
inline void putimage_alpha(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER , 0, 255, AC_SRC_ALPHA });
}

inline void putimage_alpha(const Camera& camera,int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	Vector2 camera_position = camera.get_poisition();
	AlphaBlend(GetImageHDC(NULL), (int)(x-camera_position.x), (int)(y-camera_position.y), w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER , 0, 255, AC_SRC_ALPHA });
	//putimage((int)(x - camera.get_poisition().x), (int)(y - camera.get_poisition().y), img);
}

// 生成指定范围内的随机数
inline int RandomRange(int min, int max) {
	std::cout << "rand" << std::endl;
	if (min > max) {
		std::swap(min, max);
	}
	std::cout << rand() << 1 << std::endl;
	return min + rand() % (max - min + 1);
}

// 绘制带阴影的文本
inline void outtextxy_shaded(int x, int y, LPCTSTR str) {
	settextcolor(RGB(45, 45, 45)); // 设置阴影颜色
	outtextxy(x + 3, y + 3, str); // 绘制阴影文本
	settextcolor(RGB(255,255,255)); // 设置文本颜色
	outtextxy(x, y, str); // 绘制文本
}


inline void line(const Camera& camera, int x1, int y1, int x2, int y2) {
	const Vector2 camera_position = camera.get_poisition();
	line((int)(x1 - camera_position.x), (int)(y1 - camera_position.y), (int)(x2 - camera_position.x), (int)(y2 - camera_position.y));
} 