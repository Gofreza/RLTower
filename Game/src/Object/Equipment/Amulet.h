#pragma once

#include <functional>
#include "Equipment.h"

class Amulet : public Equipment
{
public:
    Amulet(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
        int physicalDefense, int magicalDefense,
        std::string imagePath,
        std::vector<Effect*> effects = std::vector<Effect*>{},
        std::array<int, 5> requirements = std::array<int, 5>{-1, -1, -1, -1, -1});
    ~Amulet();
    Amulet(const Amulet& amulet);

    void use(Character* character) override;

    virtual Amulet* clone() const override;
private:

};
