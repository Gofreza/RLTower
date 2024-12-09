#pragma once

#include "Equipment.h"


class Ring : public Equipment
{    
public:
    Ring(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
        int phyDefense, int magDefense,
        std::vector<Effect*> effects,
        std::array<int, 5> requirements);
    ~Ring();
    Ring(const Ring& ring);

    virtual Ring* clone() const override;

    void use(Character* character) override;

private:
};
