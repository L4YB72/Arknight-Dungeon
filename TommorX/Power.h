#pragma once
#include "Skill.h"
class Power : public Skill {
    bool is_active = false; // �����Ƿ񼤻�
    int damage_times = 0;
    int power_add = 1;      // ���ӵĹ�����
public:
    Power() {
        cd = 40;
    }

    void on_effect(Player* player) override {
        //if (current_cd > 0) return; // ��ȴ��
        if (is_active||current_cd>0) return;      // �Ѽ���
        player->add_attack_power(power_add); // ���ӹ�����
        damage_times = 5;
        is_active = true;
        current_cd = cd;
    }

    void cd_update(bool have_attacked) {
        Skill::cd_update();

    }

	void after_battle() override{
		std::cout << "Power skill after battle, current CD: " << current_cd << std::endl;
		if (damage_times > 0) {
			damage_times--;
		}
		std::cout << "Power skill active, remaining damage times: " << damage_times << std::endl;
	}


    void on_end(Player* player) override {
        if (is_active && damage_times <= 0) {
            player->subtract_attack_power(power_add); // �ָ�������
            is_active = false;
        }
    }
};