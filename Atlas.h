#pragma once

#include <vector>
#include <graphics.h>

class Atlas {
private:
	std::vector<IMAGE> img_list;
public:
	Atlas() = default; //Ĭ�Ϲ��캯��
	~Atlas() = default; //Ĭ����������

	void add_image(LPCTSTR path_template,int num,int nwid=0,int nhig=0,bool resize=0) { //���ͼƬ��ͼ��
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++) {
			_stprintf_s(path_file, path_template, i);
			loadimage(&img_list[i], path_file,nwid,nhig,resize);
		}
	}

	void clear() {
		img_list.clear(); //���ͼ��
	}

	int get_size() const { //��ȡͼ����С
		return (int)img_list.size();
	}

	IMAGE* get_image(int index) { //��ȡָ��������ͼƬ
		if (index < 0 || index >= img_list.size()) {
			return nullptr; //����Խ��
		}
		return &img_list[index];
	}

	void add_image(const IMAGE& img) { //��ӵ���ͼƬ��ͼ��
		img_list.push_back(img);
	}
};