#pragma once
#include "Skill.h"
#include "Power.h"
#include <vector>

class SkillManager {
public:
    std::vector<Skill*> skill_list; // 技能列表
    Skill::SkillType new_type = Skill::SkillType::None; // 新技能类型
    Skill::SkillType type = Skill::SkillType::None;     // 当前技能类型

    void type_roll() {
        // 随机选择技能类型（跳过None，假设技能数量与枚举顺序一致）
        new_type = (Skill::SkillType)RandomRange(1, skill_list.size() - 1);
        std::cout << "New skill type: " << (int)new_type << std::endl;
    }

    Skill* choose_skill(const ExMessage* msg) {
        if (msg->vkcode == 'E') { 
            type = new_type;
        }
        return skill_list[(int)type];
    }

    void on_render() {
        // 显示当前技能和新技能类型
        outtextxy(100, 150, _T("Current Skill:"));
        outtextxy(220, 150, skill_type_to_string(type));
        outtextxy(100, 170, _T("Next Skill:"));
        outtextxy(220, 170, skill_type_to_string(new_type));
    }

    SkillManager() {
        // 初始化技能列表（需有对应Skill子类实现）
        //skill_list.push_back(new SkillNone());    // None
        skill_list.push_back(new Power());   // Power
        //skill_list.push_back(new SkillDefence()); // Defence
        //skill_list.push_back(new SkillHeal());    // Heal
        //skill_list.push_back(new SkillTelepote());// Telepote
    }

    ~SkillManager() {
        for (auto& skill : skill_list) {
            delete skill;
        }
    }

private:
    // 技能类型转字符串
    const TCHAR* skill_type_to_string(Skill::SkillType type) {
        switch (type) {
        case Skill::SkillType::None:     return _T("None");
        case Skill::SkillType::Power:    return _T("Power");
        case Skill::SkillType::Defence:  return _T("Defence");
        case Skill::SkillType::Heal:     return _T("Heal");
        case Skill::SkillType::Telepote: return _T("Telepote");
        default:                         return _T("Unknown");
        }
    }
};

