#pragma once
#include <functional>

class Timer {
private:
	int elapsed_time = 0;	//已用时间
	int start_time = 0;	//开始时间
	int end_time = 0;	//结束时间
	int waite_time = 0;	//等待时间
	bool paused = 0;	//是否暂停
	bool shotted = 0;	//是否已执行
	bool one_shot = 0;	//是否单次执行
	std::function<void()> callback; //回调函数
public:
	Timer() = default;//默认构造函数
	~Timer() = default; //默认析构函数

	void restart() {
		elapsed_time = 0;
		shotted = false;
	}

	void set_wait_time(int time) {
		waite_time = time;
	}


	void set_one_shot(bool one_shot) {
		this->one_shot = one_shot;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}
	
	void pause() {
		paused = true;
	}

	void resume() {
		paused = false;
	}

	void on_update(int delta) {
		if (paused) return; //如果暂停或已执行则不更新
		   
		elapsed_time += delta; //增加已用时间
		if (elapsed_time >= waite_time) { //如果已用时间超过等待时间
			if (!one_shot || (one_shot && !shotted) && callback) {
				callback();
			}
			shotted = true;
			elapsed_time = 0;
		}
	}
	
};
