#include "Spell.h"

#include "../Character/Character.h"

Spell::Spell(short id, 
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
            std::array<int, 5> requirements)
: id(id), name(name), description(description), energyType(energyType), type(type), element(element), damage(damage), range(range), consumption(consumption),
  effectText(effectText), effect(effect), requirements(requirements)
{
}

short Spell::getId() const {
    return id;
}

const std::string& Spell::getName() const {
    return name;
}

std::string Spell::getDescription() const {
    return description;
}

SpellEnergy Spell::getSpellEnergyType() const {
    return energyType;
}

SpellType Spell::getType() const {
    return type;
}

SpellElement Spell::getElement() const {
    return element;
}

int Spell::getDamage() const {
    return damage;
}

int Spell::getRange() const {
    return range;
}

int Spell::getConsumption() const {
    return consumption;
}

std::string Spell::getEffectText() const {
    return effectText;
}

std::function<void(Character*)> Spell::getEffect() const {
    return effect;
}

const std::array<int, 5>& Spell::getRequirements() const {
    return requirements;
}

Spell::~Spell() {
}