#include "DamageManager.h"
#include "Power.h"


void DamageManager::deal(Player* player, Enemy* enemy) {


	if (enemy && player) {
		// Example logic: reduce player's HP by enemy's attack power
		//player->Hp -= enemy->attack_power;
		if (player->Hp <= 0) {
			// Handle player death
			std::cout << "Player has been defeated!" << std::endl;
		}
		else {
			std::cout << "Player HP: " << player->Hp << std::endl;
		}
		for (const auto& v : player->attach_range) {
			std::cout << "(" << v.x << "," << v.y << ") ";
		}
		std::cout << std::endl;
		bool aaa = false;//û����aaaaaa
		if (player->skill->current_cd == player->skill->cd);
		else
		for (auto block : player->attach_range) {
			//�˴����
			player->attach_range_cal();
			Vector2 attack_pos = block + player->real_target_block;
			std::cout << "Attack power" << player->attack_power <<"Arm poower" <<player->arm_attack_power() << std::endl;
			/*std::cout << "___________" << std::endl;
			std::cout << "�����ж���: (" << attack_pos.x << ", " << attack_pos.y << ")"
				<< " | ���ﵱǰ��: (" << enemy->current_block.x << ", " << enemy->current_block.y << ")"
				<< " | ����Ŀ���: (" << enemy->target_block.x << ", " << enemy->target_block.y << ")" << std::endl;*/

			if ((aaa==false&&((block + player->real_target_block) == enemy->current_block || (block + player->real_target_block) == enemy->target_block))) {
				
				player->current_animation = player->is_facing_right ? &player->animation_attack_left :&player->animation_attack_right;

				enemy->Hp -= player->attack_power+player->arm_attack_power();
				player->have_attacked = true;
				player->skill->after_battle(); // Update skill state after attack
				player->skill->on_end(player); // End skill effect after attack)
				aaa = true;
			}
			if (enemy->Hp <= 0) {
				// Handle enemy death
				std::cout << "Enemy has been defeated!" << std::endl;
				if (enemy->on_dead_callback) {
					enemy->on_dead_callback(); // Call the death callback if set
				}
			}
			else {
				std::cout << "Enemy HP: " << enemy->Hp << std::endl;
			}
		}
		//�������

		if (enemy->target_block == player->real_block) {// ��������Ŀ�������������ڸ���
			if (enemy->remote_ready_to_attack == true) {// ��������Ѿ�׼���ù���
				enemy->ready_to_attack = true;// ����Ϊ����״̬
				enemy->remote_ready_to_attack = false;// ����Ϊ����Զ�̹���״̬
			}
			if (enemy->ready_to_attack == false || enemy->remote_ready_to_attack == true)// �������û��׼���ù�������Զ�̹���״̬
				enemy->ready_to_attack = true;// ����Ϊ����״̬

			else {// �������׼���ù���
				enemy->current_animation =enemy->is_facing_right? &enemy->animation_attack_right:&enemy->animation_attack_left;
				player->Hp -= (enemy->attack_power-player->defence)? enemy->attack_power - player->defence :0;// ������ҵ�HP
				std::cout << "Player hit! Player HP reduced by " << enemy->attack_power << std::endl;
				enemy->ready_to_attack = false; // ����Ϊ���ɹ���״̬
				enemy->have_attacked = true;// ����Ϊ�Ѿ�����״̬
			}
			
		}
		/*else if (enemy->target_block == player->real_target_block) {
			enemy->remote_ready_to_attack = true;

		}*/

		else {
			enemy->ready_to_attack = false;
			enemy->have_attacked = false;
			enemy->remote_ready_to_attack = false;
		}
	}
}