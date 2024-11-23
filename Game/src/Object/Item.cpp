#include "Item.h"

Item::Item(short id, std::string name, std::string description, ItemType type, int weight, RarityType rarity,
        std::vector<Effect*> effects,
        std::array<int, 5> requirements)
: id(id), name(name), description(description), type(type), weight(weight), rarity(rarity),
effects(effects), requirements(requirements)
{}

Item::Item(const Item& item)
    : id(item.id), name(item.name), description(item.description), type(item.type) , weight(item.weight), rarity(item.rarity),
    effects(item.effects), requirements(item.requirements)
{}

Item* Item::clone() const {
    return new Item(*this); 
}

short Item::getId() const {
    return id;
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

ItemType Item::getType() const {
    return this->type;
}

int Item::getWeight() const {
    return this->weight;
}

RarityType Item::getRarity() const {
    return this->rarity;
}

const std::array<int, 5>& Item::getRequirements() const {
    return requirements;
}

const std::vector<Effect*> Item::getEffects() const {
    return effects;
}

Item::~Item()
{
    // for (const auto& e : effects) {
    //     if (e)
    //         delete e;
    // }
}
