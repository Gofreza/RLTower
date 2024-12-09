#include "Shield.h"
#include "../../Character/Character.h"

Shield::Shield(short id, 
            std::string name,
            const std::string& description, 
            ItemType type, 
            float weight, 
            int durability, 
            RarityType rarity, 
            int phyDefense, 
            int magDefense, 
            int parryChance, 
            std::vector<Effect*> effects,
            std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, phyDefense, magDefense, effects, requirements), parryChance(parryChance)
{
}

Shield::Shield(const Shield& shield)
: Equipment(shield.getId(), shield.getName(), shield.getDescription(), shield.getType(), shield.getWeight(), shield.getRarity(), shield.getDurability(), shield.getPhyDefense(), shield.getMagDefense(), shield.getEffects(), shield.getRequirements()), 
            parryChance(shield.getParryChance())
{
}

Shield* Shield::clone() const {
    return new Shield(*this); 
}

void Shield::use(Character* character) {
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

int Shield::getParryChance() const {
    return parryChance;
}

bool Shield::block() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 100);

    int random_number = distr(gen);

    return random_number <= parryChance;
}

Shield::~Shield() {}