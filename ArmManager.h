#pragma once
#include <graphics.h>
#include <vector>
#include "Arm.h"
#include "LongKnife.h"
#include "rossbow.h"
#include "Fist.h"
#include "Box_glove.h"

class ArmManager{
public:	
	std::vector<Arm*> arm_list; // �����б�
	Arm::arm_type new_type = Arm::arm_type::Fist; // Ĭ����������Ϊȭͷ
	Arm::arm_type type = Arm::arm_type::Fist; // ��ǰ��������

	void type_roll() {
		new_type = (Arm::arm_type)RandomRange(1, arm_list.size()-1); // ���ѡ����������
		std::cout << "New type: " << Arm::ToString(new_type) << std::endl; // �����ѡ�����������
	}
	
	Arm* choose_arm(const ExMessage* msg){
		if (msg->vkcode == 'E') {
			type = new_type; // �������E�������л�����ѡ�����������
		}
			return arm_list[(int)type];
	}

	void on_render() {
		switch (type)
		{
		case Arm::arm_type::Fist:
			outtextxy(100, 100, _T("FIST"));
			break;
		case Arm::arm_type::LongKnife:
			outtextxy(100, 100, _T("LONGKNIFE"));
			break;
		case Arm::arm_type::Crossbow:
			outtextxy(100, 100, _T("CROSSBOW"));
			break;
		case Arm::arm_type::Box_glove:
			outtextxy(100, 100, _T("BOX_GLOVE"));
			break;
		default:
			break;
		}

		switch (new_type)
		{
		case Arm::arm_type::Fist:
			outtextxy(300, 100, _T("FIST"));
			break;
		case Arm::arm_type::LongKnife:
			outtextxy(300, 100, _T("LONGKNIFE"));
			break;
		case Arm::arm_type::Crossbow:
			outtextxy(300, 100, _T("CROSSBOW"));
			break;
		case Arm::arm_type::Box_glove:
			outtextxy(300, 100, _T("BOX_GLOVE"));
			break;
		default:
			break;
		}
		
	}

	ArmManager() {
		// ��ʼ�������б�
		arm_list.push_back(new Fist()); // ���ȭͷ
		arm_list.push_back(new LongKnife()); // ��ӳ���
		arm_list.push_back(new Crossbow()); // �����
		arm_list.push_back(new Box_glove()); // ���ȭ��
	}

	~ArmManager() {
		for(auto & arm : arm_list) {
			delete arm; // ɾ����������
		}
	}
};

