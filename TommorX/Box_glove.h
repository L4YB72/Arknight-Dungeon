#pragma once
#include "Arm.h"
class Box_glove :public Arm
{
public:
	Box_glove() {
		type = Arm::arm_type::Box_glove; // ������������Ϊȭ��
		position = Vector2(0, 0); // ��ʼ��λ��
		damage = 2; // �����˺�ֵ
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