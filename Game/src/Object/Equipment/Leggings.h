#pragma once

#include "Equipment.h"

class Leggings : public Equipment
{
public:
    Leggings(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity, int phyDefense, int magDefense, 
            std::string imagePath,
            std::vector<Effect*> effects,
            std::array<int, 5> requirements);
    ~Leggings();
    Leggings(const Leggings& leggings);

    virtual Leggings* clone() const override;

    void use(Character* character) override;
private:
};
