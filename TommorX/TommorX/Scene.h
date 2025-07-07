#pragma once
#include "Camera.h"
class Scene {
	//private
	
public:
	Scene() = default; //默认构造函数
	~Scene() = default; //默认析构函数	

	virtual void on_load(){}; //加载场景
	virtual void on_update(int delta){}; //更新场景
	virtual void on_render(const Camera& camera){}; //渲染场景
	virtual void on_unload(){}; //卸载场景
	virtual void on_event(const ExMessage& msg) = 0; //处理事件
 };