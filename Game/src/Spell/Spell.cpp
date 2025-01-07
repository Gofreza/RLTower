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
            std::vector<Effect*> effects,
            std::array<int, 5> requirements)
: id(id), name(name), description(description), energyType(energyType), type(type), element(element), damage(damage), range(range), consumption(consumption),
  effects(effects), requirements(requirements)
{
}

Spell::Spell(const Spell& spell) 
: id(spell.id), name(spell.name), description(spell.description), energyType(spell.energyType), type(spell.type), element(spell.element), damage(spell.damage), range(spell.range), consumption(spell.consumption),
  effects(spell.effects), requirements(spell.requirements)
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

const std::vector<Effect*>& Spell::getEffects() const {
    return effects;
}

const std::array<int, 5>& Spell::getRequirements() const {
    return requirements;
}

Spell::~Spell() {
}