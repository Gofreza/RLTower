#include "Player.h"

Player::Player(float hp, int mana, int energy, int stamina, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck)
 : Character(hp, mana, energy, stamina, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck)
{
}

Player::~Player()
{
}