#pragma once
#include "Enemy.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"

class B1:public Enemy{
private:
	const Vector2 move_direction[2] = { {0,1},{0,-1} };
public:

	B1(int level=0);
	~B1(); // 默认析构函数

	void on_update(int delta);
	void on_render(const Camera& camera);

	void move(Map*& map) override;

	void attact() override; // 攻击方法

};

