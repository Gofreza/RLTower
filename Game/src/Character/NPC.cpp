#include "NPC.h"

NPC::NPC(const std::string& name, SDL_Color color, GroupType group, const std::string& imagePath, const std::string& description, 
        float hp, int mana, int energy, int stamina, int fov, int speed,
        int phyDamage, int magDamage, int strength, int dexterity,
        int intelligence, int wisdom, int constitution, int luck,
        const char symbol,
        std::vector<int> desires, std::vector<int> disgusts)
 : Character(name, color, group, imagePath, description, hp, mana, energy, stamina, fov, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck, symbol, desires, disgusts)
{
}

NPC::~NPC()
{
}

bool NPC::update() {
    return true;
}