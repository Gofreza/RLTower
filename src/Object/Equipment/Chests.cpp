#include "Chests.h"
#include "../../Character/Character.h"

Chests::Chests(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
               int phyDefense, int magDefense,
               std::string imagePath,
               std::vector<Effect*> effects,
               std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, phyDefense, magDefense, imagePath, effects, requirements)
{
}

Chests::Chests(const Chests& chests)
: Equipment(chests.getId(), chests.getName(), chests.getDescription(), chests.getType(), chests.getWeight(), chests.getRarity(), chests.getDurability(), chests.getPhyDefense(), chests.getMagDefense(), chests.getImagePath(), chests.getEffects(), chests.getRequirements())
{
}

Chests* Chests::clone() const {
    return new Chests(*this); 
}

void Chests::use(Character* character) {
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

Chests::~Chests()
{
}