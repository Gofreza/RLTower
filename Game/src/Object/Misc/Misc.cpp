#include "Misc.h"

Misc::Misc(short id, std::string name, std::string description, ItemType type, float weight, RarityType rarity,
        std::vector<Effect*> effects)
: Item(id, name, description, type, weight, rarity, effects)
{
}

Misc::~Misc()
{
}