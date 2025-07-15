#pragma once
#include <vector>
#include "Vector2.h"
#include <graphics.h>
#include "tool.h"

#include <iostream>
class Arm{

public:
	enum class arm_type {
		Fist=0, // Ä¬ÈÏ,È­
		LongKnife, // ³¤µ¶
		Crossbow,  // åó
		Box_glove // È­Ì×
	};
	static const TCHAR* ToString(arm_type type) {
		switch (type) {
		case arm_type::Fist:      return _T("Fist");
		case arm_type::LongKnife: return _T("LongKnife");
		case arm_type::Crossbow:  return _T("Crossbow");
		case arm_type::Box_glove: return _T("Box_glove");
		default:                  return _T("Unknown");
		}
	}



	Arm() = default;
	~Arm() = default; // Îö¹¹º¯Êıgggggb
	Vector2 position; // ÎäÆ÷Î»ÖÃ
	int damage; // ÎäÆ÷ÉËº¦
	arm_type type = arm_type::Fist; // ÎäÆ÷ÀàĞÍ]
	bool is_active; // ÎäÆ÷ÊÇ·ñ¼¤»î
	virtual std::vector<Vector2> get_range(Vector2 dir) = 0;
	

};


