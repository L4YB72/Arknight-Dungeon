#pragma once

#include "Arm.h"

class Crossbow :public Arm
{
public:
	Crossbow()
	{
		int Arrow = 3;//�ӵ���
		//position = Vector2(0, 0); // ��ʼ��λ��
		damage = 1; // �����˺�ֵ
		type = Arm::arm_type::Crossbow; // ������������Ϊ��
		//is_active = true; // ����Ϊ����״̬
	}
	std::vector<Vector2> get_range(Vector2 dir) override {
		std::vector<Vector2> range;
		// dirΪ����������������ΧΪǰ������

		Vector2 dir_norm = dir.normalized();

		range.push_back(dir_norm);           // ǰ��һ��
		range.push_back(dir_norm*2);           // ǰ��һ��
		range.push_back(dir_norm*3);           // ǰ��һ��

		//std::cout << "LongKnife range: " << range.size() << std::endl;

		for (auto a : range) {
			//std::cout << "Range block: " << a.x << "," << a.y << std::endl;
		}
		return range;
	}
};

