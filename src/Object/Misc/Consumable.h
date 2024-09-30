#pragma once

#include <functional>
#include "Misc.h"

// Forward declaration of the Player class
class Character;

class Consumable : public Misc
{
public:
    Consumable(short id, std::string name, std::string description, ItemType type, int weight, RarityType rarity,
            std::vector<Effect*> effects);
    Consumable(const Consumable& consumable);
    ~Consumable();

    virtual Consumable* clone() const override;

    void use(Character* character);

private:
    
};
