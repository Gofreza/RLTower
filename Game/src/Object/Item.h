#pragma once

#include <iostream>
#include <array>
#include <vector>

#include "ItemType.h"
#include "RarityType.h"
#include "../Effect/Effect.h"

class Item
{
public:
    Item(short id, std::string name, std::string description, ItemType type, float weight, RarityType rarity,
        std::vector<Effect*> effects = std::vector<Effect*>{},
        std::array<int, 5> requirements = {-1, -1, -1, -1, -1});
    virtual ~Item();

    short getId() const;
    std::string getName() const;
    std::string getDescription() const;
    ItemType getType() const;
    float getWeight() const;
    void setWeight(float weight);
    RarityType getRarity() const;
    const std::array<int, 5>& getRequirements() const;

    Item(const Item& item);
    virtual Item* clone() const;

    inline std::string to_string(Item* item) {
        return item->getName() + " (" + std::to_string(item->getId()) + ")";
    }

    const std::vector<Effect*> getEffects() const;

private:
    short id;
    std::string name;
    std::string description;
    ItemType type;
    float weight;
    RarityType rarity;

    std::array<int, 5> requirements;

    std::vector<Effect*> effects;

};