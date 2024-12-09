#include "Leggings.h"
#include "../../Character/Character.h"

Leggings::Leggings(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
               int phyDefense, int magDefense,
               std::vector<Effect*> effects,
               std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, phyDefense, magDefense, effects, requirements)
{
}

Leggings::Leggings(const Leggings& leggings)
: Equipment(leggings.getId(), leggings.getName(), leggings.getDescription(), leggings.getType(), leggings.getWeight(), leggings.getRarity(), leggings.getDurability(), leggings.getPhyDefense(), leggings.getMagDefense(), leggings.getEffects(), leggings.getRequirements())
{
}

Leggings* Leggings::clone() const {
    return new Leggings(*this); 
}

void Leggings::use(Character* character) {
    // Apply effect and stats
    if (!equiped) {
        character->setPhysicalDefenseBonus(this->getPhyDefense());
        character->setMagicalDefenseBonus(this->getMagDefense());
        for (const auto& effect : this->getEffects()) {
            effect->trigger(character);
        }
        equiped = true;
    } else {
        character->setPhysicalDefenseBonus(-this->getPhyDefense());
        character->setMagicalDefenseBonus(-this->getMagDefense());
        for (const auto& effect : this->getEffects()) {
            effect->trigger(character, true);
        }
        equiped = false;
    }
}

Leggings::~Leggings()
{
}