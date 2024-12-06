#pragma once

#include "Character.h"

class Player : public Character
{
public:
    Player(const std::string& name, SDL_Color color, GroupType group, float hp, int mana, int energy, int stamina, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            std::vector<int> desires, std::vector<int> disgusts);
    ~Player();

    bool update() override;

private:
};