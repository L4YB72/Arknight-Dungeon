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
		bool aaa = false;//没救了aaaaaa
		if (player->skill->current_cd == player->skill->cd);
		else
		for (auto block : player->attach_range) {
			//人打怪物
			player->attach_range_cal();
			Vector2 attack_pos = block + player->real_target_block;
			std::cout << "Attack power" << player->attack_power <<"Arm poower" <<player->arm_attack_power() << std::endl;
			/*std::cout << "___________" << std::endl;
			std::cout << "攻击判定格: (" << attack_pos.x << ", " << attack_pos.y << ")"
				<< " | 怪物当前格: (" << enemy->current_block.x << ", " << enemy->current_block.y << ")"
				<< " | 怪物目标格: (" << enemy->target_block.x << ", " << enemy->target_block.y << ")" << std::endl;*/

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
		//怪物打人

		if (enemy->target_block == player->real_block) {// 如果怪物的目标格子是玩家所在格子
			if (enemy->remote_ready_to_attack == true) {// 如果怪物已经准备好攻击
				enemy->ready_to_attack = true;// 设置为攻击状态
				enemy->remote_ready_to_attack = false;// 设置为不可远程攻击状态
			}
			if (enemy->ready_to_attack == false || enemy->remote_ready_to_attack == true)// 如果怪物没有准备好攻击或者远程攻击状态
				enemy->ready_to_attack = true;// 设置为攻击状态

			else {// 如果怪物准备好攻击
				enemy->current_animation =enemy->is_facing_right? &enemy->animation_attack_right:&enemy->animation_attack_left;
				player->Hp -= (enemy->attack_power-player->defence)? enemy->attack_power - player->defence :0;// 减少玩家的HP
				std::cout << "Player hit! Player HP reduced by " << enemy->attack_power << std::endl;
				enemy->ready_to_attack = false; // 设置为不可攻击状态
				enemy->have_attacked = true;// 设置为已经攻击状态
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