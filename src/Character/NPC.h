#pragma once

#include "Character.h"

class NPC : public Character
{
private:
    /* data */
public:
    NPC(const std::string& name, SDL_Color color, GroupType group, const std::string& imagePath, const std::string& description,
        float hp, int mana, int energy, int stamina, bool isAuraUser, int fov, int speed,
        int phyDamage, int magDamage, int strength, int dexterity,
        int intelligence, int wisdom, int constitution, int luck,
        const char symbol,
        std::vector<int> desires, std::vector<int> disgusts);
    ~NPC();

    UpdateState update() override;
};
