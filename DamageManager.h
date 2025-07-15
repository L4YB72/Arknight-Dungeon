#pragma once
#include "Enemy.h" // Ensure Enemy.h is included
#include "Player.h" // Ensure Player.h is included
#include "iostream"


class Enemy; // Forward declaration of Enemy class

class DamageManager
{
public: // Add public access specifier for proper usage
    void deal(Player* player,Enemy* enemy); // Correct spelling of "enemy"
};

