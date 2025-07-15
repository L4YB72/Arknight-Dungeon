#pragma once

#include "Atlas.h"
#include "tool.h"
#include "functional"
#include "camera.h"

class Animation {
private:
	Atlas* atlas = nullptr; // 动画图集
	int timer = 0;
	int frame_index = 0; // 当前帧索引
	int interval = 100; // 帧间隔时间（毫秒）
	bool loop = true; // 是否循环播放
	std::function<void()> on_finished_callback; // 动画完成回调函数 

public:
	Animation() = default; // 默认构造函数
	~Animation() = default; // 默认析构函数

	void reset() { // 重置动画
		frame_index = 0;
		timer = 0;
	}

	void set_atlas(Atlas* new_atlas) { // 设置动画图集
		reset(); // 重置动画状态
		atlas = new_atlas;
	}
	void set_loop(bool should_loop) { // 设置是否循环播放
		loop = should_loop;
	}

	void set_interval(int new_interval) { // 设置帧间隔时间
		interval = new_interval;
	}

	int get_frame_index() const { // 获取当前帧索引
		return frame_index;
	}

	int get_frame_count() const { // 获取总帧数
		if (atlas) {
			return atlas->get_size();
		}
		return 0; // 如果没有图集，返回0
	}

	IMAGE* get_current_frame() { // 获取当前帧图片
			return atlas->get_image(frame_index);
	}

	bool check_finished() { // 检查动画是否完成
		if (atlas) {
			return (frame_index==atlas->get_size()-1);
		}
		if (loop)
			return false;
	}

	void on_update(int delta) {// 更新动画状态
		timer += delta; // 增加计时器
		if (timer >= interval) {
			timer = 0;
			frame_index++;
			if (frame_index >= atlas->get_size()) {// 如果当前帧索引超过图集大小
				frame_index = loop ? 0 : atlas->get_size() - 1; // 如果循环则重置帧索引，否则保持在最后一帧
				if (!loop && on_finished_callback) { // 如果不循环且设置了回调函数
					on_finished_callback(); // 调用回调函数
				}
			}
		}
	}

	void on_draw(int x, int y,const Camera camera) const {// 绘制当前帧图片
		putimage_alpha(camera,x, y, atlas->get_image(frame_index));
	}

	void set_on_finished_callback(std::function<void()> callback) { // 设置动画完成回调函数
		on_finished_callback = callback;
	}
};
 
