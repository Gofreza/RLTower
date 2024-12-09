#pragma once

#include "Misc.h"
#include "../DamageType.h"

class Projectile : public Misc
{
public:
    Projectile(short id, const std::string& name, const std::string& description, ItemType type, float weight, RarityType rarity,
            int damage, DamageType damageeType);
    ~Projectile();
    Projectile(const Projectile& projectile);

    virtual Projectile* clone() const override;

    int getDamage() const;
    DamageType getDamageType() const;
private:
    int damage;
    DamageType damageType;
};

