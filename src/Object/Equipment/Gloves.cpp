#include "Gloves.h"
#include "../../Character/Character.h"

Gloves::Gloves(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
               int phyDefense, int magDefense,
               std::string imagePath,
               std::vector<Effect*> effects,
               std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, phyDefense, magDefense, imagePath, effects, requirements)
{
}

Gloves::Gloves(const Gloves& gloves)
: Equipment(gloves.getId(), gloves.getName(), gloves.getDescription(), gloves.getType(), gloves.getWeight(), gloves.getRarity(), gloves.getDurability(), gloves.getPhyDefense(), gloves.getMagDefense(), gloves.getImagePath(), gloves.getEffects(), gloves.getRequirements())
{
}

Gloves* Gloves::clone() const {
    return new Gloves(*this); 
}

void Gloves::use(Character* character) {
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

Gloves::~Gloves()
{
}