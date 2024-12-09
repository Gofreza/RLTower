#include "Amulet.h"
#include "../../Character/Character.h"
#include "../../Character/Player.h"

Amulet::Amulet(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
            int physicalDefense, int magicalDefense,
            std::vector<Effect*> effects,
            std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, physicalDefense, magicalDefense, effects, requirements)
{
}

Amulet::Amulet(const Amulet& amulet)
: Equipment(amulet.getId(), amulet.getName(), amulet.getDescription(), amulet.getType(), amulet.getWeight(), amulet.getRarity(), amulet.getDurability(), amulet.getPhyDefense(), amulet.getMagDefense(), amulet.getEffects(), amulet.getRequirements())
{
}

Amulet* Amulet::clone() const {
    return new Amulet(*this); 
}

void Amulet::use(Character* character) {
    // Apply effect and stats
    if (!equiped) {
        for (const auto& effect : this->getEffects()) {
            effect->trigger(character);
        }
        equiped = true;
    } else {
        for (const auto& effect : this->getEffects()) {
            effect->trigger(character, true);
        }
        equiped = false;
    }
}


Amulet::~Amulet()
{
}