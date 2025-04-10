#pragma once

#include "Equipment.h"

class Gloves : public Equipment
{
public:
    Gloves(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity, int phyDefense, int magDefense, 
            std::string imagePath,
            std::vector<Effect*> effects,
            std::array<int, 5> requirements);
    ~Gloves();
    Gloves(const Gloves& gloves);

    virtual Gloves* clone() const override;

    void use(Character* character) override;
private:
};
