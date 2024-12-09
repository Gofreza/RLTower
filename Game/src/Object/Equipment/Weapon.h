#pragma once

#include "Equipment.h"
#include "../WeaponType.h"
#include "../DamageType.h"

class Weapon : public Equipment
{
public:
    Weapon(short id, 
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
        int phyDefense, int magDefense,
        std::string imagePath,
        std::vector<Effect*> effects,
        std::array<int, 5> requirements);
    ~Weapon();

    Weapon(const Weapon& weapon);
    virtual Weapon* clone() const override;

    void use(Character* character) override;

    WeaponType getWeaponType() const;
    int getPhyDamage() const;
    int getMagDamage() const;
    DamageType getDamageType() const;
    bool isTwoHanded() const;
    int getLength() const;
    bool isMagical() const;
private:
    WeaponType wType;
    int phyDamage;
    int magDamage;
    DamageType damageType;
    bool twoHanded;
    int length;
    bool magical;
};
