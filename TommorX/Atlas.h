#pragma once

#include <vector>
#include <graphics.h>

class Atlas {
private:
	std::vector<IMAGE> img_list;
public:
	Atlas() = default; //默认构造函数
	~Atlas() = default; //默认析构函数

	void add_image(LPCTSTR path_template,int num,int nwid=0,int nhig=0,bool resize=0) { //添加图片到图集
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++) {
			_stprintf_s(path_file, path_template, i);
			loadimage(&img_list[i], path_file,nwid,nhig,resize);
		}
	}

	void clear() {
		img_list.clear(); //清空图集
	}

	int get_size() const { //获取图集大小
		return (int)img_list.size();
	}

	IMAGE* get_image(int index) { //获取指定索引的图片
		if (index < 0 || index >= img_list.size()) {
			return nullptr; //索引越界
		}
		return &img_list[index];
	}

	void add_image(const IMAGE& img) { //添加单张图片到图集
		img_list.push_back(img);
	}
};