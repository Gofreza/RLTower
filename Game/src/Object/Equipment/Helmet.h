#pragma once

#include "Equipment.h"

class Character;

class Helmet : public Equipment
{
public:
    Helmet(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity, int phyDefense, int magDefense, 
            std::string imagePath,
            std::vector<Effect*> effects,
            std::array<int, 5> requirements);
    ~Helmet();
    Helmet(const Helmet& helmet);

    virtual Helmet* clone() const override;

    void use(Character* character) override;
private:
    
};
