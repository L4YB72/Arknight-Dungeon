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
	std::vector<Arm*> arm_list; // 武器列表
	Arm::arm_type new_type = Arm::arm_type::Fist; // 默认武器类型为拳头
	Arm::arm_type type = Arm::arm_type::Fist; // 当前武器类型

	void type_roll() {
		new_type = (Arm::arm_type)RandomRange(1, arm_list.size()-1); // 随机选择武器类型
		std::cout << "New type: " << Arm::ToString(new_type) << std::endl; // 输出新选择的武器类型
	}
	
	Arm* choose_arm(const ExMessage* msg){
		if (msg->vkcode == 'E') {
			type = new_type; // 如果按下E键，则切换到新选择的武器类型
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
		// 初始化武器列表
		arm_list.push_back(new Fist()); // 添加拳头
		arm_list.push_back(new LongKnife()); // 添加长刀
		arm_list.push_back(new Crossbow()); // 添加弩
		arm_list.push_back(new Box_glove()); // 添加拳套
	}

	~ArmManager() {
		for(auto & arm : arm_list) {
			delete arm; // 删除武器对象
		}
	}
};

