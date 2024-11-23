#pragma once

#include <functional>
#include <random>
#include "Equipment.h"

class Shield : public Equipment
{
public:
    Shield(short id, 
        std::string name, 
        const std::string& description,
        ItemType type, 
        int weight, 
        int durability, 
        RarityType rarity, 
        int phyDefense, int magDefense,
        int parryChance,
        std::vector<Effect*> effects,
        std::array<int, 5> requirements);
    ~Shield();

    Shield(const Shield& weapon);
    virtual Shield* clone() const override;

    void use(Character* character) override;

    int getParryChance() const;
    bool block();
private:
    int parryChance;
};
