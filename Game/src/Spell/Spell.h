#pragma once

#include <functional>
#include "../Effect/Effect.h"
#include "SpellEnergy.h"
#include "SpellType.h"
#include "SpellElement.h"

class Character;

class Spell
{
public:
    Spell(short id,
        std::string name,
        std::string description,
        SpellEnergy energyType,
        SpellType type,
        SpellElement element,
        int damage,
        int range,
        int consumption,
        std::vector<Effect*> effects = std::vector<Effect*>{},
        std::array<int, 5> requirements = {-1, -1, -1, -1, -1});
    Spell(const Spell& spell);
    ~Spell();

    short getId() const;
    const std::string& getName() const;
    std::string getDescription() const;
    SpellEnergy getSpellEnergyType() const;
    SpellType getType() const;
    SpellElement getElement() const;
    int getDamage() const;
    int getRange() const;
    int getConsumption() const;
    const std::vector<Effect*>& getEffects() const;
    const std::array<int, 5>& getRequirements() const; 

private:
    short id;
    std::string name;
    std::string description;
    SpellEnergy energyType;
    SpellType type;
    SpellElement element;
    int damage;
    int range;
    int consumption;

    // Effect
    std::vector<Effect*> effects;

    std::array<int, 5> requirements;

};
