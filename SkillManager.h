#pragma once
#include "Skill.h"
#include "Power.h"
#include <vector>

class SkillManager {
public:
    std::vector<Skill*> skill_list; // �����б�
    Skill::SkillType new_type = Skill::SkillType::None; // �¼�������
    Skill::SkillType type = Skill::SkillType::None;     // ��ǰ��������

    void type_roll() {
        // ���ѡ�������ͣ�����None�����輼��������ö��˳��һ�£�
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
        // ��ʾ��ǰ���ܺ��¼�������
        outtextxy(100, 150, _T("Current Skill:"));
        outtextxy(220, 150, skill_type_to_string(type));
        outtextxy(100, 170, _T("Next Skill:"));
        outtextxy(220, 170, skill_type_to_string(new_type));
    }

    SkillManager() {
        // ��ʼ�������б����ж�ӦSkill����ʵ�֣�
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
    // ��������ת�ַ���
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

