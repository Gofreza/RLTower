#pragma once

#include <functional>
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
        std::string effectText,
        std::function<void(Character*)> effect,
        std::array<int, 5> requirements);
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
    std::string getEffectText() const;
    std::function<void(Character*)> getEffect() const;
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
    std::string effectText;
    std::function<void(Character*)> effect;

    std::array<int, 5> requirements;

};
