#include "Enemy.h"
#include "../Manager/Game/MapManager.h"

Enemy::Enemy(const std::string& name, SDL_Color color, GroupType group, const std::string& imagePath, const std::string& description,
            float hp, int mana, int energy, int stamina, bool isAuraUser, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            std::vector<int> desire, std::vector<int> disgust,
            int minSpawnLevel, int maxSpawnLevel, int value,
            float basicAggression, float basicFear, float bascDesire, float basicWander, float basicMisc)
 : Character(name, color, group, imagePath, description, hp, mana, energy, stamina, isAuraUser, fov, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck, symbol, desire, disgust),
    minSpawnLevel(minSpawnLevel), maxSpawnLevel(maxSpawnLevel), value(value),
    actionType(ActionType::NONE), hasBeenAttacked(false),
    basicAggression(basicAggression), basicFear(basicFear), bascDesire(bascDesire), basicWander(basicWander), basicMisc(basicMisc),
    wanderValue(basicWander)
{
}

Enemy::Enemy(const Enemy& enemy)
    : Character(enemy),
    minSpawnLevel(enemy.minSpawnLevel), maxSpawnLevel(enemy.maxSpawnLevel), value(enemy.value),
    basicAggression(enemy.basicAggression), basicFear(enemy.basicFear), bascDesire(enemy.bascDesire), basicWander(enemy.basicWander), basicMisc(enemy.basicMisc)
{
}

Enemy* Enemy::clone() const {
    return new Enemy(*this);
}

Enemy::~Enemy()
{
}

UpdateState Enemy::update()
{   
    Character::update();
    this->hasWaited = false;
    this->hasMoved = false;
    this->hasAttack = false;
    this->addLastVisitedCell(&MapManager::instance().getCell(this->getXPosition(), this->getYPosition()));
    // TODO: first check if we're in a fight
    // If we're in a fight, don't bother checking our surroundings we have to fight
    // But if we have a range weapon, we can attack from a distance so we still have to move


    // Reset perceived combat strength
    this->ownPerceivedCombatStrength = this->ownCombatStrength;
    // First get what the character is seeing
    AICells visibleCells = MapManager::instance().calculateCharacterFov(this, this->getXPosition(), this->getYPosition(), this->getFov());
    
    // Pour chaque direction, on calcule la valeur d'agression 
    // North
    int aggression = 0;
    if (visibleCells.closestNorthCell != nullptr) {
        aggression = this->ownPerceivedCombatStrength * (6 - visibleCells.northDistance) + (2*this->basicAggression);
        visibleCells.nortValue += aggression;
        visibleCells.decision.aggression = aggression;
    }
    // South
    if (visibleCells.closestSouthCell != nullptr) {
        aggression = this->ownPerceivedCombatStrength * (6 - visibleCells.southDistance) + (2*this->basicAggression);
        visibleCells.southValue += aggression;
        visibleCells.decision.aggression = aggression;
    }
    // East
    if (visibleCells.closestEastCell != nullptr) {
        aggression = this->ownPerceivedCombatStrength * (6 - visibleCells.eastDistance) + (2*this->basicAggression);
        visibleCells.eastValue += aggression;
        visibleCells.decision.aggression = aggression;
    }
    // West
    if (visibleCells.closestWestCell != nullptr) {
        aggression = this->ownPerceivedCombatStrength * (6 - visibleCells.westDistance) + (2*this->basicAggression);
        visibleCells.westValue += aggression;
        visibleCells.decision.aggression = aggression;
    }

    // Set Action
    int max_action = std::max({
        visibleCells.decision.aggression,
        visibleCells.decision.fear,
        visibleCells.decision.desire,
        visibleCells.decision.wander,
        visibleCells.decision.misc
    });
    if (max_action == visibleCells.decision.aggression) {
        this->actionType = ActionType::ATTACK;
    } else if (max_action == visibleCells.decision.fear) {
        this->actionType = ActionType::MOVE;
    } else if (max_action == visibleCells.decision.desire) {
        this->actionType = ActionType::MOVE;
    } else if (max_action == visibleCells.decision.wander) {
        int random = RandomUtils::getRandomNumber(0, 1);
        if (random == 0) {
            this->actionType = ActionType::MOVE;
        } else {
            this->actionType = ActionType::WAIT;
            this->hasWaited = true;
        }
    } else if (max_action == visibleCells.decision.misc) {
        this->actionType = ActionType::MOVE;
    }

    // Set direction
    int max_val = std::max({
        visibleCells.nortValue,
        visibleCells.southValue,
        visibleCells.eastValue,
        visibleCells.westValue
    });
    std::pair<int, int> offset = {0, 0};
    Direction direction = Direction::None;
    if (max_val == visibleCells.nortValue) {
        offset = getDirectionOffset(Direction::North);
        direction = Direction::North;
    } else if (max_val == visibleCells.southValue) {
        offset = getDirectionOffset(Direction::South);
        direction = Direction::South;
    } else if (max_val == visibleCells.eastValue) {
        offset = getDirectionOffset(Direction::East);
        direction = Direction::East;
    } else if (max_val == visibleCells.westValue) {
        offset = getDirectionOffset(Direction::West);
        direction = Direction::West;
    }

    bool isTryingToAttack = false;
    Cell* target = nullptr;
    if (this->actionType == ActionType::MOVE) {
        // Move character
        int dx = offset.first;
        int dy = offset.second;
        if (MapManager::instance().canCharacterMove(this, dx, dy)) {
            this->move(dx, dy);
            MapManager::instance().moveCharacterInMap(this, dx, dy);
            this->addLastVisitedCell(&MapManager::instance().getCell(this->getXPosition(), this->getYPosition()));
            this->hasMoved = true;
        }
    } else if (this->actionType == ActionType::ATTACK) {
        if (!this->canAttack()) {
            // We can't attack, we need to move or wait
            this->actionType = ActionType::WAIT;
            this->hasWaited = true;
        } else {
            // Ok here we are attacking
            // First we need to get the target
            int targetDistance = 0;
            if (direction == Direction::North) {
                target = visibleCells.closestNorthCell;
                targetDistance = visibleCells.northDistance;
            } else if (direction == Direction::South) {
                target = visibleCells.closestSouthCell;
                targetDistance = visibleCells.southDistance;
            } else if (direction == Direction::East) {
                target = visibleCells.closestEastCell;
                targetDistance = visibleCells.eastDistance;
            } else if (direction == Direction::West) {
                target = visibleCells.closestWestCell;
                targetDistance = visibleCells.westDistance;
            }
            // Check if there is realy a target
            if (target == nullptr) {
                // No target, we can't attack
                this->actionType = ActionType::WAIT;
                this->hasWaited = true;    
            } else {
                // Then we need to check if we can reach the target
                if (this->getWeapon() != nullptr) {
                    Weapon* weapon = static_cast<Weapon*>(this->getWeapon());
                    if (weapon->getLength() >= targetDistance) {
                        // We can attack
                        isTryingToAttack = true;
                    } else {
                        // Out of reach, move to engage
                        // TODO: If the direction of movement is blocked, try pathfinding
                        // Move character
                        int dx = offset.first;
                        int dy = offset.second;
                        if (MapManager::instance().canCharacterMove(this, dx, dy)) {
                            this->move(dx, dy);
                            MapManager::instance().moveCharacterInMap(this, dx, dy);
                            this->hasMoved = true;
                        }
                    }
                } else {
                    if (targetDistance <= 1) {
                        // We can attack
                        isTryingToAttack = true;
                    } else {
                        // Out of reach, move to engage
                        // TODO: If the direction of movement is blocked, try pathfinding
                        // Move character
                        int dx = offset.first;
                        int dy = offset.second;
                        if (MapManager::instance().canCharacterMove(this, dx, dy)) {
                            this->move(dx, dy);
                            MapManager::instance().moveCharacterInMap(this, dx, dy);
                            this->hasMoved = true;
                        }
                    }
                }
            }
        }
    }

    this->aiCells = visibleCells;

    if (hasMoved || hasWaited) {
        if (!overweight && this->stamina < this->maxStamina) {
            this->stamina += 1;
        } else if (overweight && this->stamina > 0) {
            this->stamina -= 1;
        }
    }

    // Update hasMoved and hasAttack and call updateProgress
    Character::updateProgress();

    UpdateState state;
    state.hasPlayed = !isTryingToAttack;
    state.target = target;
    state.actionType = this->actionType;
    state.isAI = true;
    
    return state;
}

int Enemy::getValue() const {
    return value;
}

void Enemy::addLastVisitedCell(Cell* cell) {
    // Allow the 5 last visited cells
    // When adding a new one, remove the oldest one
    if (lastVisitedCells.size() >= 5) {
        lastVisitedCells.erase(lastVisitedCells.begin());
    }
    // Check if the cell is already in the list
    auto it = std::find(lastVisitedCells.begin(), lastVisitedCells.end(), cell);
    if (it != lastVisitedCells.end()) {
        // If it is, remove it to update it's order
        lastVisitedCells.erase(it);
    }
    // Add the new cell
    lastVisitedCells.push_back(cell);
}

std::vector<Cell*>& Enemy::getLastVisitedCells() {
    return lastVisitedCells;
}

bool Enemy::isLastVisitedCell(Cell* cell) const {
    // Check if the cell is in the list
    auto it = std::find(lastVisitedCells.begin(), lastVisitedCells.end(), cell);
    return it != lastVisitedCells.end();
}

int Enemy::getBasicAggression() const {
    return basicAggression;
}

int Enemy::getBasicFear() const {
    return basicFear;
}

int Enemy::getBasicDesire() const {
    return bascDesire;
}

int Enemy::getBasicWander() const {
    return basicWander;
}

int Enemy::getBasicMisc() const {
    return basicMisc;
}

int Enemy::getWanderValue() const {
    return wanderValue;
}

void Enemy::setWanderValue(int value) {
    wanderValue = value;
}

AICells Enemy::getAICells() const {
    return this->aiCells;   
}

ActionType Enemy::getActionType() const {
    return this->actionType;
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