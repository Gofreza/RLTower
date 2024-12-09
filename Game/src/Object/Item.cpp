#include "Item.h"
#include <filesystem>

Item::Item(short id, std::string name, std::string description, ItemType type, float weight, RarityType rarity,
        std::string imagePath,
        std::vector<Effect*> effects,
        std::array<int, 5> requirements)
: id(id), name(name), description(description), type(type), weight(weight), rarity(rarity), imagePath(imagePath),
effects(effects), requirements(requirements)
{}

Item::Item(const Item& item)
    : id(item.id), name(item.name), description(item.description), type(item.type) , weight(item.weight), rarity(item.rarity),
    imagePath(item.imagePath),
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

float Item::getWeight() const {
    return this->weight;
}

void Item::setWeight(float weight) {
    this->weight = weight;
}

RarityType Item::getRarity() const {
    return this->rarity;
}

std::string Item::getImagePath() const {
    return this->imagePath;
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
