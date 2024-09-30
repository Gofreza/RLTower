#pragma once

#include "Equipment.h"

class Chests : public Equipment
{
public:
    Chests(short id, std::string name, const std::string& description, ItemType type, int weight, int durability, RarityType rarity, int phyDefense, int magDefense, 
        std::vector<Effect*> effects = std::vector<Effect*>{},
        std::array<int, 5> requirements = std::array<int, 5>{-1, -1, -1, -1, -1});
    ~Chests();
    Chests(const Chests& amulet);

    virtual Chests* clone() const override;

    void use(Character* character) override;
private:

};
