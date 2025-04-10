#include "Projectile.h"

Projectile::Projectile(short id, const std::string& name, const std::string& description, ItemType type, float weight, RarityType rarity,
                    std::string imagePath,
                    int damage, DamageType damageType)
: Misc(id, name, description, type, weight, rarity, imagePath), damage(damage), damageType(damageType)
{
}

Projectile::Projectile(const Projectile& projectile)
: Misc(projectile.getId(), projectile.getName(), projectile.getDescription(), projectile.getType(), projectile.getWeight(), projectile.getRarity(), projectile.getImagePath()),
    damage(projectile.getDamage()), damageType(projectile.getDamageType())
{
}

Projectile* Projectile::clone() const {
    return new Projectile(*this); 
}

int Projectile::getDamage() const {
    return damage;
}

DamageType Projectile::getDamageType() const {
    return damageType;
}

Projectile::~Projectile()
{
}
