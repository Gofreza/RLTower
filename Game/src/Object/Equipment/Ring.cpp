#include "Ring.h"
#include "../../Character/Character.h"

Ring::Ring(short id, std::string name, const std::string& description, ItemType type, float weight, int durability, RarityType rarity,
        int phyDefense, int magDefense,
        std::vector<Effect*> effects,
        std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, phyDefense, magDefense, effects, requirements)
{
}

Ring::Ring(const Ring& ring)
: Equipment(ring.getId(), ring.getName(), ring.getDescription(), ring.getType(), ring.getWeight(), ring.getRarity(), ring.getDurability(), ring.getPhyDefense(), ring.getMagDefense(), ring.getEffects(), ring.getRequirements()){
}

Ring* Ring::clone() const {
    return new Ring(*this); 
}

void Ring::use(Character* character) {
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

Ring::~Ring()
{
}