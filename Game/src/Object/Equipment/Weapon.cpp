#include "Weapon.h"
#include "../../Character/Character.h"

Weapon::Weapon(short id, 
            std::string name, 
            const std::string& description, 
            ItemType type, 
            WeaponType wType, 
            float weight, 
            int durability, 
            RarityType rarity, 
            int phyDamage, 
            int magDamage, 
            DamageType damageType, 
            bool twoHanded, 
            int length, 
            bool magical, 
            int phyDefense, 
            int magDefense, 
            std::string imagePath,
            std::vector<Effect*> effects,
            std::array<int, 5> requirements)
: Equipment(id, name, description, type, weight, rarity, durability, phyDefense, magDefense, imagePath, effects, requirements), wType(wType), phyDamage(phyDamage), magDamage(magDamage), damageType(damageType), twoHanded(twoHanded), length(length), magical(magical)
{
}

Weapon::Weapon(const Weapon& weapon)
: Equipment(weapon.getId(), weapon.getName(), weapon.getDescription(), weapon.getType(), weapon.getWeight(), weapon.getRarity(), weapon.getDurability(), weapon.getPhyDefense(), weapon.getMagDefense(), weapon.getImagePath(), weapon.getEffects(), weapon.getRequirements()), 
            wType(weapon.getWeaponType()), phyDamage(weapon.getPhyDamage()), magDamage(weapon.getMagDamage()), damageType(weapon.getDamageType()), twoHanded(weapon.isTwoHanded()), length(weapon.getLength()), magical(weapon.isMagical())
{
}

Weapon* Weapon::clone() const {
    return new Weapon(*this); 
}

void Weapon::use(Character* character) {
    // Apply effect and stats
    if (!equiped) {
        character->setPhyDamage(character->getPhyDamage() + this->phyDamage);
        character->setMagDamage(character->getMagDamage() + this->magDamage);
        character->setPhysicalDefenseBonus(this->getPhyDefense());
        character->setMagicalDefenseBonus(this->getMagDefense());
        character->setRange(character->getRange() + this->length);
        for (const auto& effect : this->getEffects()) {
            effect->trigger(character);
        }
        equiped = true;
    } else {
        character->setPhyDamage(character->getPhyDamage() - this->phyDamage);
        character->setMagDamage(character->getMagDamage() - this->magDamage);
        character->setPhysicalDefenseBonus(-this->getPhyDefense());
        character->setMagicalDefenseBonus(-this->getMagDefense());
        character->setRange(character->getRange() - this->length);
        for (const auto& effect : this->getEffects()) {
            effect->trigger(character, true);
        }
        equiped = false;
    }
}

WeaponType Weapon::getWeaponType() const {
    return wType;
}

int Weapon::getPhyDamage() const {
    return phyDamage;
}

int Weapon::getMagDamage() const {
    return magDamage;
}

DamageType Weapon::getDamageType() const {
    return damageType;
}

bool Weapon::isTwoHanded() const {
    return twoHanded;
}

int Weapon::getLength() const {
    return length;
}

bool Weapon::isMagical() const {
    return magical;
}

Weapon::~Weapon() {}