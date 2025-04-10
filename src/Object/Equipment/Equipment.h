#pragma once

#include "../Item.h"
#include "../../Effect/Effect.h"

class Character;

class Equipment : public Item
{
public:
    Equipment(short id, std::string name, const std::string& description, ItemType type, float weight, RarityType rarity, int durability,
            int phyDefense, int magDefense,
            std::string imagePath,
            std::vector<Effect*> effects = std::vector<Effect*>{},
            std::array<int, 5> requirement = std::array<int, 5>{-1, -1, -1, -1, -1});
    ~Equipment();

    virtual void use(Character* character) = 0;

    int getDurability() const;
    int getMaxDurability() const;

    int getPhyDefense() const;
    int getMagDefense() const;
protected:
    bool equiped;
private:
    int durability;
    int maxDurability;

    int phyDefense;
    int magDefense;

    // Resistances here
};


