#include "Helmet.h"
#include "../../Character/Character.h"

Helmet::Helmet(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
               int phyDefense, int magDefense,
               std::string imagePath,
               std::vector<Effect*> effects,
               std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, phyDefense, magDefense, imagePath, effects, requirements)
{
}

Helmet::Helmet(const Helmet& helmet)
: Equipment(helmet.getId(), helmet.getName(), helmet.getDescription(), helmet.getType(), helmet.getWeight(), helmet.getRarity(), helmet.getDurability(), helmet.getPhyDefense(), helmet.getMagDefense(), helmet.getImagePath(), helmet.getEffects(), helmet.getRequirements())
{
}

Helmet* Helmet::clone() const {
    return new Helmet(*this); 
}

void Helmet::use(Character* character) {
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

Helmet::~Helmet()
{
}