//#include <graphics.h>
//#include <vector>
//#include <string>
//#include "Amiya.h"
//
////透明通道图片
//#pragma comment(lib,"MSIMG32.LIB")
//void putimage_alpha(int x, int y, IMAGE* img) {
//	int w = img->getwidth();
//	int h = img->getheight();
//	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
//		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER , 0, 255, AC_SRC_ALPHA });
//}
//
////绘制背景
//void load_background(const IMAGE& img_background) {
//	int room_row_num = 5;
//	int room_line_num = 5;
//	for (int i = 0; i < room_row_num; i++) {
//		for (int j = 0; j < room_line_num; j++) {
//			putimage(600*i, 600*j, &img_background);
//		}
//	}
//}
//
//extern const int AMIYA_ANIM_NUM;
////std::vector<IMAGE*> loadimage_frames(LPCTSTR path_format, int num) {
////	std::vector<IMAGE*> frames;
////	TCHAR path_file[256];
////	for (int i = 0; i < num; ++i) {
////		_stprintf_s(path_file, path_format, i);
////		IMAGE* frame = new IMAGE();
////		loadimage(frame, path_file);
////		frames.push_back(frame);
////	}
////	return frames;
////}
////Animate amiya_right_move(loadimage_frames(_T("Image/amiya/%d@0.5x.png"), AMIYA_ANIM_NUM), 75);
//
////amiya动画
//Animate amiya_right_move(_T("Image/amiya/%d@0.5x.png"), AMIYA_ANIM_NUM, 100);
//extern Amiya amiya;
//void DrawAmiya(int x, int y, DWORD delta) {
//	amiya_right_move.Play(x, y, delta);
//}
//
////动画加载
//void DrawAnimation() {
//	static DWORD last_draw_time=GetTickCount();
//	DWORD current_draw_time;
//	current_draw_time = GetTickCount();
//	DWORD delta_draw_time = current_draw_time - last_draw_time;
//	DrawAmiya(amiya.x,amiya.y,delta_draw_time);
//	last_draw_time = current_draw_time;
//}
//
//
////camera
//
