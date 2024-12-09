#include "Equipment.h"
#include "../../Character/Character.h"

Equipment::Equipment(short id, std::string name, const std::string& description, ItemType type, float weight, RarityType rarity, int durability,
                    int phyDefense, int magDefense,
                    std::vector<Effect*> effects,
                    std::array<int, 5> requirements)
: Item(id, name, description, type, weight, rarity, effects, requirements), equiped(false), durability(durability), maxDurability(durability), phyDefense(phyDefense), magDefense(magDefense)
{
}

int Equipment::getDurability() const {
    return this->durability;
}

int Equipment::getMaxDurability() const {
    return this->maxDurability;
}

int Equipment::getPhyDefense() const {
    return this->phyDefense;
}

int Equipment::getMagDefense() const {
    return this->magDefense;
}

Equipment::~Equipment()
{
}