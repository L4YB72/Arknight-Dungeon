#pragma once
#include "Arm.h"
class LongKnife :public Arm
{
	public:
	LongKnife() {
		type = Arm::arm_type::LongKnife; // ������������Ϊ����
		position = Vector2(0, 0); // ��ʼ��λ��
		damage = 1; // �����˺�ֵ
		is_active = true; // ����Ϊ����״̬
	}
	std::vector<Vector2> get_range(Vector2 dir) override {
		std::vector<Vector2> range;
		// dirΪ����������������ΧΪǰ������
		Vector2 dir_norm = dir.normalized();
		range.push_back(dir_norm);           // ǰ��һ��
		//range.push_back(dir_norm * 2);       // ǰ������
		std::cout << "LongKnife range: " << range.size() << std::endl;
		for(auto a:range) {
			std::cout << "Range block: " << a.x << "," << a.y << std::endl;
		}
		return range;
	}
};

