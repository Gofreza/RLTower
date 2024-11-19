#include "NPC.h"

NPC::NPC(const std::string& name, SDL_Color color, float hp, int mana, int energy, int stamina, int fov, int speed,
        int phyDamage, int magDamage, int strength, int dexterity,
        int intelligence, int wisdom, int constitution, int luck,
        const char symbol)
 : Character(name, color, hp, mana, energy, stamina, fov, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck, symbol)
{
}

NPC::~NPC()
{
}
