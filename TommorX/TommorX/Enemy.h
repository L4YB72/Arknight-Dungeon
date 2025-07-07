#pragma once
#include "Camera.h"
#include "graphics.h"

class Enemy {
private:
public:
		Enemy() = default; // 默认构造函数
	~Enemy() = default; // 默认析构函数
	virtual void on_load() {} // 加载敌人资源
	virtual void on_update(int delta) {} // 更新敌人状态
	virtual void on_render(const Camera& camera) {} // 渲染敌人
	virtual void on_unload() {} // 卸载敌人资源
	virtual void on_event(const ExMessage& msg) = 0; // 处理事件
};