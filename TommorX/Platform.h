#pragma once
#include "Camera.h"
#include <graphics.h>
#include "Camera.h"

extern bool is_debug; // 是否开启debug模式


class Platform {
private:
public:
	Platform() = default; // 默认构造函数
	~Platform() = default; // 默认析构函数

	struct CollisionShape//碰撞外形
	{
		float y;//y坐标
		float left; // 左边界
		float right; // 右边界
	};

	CollisionShape collision_shape; // 碰撞外形
	IMAGE* img = nullptr; // 平台图片
	POINT render_posiiton = {0}; // 平台位置


	void on_render(const Camera& camera) const {
		if (is_debug) {
			setlinecolor(RED);
			line(camera,(int)collision_shape.left,(int)collision_shape.y,
				(int)collision_shape.right,(int)collision_shape.y);
		}
	}

};