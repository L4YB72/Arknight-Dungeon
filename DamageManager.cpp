#include "DamageManager.h"


void DamageManager::deal(Player* player, Enemy* enemy) {
	// Implement the logic to deal damage from enemy to player
	std::cout << "RAW" <<player->Hp<<enemy->Hp<< std::endl;
	if (enemy && player) {
		// Example logic: reduce player's HP by enemy's attack power
		player->Hp -= enemy->attack_power;
		if (player->Hp <= 0) {
			// Handle player death
			std::cout << "Player has been defeated!" << std::endl;
		} else {
			std::cout << "Player HP: " << player->Hp << std::endl;
		}

		enemy->Hp -= player->attack_power;
		if (enemy->Hp <= 0) {
			// Handle enemy death
			std::cout << "Enemy has been defeated!" << std::endl;
			if (enemy->on_dead_callback) {
				enemy->on_dead_callback(); // Call the death callback if set
			}
		} else {
			std::cout << "Enemy HP: " << enemy->Hp << std::endl;
		}

	}
	std::cout << "AFTER" << player->Hp << enemy->Hp << std::endl;
}