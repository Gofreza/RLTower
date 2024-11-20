#pragma once

#include "Character.h"

class NPC : public Character
{
private:
    /* data */
public:
    NPC(const std::string& name, SDL_Color color, GroupType group, float hp, int mana, int energy, int stamina, int fov, int speed,
        int phyDamage, int magDamage, int strength, int dexterity,
        int intelligence, int wisdom, int constitution, int luck,
        const char symbol);
    ~NPC();
};
