#pragma once

#include "Arm.h"

class Common_Amiya :public Arm
{
public:
	Common_Amiya() 
	{
		//position = Vector2(0, 0); // 初始化位置
		damage = 10; // 设置伤害值
		//is_active = true; // 设置为激活状态
	}
	std::vector<Vector2> get_range(Vector2 dir) override {
		std::vector<Vector2> range;
		// dir为方向向量，攻击范围为前方两格

		Vector2 dir_norm = dir.normalized();

		range.push_back(dir_norm);           // 前方一格
		

		
		//std::cout << "LongKnife range: " << range.size() << std::endl;

		for (auto a : range) {
			//std::cout << "Range block: " << a.x << "," << a.y << std::endl;
		}
		return range;
	}
};

