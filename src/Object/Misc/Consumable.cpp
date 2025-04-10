#include "Consumable.h"

#include "../../Character/Character.h"

Consumable::Consumable(short id, std::string name, std::string description, ItemType type, float weight, RarityType rarity,
            std::string imagePath,
            std::vector<Effect*> effects) 
: Misc(id, name, description, type, weight, rarity, imagePath, effects)
{
}

Consumable::Consumable(const Consumable& consumable)
: Misc(consumable.getId(), consumable.getName(), consumable.getDescription(), consumable.getType(), consumable.getWeight(), consumable.getRarity(), consumable.getImagePath(), consumable.getEffects())
{
}

Consumable* Consumable::clone() const {
    return new Consumable(*this); 
}

void Consumable::use(Character* character) {
    for (const auto& e : this->getEffects()) {
        e->trigger(character);
    }
}

Consumable::~Consumable() {

}