#include "Enemy.h"
#include "../Manager/Game/MapManager.h"

Enemy::Enemy(const std::string& name, SDL_Color color, GroupType group, 
            float hp, int mana, int energy, int stamina, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            std::vector<int> desire, std::vector<int> disgust,
            int minSpawnLevel, int maxSpawnLevel, int value,
            float basicAggression, float basicFear, float bascDesire, float basicWander, float basicMisc)
 : Character(name, color, group, hp, mana, energy, stamina, fov, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck, symbol, desire, disgust),
    minSpawnLevel(minSpawnLevel), maxSpawnLevel(maxSpawnLevel), value(value),
    basicAggression(basicAggression), basicFear(basicFear), bascDesire(bascDesire), basicWander(basicWander), basicMisc(basicMisc)
{
}

Enemy::Enemy(const Enemy& enemy)
    : Character(enemy),
    minSpawnLevel(enemy.minSpawnLevel), maxSpawnLevel(enemy.maxSpawnLevel), value(enemy.value),
    basicAggression(enemy.basicAggression), basicFear(enemy.basicFear), bascDesire(enemy.bascDesire), basicWander(enemy.basicWander), basicMisc(enemy.basicMisc)
{
}

Enemy::~Enemy()
{
}

AIDecision Enemy::check()
{
    // Check the enemy, see it's state and what will it's next move be
    return AIDecision();
}

bool Enemy::update()
{
    AIDecision decision = this->check();
    // Move, attack, etc
    int dx = RandomUtils::getRandomNumber(-1, 1);
    int dy = RandomUtils::getRandomNumber(-1, 1);
    if (MapManager::instance().canCharacterMove(this, dx, dy)) {
        this->move(dx, dy);
        MapManager::instance().moveCharacterInMap(this, dx, dy);
        this->hasMoved = true;
    }

    // Update hasMoved and hasAttack and call updateProgress
    Character::updateProgress();
    
    return true;
}

int Enemy::getValue() const {
    return value;
}

Enemy* Enemy::clone() const {
    return new Enemy(*this);
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy)
{   
    SDL_Color color = enemy.getColor();
    os << "Enemy: " << enemy.getName() << std::endl;
    os << "Symbol: " << enemy.getSymbol() << std::endl;
    os << "SDL_Color: R=" << static_cast<int>(color.r)
              << ", G=" << static_cast<int>(color.g)
              << ", B=" << static_cast<int>(color.b)
              << ", A=" << static_cast<int>(color.a) << std::endl;
    os << "Group: " << to_string(enemy.group) << std::endl;
    os << "Value: " << enemy.value << std::endl;
    os << "Basic Aggression: " << enemy.basicAggression << std::endl;
    os << "Basic Fear: " << enemy.basicFear << std::endl;
    os << "Basic Desire: " << enemy.bascDesire << std::endl;
    os << "Basic Wander: " << enemy.basicWander << std::endl;
    os << "Basic Misc: " << enemy.basicMisc << std::endl;
    os << "Min Spawn Level: " << enemy.minSpawnLevel << std::endl;
    os << "Max Spawn Level: " << enemy.maxSpawnLevel << std::endl;
    os << "HP: " << enemy.getHp() << std::endl;
    os << "Mana: " << enemy.getMana() << std::endl;
    os << "Energy: " << enemy.getEnergy() << std::endl;
    os << "Stamina: " << enemy.getStamina() << std::endl;
    os << "FOV: " << enemy.getFov() << std::endl;
    os << "Speed: " << enemy.getSpeed() << std::endl;
    os << "Phy. Damage: " << enemy.getPhyDamage() << std::endl;
    os << "Mag. Damage: " << enemy.getMagDamage() << std::endl;
    os << "Strength: " << enemy.strength << std::endl;
    os << "Dexterity: " << enemy.dexterity << std::endl;
    os << "Intelligence: " << enemy.intelligence << std::endl;
    os << "Wisdom: " << enemy.wisdom << std::endl;
    os << "Constitution: " << enemy.constitution << std::endl;
    os << "Luck: " << enemy.luck << std::endl;
    os << "Gold: " << enemy.getGold() << std::endl;
    os << "Silver: " << enemy.getSilver() << std::endl;
    os << "Copper: " << enemy.getCopper() << std::endl;
    if (enemy.getLeftHand() != nullptr)
        os << "Left Hand: " << enemy.getLeftHand()->getName() << std::endl;
    if (enemy.getRightHand() != nullptr)
        os << "Right Hand: " << enemy.getRightHand()->getName() << std::endl;
    if (enemy.getHead() != nullptr)
        os << "Head: " << enemy.getHead()->getName() << std::endl;
    if (enemy.getTorso() != nullptr)
        os << "Torso: " << enemy.getTorso()->getName() << std::endl;
    if (enemy.getHands() != nullptr) 
        os << "Hands: " << enemy.getHands()->getName() << std::endl;
    if (enemy.getBoots() != nullptr) 
        os << "Boots: " << enemy.getBoots()->getName() << std::endl;
    if (enemy.getRing1() != nullptr)
        os << "Ring 1: " << enemy.getRing1()->getName() << std::endl;
    if (enemy.getRing2() != nullptr)
        os << "Ring 2: " << enemy.getRing2()->getName() << std::endl;
    if (enemy.getAmulet() != nullptr)
        os << "Amulet: " << enemy.getAmulet()->getName() << std::endl;
    os << "Desires: ";
    for (auto& desire : enemy.desires) {
        os << desire << " ";
    }
    os << std::endl;
    os << "Disgusts: ";
    for (auto& disgust : enemy.disgusts) {
        os << disgust << " ";
    }
    os << std::endl;
    return os;
}