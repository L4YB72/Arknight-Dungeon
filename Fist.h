#pragma once
#include "Arm.h"
class Fist :public Arm {
public:
	Fist() {
		type = Arm::arm_type::Fist; // 设置武器类型为拳头
		position = Vector2(0, 0); // 初始化位置
		damage = 1; // 设置伤害值
		is_active = true; // 设置为激活状态
	}

	std::vector<Vector2> get_range(Vector2 dir) override {
		std::vector < Vector2> range;
		range.clear(); // 清空范围
		range.push_back(Vector2(0, 0)); // 添加中心格子
		std::cout << "Fist range: " << range.size() << std::endl;
		for (auto a : range) {
			std::cout << "Range block: " << a.x << "," << a.y << std::endl;
		}
		return range;

	}
};

