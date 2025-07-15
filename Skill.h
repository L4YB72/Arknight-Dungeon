#pragma once
#include "Player.h"
class Player;
class Skill
{
public:
	enum class SkillType {
		None = 0, // 无技能
		Power, // 加伤术
		Defence, // 减伤术
		Heal, // 治疗术
		Telepote // 传送术
	};
	int cd;
	int current_cd;
	virtual void on_effect(Player* player) = 0;// 更新技能使用状态
	virtual void on_end(Player* player) = 0;// 技能结束时调用
	virtual void cd_update() {// 技能冷却更新
		current_cd -= 1; // 每次调用减少冷却时间;
	}
	virtual void after_battle() = 0;
};

