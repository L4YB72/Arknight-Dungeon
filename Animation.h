#pragma once

#include "Atlas.h"
#include "tool.h"
#include "functional"
#include "camera.h"

class Animation {
private:
	Atlas* atlas = nullptr; // ����ͼ��
	int timer = 0;
	int frame_index = 0; // ��ǰ֡����
	int interval = 100; // ֡���ʱ�䣨���룩
	bool loop = true; // �Ƿ�ѭ������
	std::function<void()> on_finished_callback; // ������ɻص����� 

public:
	Animation() = default; // Ĭ�Ϲ��캯��
	~Animation() = default; // Ĭ����������

	void reset() { // ���ö���
		frame_index = 0;
		timer = 0;
	}

	void set_atlas(Atlas* new_atlas) { // ���ö���ͼ��
		reset(); // ���ö���״̬
		atlas = new_atlas;
	}
	void set_loop(bool should_loop) { // �����Ƿ�ѭ������
		loop = should_loop;
	}

	void set_interval(int new_interval) { // ����֡���ʱ��
		interval = new_interval;
	}

	int get_frame_index() const { // ��ȡ��ǰ֡����
		return frame_index;
	}

	int get_frame_count() const { // ��ȡ��֡��
		if (atlas) {
			return atlas->get_size();
		}
		return 0; // ���û��ͼ��������0
	}

	IMAGE* get_current_frame() { // ��ȡ��ǰ֡ͼƬ
			return atlas->get_image(frame_index);
	}

	bool check_finished() { // ��鶯���Ƿ����
		if (atlas) {
			return (frame_index==atlas->get_size()-1);
		}
		if (loop)
			return false;
	}

	void on_update(int delta) {// ���¶���״̬
		timer += delta; // ���Ӽ�ʱ��
		if (timer >= interval) {
			timer = 0;
			frame_index++;
			if (frame_index >= atlas->get_size()) {// �����ǰ֡��������ͼ����С
				frame_index = loop ? 0 : atlas->get_size() - 1; // ���ѭ��������֡���������򱣳������һ֡
				if (!loop && on_finished_callback) { // �����ѭ���������˻ص�����
					on_finished_callback(); // ���ûص�����
				}
			}
		}
	}

	void on_draw(int x, int y,const Camera camera) const {// ���Ƶ�ǰ֡ͼƬ
		putimage_alpha(camera,x, y, atlas->get_image(frame_index));
	}

	void set_on_finished_callback(std::function<void()> callback) { // ���ö�����ɻص�����
		on_finished_callback = callback;
	}
};
 
