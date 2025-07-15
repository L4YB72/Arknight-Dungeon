#pragma once
#include "Player.h"
class Player;
class Skill
{
public:
	enum class SkillType {
		None = 0, // �޼���
		Power, // ������
		Defence, // ������
		Heal, // ������
		Telepote // ������
	};
	int cd;
	int current_cd;
	virtual void on_effect(Player* player) = 0;// ���¼���ʹ��״̬
	virtual void on_end(Player* player) = 0;// ���ܽ���ʱ����
	virtual void cd_update() {// ������ȴ����
		current_cd -= 1; // ÿ�ε��ü�����ȴʱ��;
	}
	virtual void after_battle() = 0;
};

