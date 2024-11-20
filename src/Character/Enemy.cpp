#include "Enemy.h"

Enemy::Enemy(const std::string& name, SDL_Color color, GroupType group, 
            float hp, int mana, int energy, int stamina, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            float basicAggression, float basicFear, float bascDesire, float basicWander, float basicMisc)
 : Character(name, color, group, hp, mana, energy, stamina, fov, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck, symbol),
    basicAggression(basicAggression), basicFear(basicFear), bascDesire(bascDesire), basicWander(basicWander), basicMisc(basicMisc)
{
}

Enemy::~Enemy()
{
}

void Enemy::check()
{
    // Check the enemy
}

void Enemy::update()
{
    // Update the enemy
}