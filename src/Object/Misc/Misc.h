#pragma once

#include "../Item.h"

class Misc : public Item
{
public:
    Misc(short id, std::string name, std::string description, ItemType type, float weight, RarityType rarity,
    std::string imagePath,
    std::vector<Effect*> effects = std::vector<Effect*>{});
    ~Misc();
private:
    /* data */
};

