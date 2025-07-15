#pragma once
#include "Arm.h"
class Fist :public Arm {
public:
	Fist() {
		type = Arm::arm_type::Fist; // ������������Ϊȭͷ
		position = Vector2(0, 0); // ��ʼ��λ��
		damage = 1; // �����˺�ֵ
		is_active = true; // ����Ϊ����״̬
	}

	std::vector<Vector2> get_range(Vector2 dir) override {
		std::vector < Vector2> range;
		range.clear(); // ��շ�Χ
		range.push_back(Vector2(0, 0)); // ������ĸ���
		std::cout << "Fist range: " << range.size() << std::endl;
		for (auto a : range) {
			std::cout << "Range block: " << a.x << "," << a.y << std::endl;
		}
		return range;

	}
};

