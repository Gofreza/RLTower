#pragma once

#include "Character.h"

class Player : public Character
{
public:
    Player(float hp, int mana, int energy, int stamina, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck);
    ~Player();

private:
};