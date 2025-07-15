#include "Vector2.h"
#include "Timer.h"



class Camera {
private:
	Vector2 position; //相机位置
	Timer timer_shake;//抖动计时器
	bool is_shake = false;//是否抖动
	float shaking_strenth = 0;//抖动强度

public:
	Camera() {
		position = Vector2(0, 0); //初始化相机位置
		timer_shake.set_one_shot(true); //设置为单次执行
		timer_shake.set_callback([&]() {
			is_shake = false; //抖动结束
			reset(); //重置相机位置
			});
	}
	~Camera() = default;//默认析构函数

	const Vector2& get_poisition() const {//获取相机位置
		return position;
	}

	void set_position(const Vector2& new_position) {//设置相机位置
		position = new_position;
	}

	void reset() {//重置相机位置
		position = Vector2(0, 0);
	}

	void on_update(int delta) {//更新相机位置
		timer_shake.on_update(delta); //更新抖动计时器

		if (is_shake) {
			//如果正在抖动则随机偏移相机位置
			position.x += (rand() % 100 - 50) * shaking_strenth / 100.0f;
			position.y += (rand() % 100 - 50) * shaking_strenth / 100.0f;
		}
	}

	void shake(float strength, int duration) {//抖动相机
		if (is_shake) return; //如果正在抖动则不处理
		is_shake = true; //设置为正在抖动
		shaking_strenth = strength; //设置抖动强度
		timer_shake.set_wait_time(duration); //设置等待时间
		timer_shake.restart(); //重启计时器
	}
};