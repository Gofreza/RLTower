#include "Character.h"
#include <cmath>
#include "../Manager/Item/ItemManager.h"
#include "../Manager/Spell/SpellManager.h"
#include "../Manager/Game/GameManager.h"
#include "../Manager/Game/MapManager.h"
#include "../Map/Cell.h"

static float SPEED_SCALAR = 10.0f;

static float PHY_DEFENSE_SCALAR = 0.20f;
static float MAG_DEFENSE_SCALAR = 0.20f;
static float MAX_WEIGHT_SCALAR = 10.0f;

static float DODGE_SCALAR = 1.0f;
static float DODGE_DEXTERITY_SCALAR = 0.7f;
static float DODGE_LUCK_SCALAR = 0.3f;

Character::Character(const std::string& name, SDL_Color color, GroupType group, const std::string& imagePath, const std::string& description, float hp, int mana, int energy, int stamina, bool isAuraUser, int fov, int speed,
                    int phyDamage, int magDamage, int strength, int dexterity,
                    int intelligence, int wisdom, int constitution, int luck,
                    const char symbol,
                    std::vector<int> desires, std::vector<int> disgusts)
    : name(name), color(color), group(group), imagePath(imagePath), description(description), xPosition(0), yPosition(0), 
    gold(0), silver(0), copper(0), symbol(symbol),
    hp(hp), mana(mana), energy(energy), stamina(stamina), 
    maxHp(hp), maxMana(mana), maxEnergy(energy), maxStamina(stamina),
    // Level
    level(0), experience(0), isAuraUser(isAuraUser),
    // Fov
    baseFov(fov), fov(fov),
    // Speed
    baseSpeed(speed), speed(0), 
    // Progress
    characterProgress(new CharacterProgress(this)), hasWaited(false), overweight(false), hasDodge(false), hasCastSpell(false), hasFoundAncientSite(false), hasHealDamage(false),
    fatigue(0), exhausted(false), hasMoved(false), hasAttack(false),
    // Stats
    phyDamage(phyDamage), magDamage(magDamage), baseRange(1), range(1),
    strength(strength), dexterity(dexterity), intelligence(intelligence), wisdom(wisdom), constitution(constitution), luck(luck),
    // Stats Dependants
    physicalDefense(0), magicalDefense(0), weight(0.f), maxWeight(0), dodge(0.0f),
    // Bonus
    magicalDefenseBonus(0), physicalDefenseBonus(0), speedBonus(0), dodgeBonus(0.f),
    // Resistances
    fireResistance(0.0f), waterResistance(0.0f), earthResistance(0.0f), airResistance(0.0f),
    lightningResistance(0.0f), iceResistance(0.0f), natureResistance(0.0f),
    lightResistance(0.0f), darknessResistance(0.0f), arcaneResistance(0.0f),
    poisonResistance(0.0f), metalResistance(0.0f), soundResistance(0.0f),
    illusionResistance(0.0f),
    // IA
    ownCombatStrength(0), ownPerceivedCombatStrength(0),
    // Desire
    desires(desires), disgusts(disgusts),
    // Spells
    currentActiveSpell(nullptr)
{
    leftHand = nullptr;
    rightHand = nullptr;
    head = nullptr;
    torso = nullptr;
    hands = nullptr;
    boots = nullptr;
    ring1 = nullptr;
    ring2 = nullptr;
    amulet = nullptr;
    updateStatsDependants();
}

Character::Character(const Character& other)
    : name(other.name), color(other.color), group(other.group), imagePath(other.imagePath), description(other.description), xPosition(other.xPosition), yPosition(other.yPosition), 
    gold(other.gold), silver(other.silver), copper(other.copper), symbol(other.symbol),
    hp(other.hp), mana(other.mana), energy(other.energy), stamina(other.stamina), 
    maxHp(other.maxHp), maxMana(other.maxMana), maxEnergy(other.maxEnergy), maxStamina(other.maxStamina),
    // Level
    level(other.level), experience(other.experience), isAuraUser(other.isAuraUser),
    // Fov
    baseFov(other.baseFov), fov(other.fov),
    // Speed
    baseSpeed(other.baseSpeed), speed(other.speed), 
    // Progress
    characterProgress(new CharacterProgress(*other.characterProgress)), hasWaited(other.hasWaited), overweight(other.overweight), hasDodge(other.hasDodge), hasCastSpell(other.hasCastSpell), hasFoundAncientSite(other.hasFoundAncientSite), hasHealDamage(other.hasHealDamage),
    fatigue(other.fatigue), exhausted(other.exhausted), hasMoved(other.hasMoved), hasAttack(other.hasAttack),
    // Stats
    phyDamage(other.phyDamage), magDamage(other.magDamage), strength(other.strength),
    dexterity(other.dexterity), intelligence(other.intelligence), wisdom(other.wisdom), constitution(other.constitution), luck(other.luck),
    // Stats Dependants
    physicalDefense(other.physicalDefense), magicalDefense(other.magicalDefense), weight(other.weight), maxWeight(other.maxWeight), dodge(other.dodge),
    // Bonus
    magicalDefenseBonus(other.magicalDefenseBonus), physicalDefenseBonus(other.physicalDefenseBonus), speedBonus(other.speedBonus), dodgeBonus(other.dodgeBonus),
    // Resistances
    fireResistance(other.fireResistance), waterResistance(other.waterResistance), earthResistance(other.earthResistance), airResistance(other.airResistance),
    lightningResistance(other.lightningResistance), iceResistance(other.iceResistance), natureResistance(other.natureResistance),
    lightResistance(other.lightResistance), darknessResistance(other.darknessResistance), arcaneResistance(other.arcaneResistance),
    poisonResistance(other.poisonResistance), metalResistance(other.metalResistance), soundResistance(other.soundResistance),
    illusionResistance(other.illusionResistance),
    // IA
    ownCombatStrength(other.ownCombatStrength), ownPerceivedCombatStrength(other.ownPerceivedCombatStrength),
    // Desire
    desires(other.desires), disgusts(other.disgusts),
    // Spells
    currentActiveSpell(other.currentActiveSpell)
{
    leftHand = other.leftHand ? ItemManager::instance().getItem(other.leftHand->getId()) : nullptr;
    rightHand = other.rightHand ? ItemManager::instance().getItem(other.rightHand->getId()) : nullptr;
    head = other.head ? ItemManager::instance().getItem(other.head->getId()) : nullptr;
    torso = other.torso ? ItemManager::instance().getItem(other.torso->getId()) : nullptr;
    hands = other.hands ? ItemManager::instance().getItem(other.hands->getId()) : nullptr;
    boots = other.boots ? ItemManager::instance().getItem(other.boots->getId()) : nullptr;
    ring1 = other.ring1 ? ItemManager::instance().getItem(other.ring1->getId()) : nullptr;
    ring2 = other.ring2 ? ItemManager::instance().getItem(other.ring2->getId()) : nullptr;
    amulet = other.amulet ? ItemManager::instance().getItem(other.amulet->getId()) : nullptr;

    for (const auto& item : other.inventory) {
        inventory.push_back(ItemManager::instance().getItem(item->getId()));
    }

    for (const auto& spell : other.spells) {
        spells.push_back(SpellManager::instance().getSpell(spell->getId()));
    }
}

Character::~Character()
{
    delete(characterProgress);

    for (Item* item : inventory) {
        delete item;
    }
    inventory.clear();

    if (leftHand) {
        if (leftHand->getType() == ItemType::Weapon) {
            Weapon* weapon = static_cast<Weapon*>(leftHand);
            if (weapon->isTwoHanded())
                rightHand = nullptr;
        } 
        delete leftHand;       
    }
    if (rightHand)
        delete rightHand;
    if (head)
        delete head;
    if (torso)
        delete torso;
    if (hands)
        delete hands;
    if (boots)
        delete boots;
    if (ring1)
        delete ring1;
    if (ring2)
        delete ring2;
    if (amulet)
        delete amulet;

    for (Effect* effect : effects) {
        delete effect;
    }
}

void Character::updateStatsDependants() {
    // Speed
    if (exhausted) {
        speed = 0;
    } else if (overweight) {
        // Check for 175% weight 
        if (weight > maxWeight + maxWeight / 4 * 3) {
            speed = 0;
        } 
        // Check for 150% weight
        else if (weight > maxWeight + maxWeight / 2) {
            speed = std::round((baseSpeed + std::log10(dexterity * dexterity) * SPEED_SCALAR) / 4) + speedBonus;
        } 
        // Default overweight case
        else {
            speed = std::round((baseSpeed + std::log10(dexterity * dexterity) * SPEED_SCALAR) / 2) + speedBonus;
        }
    } else
        speed = std::round(baseSpeed + std::log10(dexterity * dexterity) * SPEED_SCALAR) + speedBonus;          

    // Phy. Defense
    physicalDefense = std::floor(this->constitution * PHY_DEFENSE_SCALAR) + physicalDefenseBonus;

    // Mag. Defense
    magicalDefense = std::floor(this->wisdom * MAG_DEFENSE_SCALAR) + magicalDefenseBonus;

    // Max Weight
    maxWeight = this->strength * MAX_WEIGHT_SCALAR;

    // Dodge
    dodge = DODGE_SCALAR * (DODGE_DEXTERITY_SCALAR * this->dexterity + DODGE_LUCK_SCALAR * this->luck) + dodgeBonus;

    // CombatStrength
    ownCombatStrength = phyDamage + magDamage + strength + dexterity + intelligence + wisdom + constitution + luck;
}

void Character::updateProgress() {
    // TODO: Check that everything is done
    // Fatigue
    if (fatigue >= 100) {
        exhausted = true;
    }
    
    // Level
    characterProgress->levelUp();

    // Progress
    if (hasMoved) {
        characterProgress->progress();
        hasMoved = false;
    } else {
        if (hasWaited) {
            if (fatigue > 0) {
                fatigue--;
            }
            if (fatigue < 100) {
                exhausted = false;
            }
        } 

        if (hasAttack) {
            hasAttack = false;
        }
    }

    updateStatsDependants();
}

bool Character::update() {
    // Process Effects
    for (auto it = effects.begin(); it != effects.end(); ) {
        Effect* effect = *it;
        if (effect->getEffectType() != EffectType::Temporary) {
            effect->trigger(this);
        }
        effect->reduceDuration();
        if (effect->getDuration() <= 0) {
            if (effect->getEffectType() == EffectType::Temporary) {
                effect->trigger(this, true);
            }
            delete effect;
            it = effects.erase(it);
        } else {
            ++it;
        }
    }

    return true;
}

//===============
// POSITION
//===============

int Character::getXPosition() const {
    return xPosition;
}

void Character::setXPosition(int xPosition) {
    this->xPosition = xPosition;
}

int Character::getYPosition() const {
    return yPosition;
}

void Character::setYPosition(int yPosition) {
    this->yPosition = yPosition;
}

void Character::move(int x, int y) {
    xPosition += x;
    yPosition += y;
    hasMoved = true;
    hasAttack = false;
}

//===============
// MONEY
//===============

int Character::getGold() const {
    return gold;
}

void Character::setGold(int gold) {
    this->gold = gold;
}

int Character::getSilver() const {
    return silver;
}

void Character::setSilver(int silver) {
    this->silver = silver;
}

int Character::getCopper() const {
    return copper;
}

void Character::setCopper(int copper) {
    this->copper = copper;
}

//===============
// INVENTORY
//===============

void Character::addItemInInventory(Item* item) {
    this->weight += item->getWeight();
    Item* newItem = item; //item->clone();

    // If new items is a containers, check for possible objects to put in
    if (newItem->getType() == ItemType::Container) {
        Containers* c = static_cast<Containers*>(newItem);
        c->use(this);
    }
    
    this->inventory.push_back(newItem);

    // If there is a container, use it in case the new object can be added in
    // Beware, using for loop here break because we reduce the size of the inventory when a Container 
    // is used, so we need to use an iterator
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        Item* item = *it;
        if (item->getType() == ItemType::Container) {
            Containers* c = static_cast<Containers*>(item);
            c->use(this);
        }
    }

    float fmaxWeight = this->maxWeight;
    if (this->weight > fmaxWeight) {        
        Logger::instance().info(LocalizationManager::instance().getText("too_heavy_message"));
        overweight = true;
        updateStatsDependants();
    }
}

void Character::addBackItemInInventory(Item* item) {
    this->weight += item->getWeight();
    inventory.push_back(item);

    if (this->weight > this->maxWeight) {
        Logger::instance().info(LocalizationManager::instance().getText("too_heavy_message"));  
        overweight = true;
        updateStatsDependants();
    }
}

std::vector<Item*>& Character::getInventory() {
    return inventory;
}

void Character::removeItemFromInventory(Item* item, bool drop) {
    if (isEquipedItem(item)) {
        unequipItem(item);
    }
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
    // Update weight
    this->weight -= item->getWeight();
    if (this->weight > this->maxWeight) {
        overweight = true;
        updateStatsDependants();
    }
    if (!drop) {
        ItemManager::instance().addItemToDeferredDeletions(item);
        //delete (item);
    }
}

//===============
// Spells
//===============

void Character::addSpellInSpellBook(Spell* spell) {
    spells.push_back(spell);
}

std::vector<Spell*> Character::getSpells() const {
    return spells;
}

//===============
// COMBAT
//===============

void Character::attack(Cell& cell, std::vector<Cell*>& cellsAffectedByEffects) {
    bool isAttacking = false;
    // Check if the attacker can attack
    // Check for mana/energy for spells or stamina for physical attacks
    if (isAuraUser) {
        // TODO implement this correctly
        Logger::instance().info(this->name + " is an aura user. Implement this in Character.cpp.");
    } else {
        Item* weapon = this->getWeapon();
        if (weapon) {
            Weapon* w = static_cast<Weapon*>(weapon);
            if (is_weapon_magical(w->getWeaponType()) && this->getCurrentActiveSpell() != nullptr) {
                if (this->mana < this->getCurrentActiveSpell()->getConsumption()) {
                    Logger::instance().info(this->name + " doesn't have enough mana to cast the spell.");
                    return;
                }

                // Check spell type
                SpellType sType = this->getCurrentActiveSpell()->getType();
                isAttacking = sType == SpellType::Attack;
            } else {
                if (this->stamina < w->getWeight()) {
                    Logger::instance().info(this->name + " doesn't have enough stamina to attack.");
                    return;
                }
                isAttacking = true;
            }
        } else {
            if (this->stamina < 1) {
                Logger::instance().info(this->name + " doesn't have enough stamina to attack.");
                return;
            }
            isAttacking = true;
        }
        this->hasAttack = true;
        if (cell.getCharacter() != nullptr) {
            Character* target = cell.getCharacter();
            Logger::instance().info(this->name + " attacks " + target->name + ".");
            if (isAttacking) {
                target->defend(cell, this, cellsAffectedByEffects);
            } else {
                target->support(cell, cellsAffectedByEffects);
            }
        } else {
            // Attack the cell
            if (this->getCurrentActiveSpell() == nullptr) {
                // Check for effects on non magic weapon
                if (weapon) {
                    Weapon* w = static_cast<Weapon*>(weapon);
                    if (w->getEffects().size() > 0) {
                        for (Effect* effect : w->getEffects()) {
                            cell.addEffect(effect->clone());
                        }
                    }
                    cellsAffectedByEffects.push_back(&cell);
                }
                return;
            }
    
            std::vector<std::pair<int, int>> affectedCells;
            MapManager::instance().getAffectedCells(cell.getX(), cell.getY(), this->getCurrentActiveSpell()->getRadius(), affectedCells);
            // Remove mana only once
            this->mana -= this->getCurrentActiveSpell()->getConsumption();
            for (const auto& affectedCell : affectedCells) {
                // Attack all the cells
                int x = affectedCell.first;
                int y = affectedCell.second;
                Cell& targetCell = MapManager::instance().getCell(x, y); 
                // Add effects to targetedCells
                for (Effect* effect : this->getCurrentActiveSpell()->getEffects()) {
                    if (effect->getEffectType() != EffectType::Burst) {
                        targetCell.addEffect(effect->clone());
                    }
                }             
                cellsAffectedByEffects.push_back(&targetCell);  
                // Check for character in the cell
                Character* targetCharacter = targetCell.getCharacter();
                if (targetCharacter != nullptr) {
                    // Add effects to character
                    for (Effect* effect : this->getCurrentActiveSpell()->getEffects()) {
                        if (effect->getEffectType() != EffectType::Burst) {
                            targetCharacter->addEffect(effect->clone());
                        }
                    }

                    // Damage calculation
                    int distance = Utils::distance(cell.getX(), cell.getY(), targetCharacter->getXPosition(), targetCharacter->getYPosition());
                    int damage = this->magDamage + this->getCurrentActiveSpell()->getDamage() - targetCharacter->magicalDefense - distance;
                    targetCharacter->hp -= damage < 0 ? 0 : damage;
                }
            }
        }
        
    }
}

void Character::defend(Cell& cell, Character* attacker, std::vector<Cell*>& cellsAffectedByEffects) {
    Logger::instance().info(this->name + " defends against " + attacker->name + ".");
    // Before applying the damage, check if the attacker can parry, if can't try dodging
    Item* shield = this->getShield();
    if (shield) {
        Shield* s = static_cast<Shield*>(shield);
        if (s->block()) {
            Logger::instance().info(this->name + " parries the attack.");
            return;
        }
    }
    // Try dodging
    if (this->canDodge()) {
        Logger::instance().info(this->name + " dodges the attack.");
        this->hasDodge = true;
        return;
    }

    // Check the attacker weapon
    Item* weapon = attacker->getWeapon();
    if (weapon) {
        Weapon* w = static_cast<Weapon*>(weapon);
        WeaponType wType = w->getWeaponType();
        
        if (isAuraUser) {
            // TODO: Implement this correctly
            Logger::instance().info(this->name + " is an aura user.");
        } else {
            if (is_weapon_magical(wType) && attacker->getCurrentActiveSpell() != nullptr) {
                // Use magical weapon
                this->hasCastSpell = true;
                int damage = attacker->getMagDamage() + attacker->getCurrentActiveSpell()->getDamage() - this->magicalDefense;
                this->hp -= damage < 0 ? 0 : damage;
                attacker->mana -= attacker->getCurrentActiveSpell()->getConsumption();
                // Apply effect to the defender
                for (Effect* effect : attacker->getCurrentActiveSpell()->getEffects()) {
                    if (effect->getEffectType() != EffectType::Burst) {
                        this->addEffect(effect->clone());
                    }
                }

                // Check spell radius
                if (attacker->getCurrentActiveSpell()->getRadius() > 0) {
                    Logger::instance().info(this->name + " is affected by the spell " + attacker->getCurrentActiveSpell()->getName() + ".");
                    // Apply the damage on the cells around the target minus the distance and apply effects
                    std::vector<std::pair<int, int>> affectedCells;
                    MapManager::instance().getAffectedCells(cell.getX(), cell.getY(), attacker->getCurrentActiveSpell()->getRadius(), affectedCells);
                    for (const auto& affectedCell : affectedCells) {
                        // Apply effects to the cells (all of them)
                        for (Effect* effect : attacker->getCurrentActiveSpell()->getEffects()) {
                            if (effect->getEffectType() != EffectType::Burst) {
                                MapManager::instance().getCell(affectedCell.first, affectedCell.second).addEffect(effect->clone());
                            }
                        }
                        cellsAffectedByEffects.push_back(&MapManager::instance().getCell(affectedCell.first, affectedCell.second));

                        // Attack all cell except the one where the defender is (because it as already been attacked)
                        if (affectedCell.first == cell.getX() && affectedCell.second == cell.getY()) {
                            continue;
                        }
                        int x = affectedCell.first;
                        int y = affectedCell.second;
                        Cell& targetCell = MapManager::instance().getCell(x, y);
                        Character* targetCharacter = targetCell.getCharacter();
                        if (targetCharacter != nullptr && targetCharacter != this) {
                            int distance = std::sqrt(std::pow(targetCharacter->getXPosition() - x, 2) + std::pow(targetCharacter->getYPosition() - y, 2));
                            int damage = attacker->getMagDamage() + attacker->getCurrentActiveSpell()->getDamage() - targetCharacter->magicalDefense - distance;
                            targetCharacter->hp -= damage < 0 ? 0 : damage;
                            // Apply effects to the character
                            for (Effect* effect : attacker->getCurrentActiveSpell()->getEffects()) {
                                if (effect->getEffectType() != EffectType::Burst) {
                                    targetCharacter->addEffect(effect->clone());
                                }
                            }
                        }
                    }
                }
            } else {
                // Use physical weapon
                int damage = attacker->getPhyDamage() - this->physicalDefense;
                this->hp -= damage < 0 ? 0 : damage;
                attacker->stamina -= w->getWeight();

                // Apply effects to the defender and the cell
                for (Effect* effect : w->getEffects()) {
                    if (effect->getEffectType() != EffectType::Burst) {
                        this->addEffect(effect->clone());
                        cell.addEffect(effect->clone());
                    }
                }
                cellsAffectedByEffects.push_back(&cell);
            }
        }
    } else {
        // If the attacker has no weapon, use fists (base phyDamage)
        int damage = attacker->getPhyDamage() - this->physicalDefense;
        this->hp -= damage < 0 ? 0 : damage;
        attacker->stamina -= 1;
    }
}

void Character::support(Cell& cell, std::vector<Cell*>& cellsAffectedByEffects) {
    //TODO: For effects, add a flag to know if the effect need to be applied to the cell too
    Character* target = cell.getCharacter();
    // We're sure we have a spell here
    Spell* spell = this->getCurrentActiveSpell();
    // Apply the effects of the spell
    for (Effect* effect : spell->getEffects()) {
        if (effect->getEffectType() != EffectType::Burst) {
            this->addEffect(effect->clone());
        }
        effect->trigger(target);
    }
    this->mana -= spell->getConsumption();
    this->hasCastSpell = true;
}

bool Character::canDodge() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 100);

    int random_number = distr(gen);

    return random_number <= this->dodge;
}

//===============
// EQUIPMENTS
//===============

void Character::equipItem(Item* item) {
    std::array<int, 5> requirements = item->getRequirements();

    // Check for requirements
    if (!(requirements.at(0) == -1)) {
        if (this->strength < requirements.at(0)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_strength"));
            }
            return;
        }

        if (this->dexterity < requirements.at(1)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_dexterity"));
            }
            return;
        }
        
        if (this->intelligence < requirements.at(2)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_intelligence"));
            }
            return;
        }
        
        if (this->wisdom < requirements.at(3)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_wisdom"));
            }
            return;
        } 
        
        if (this->constitution < requirements.at(4)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_constitution"));
            }
            return;
        }
    }

    bool isEquiped = false;

    if (item->getType() == ItemType::Weapon) {
        isEquiped = equipWeapons(item);
    } else if (item->getType() == ItemType::Shield) {
        isEquiped = equipShield(item);
    } else if (item->getType() == ItemType::Helmet) {
        isEquiped = equipHead(item);
    } else if (item->getType() == ItemType::Gloves) {
        isEquiped = equipHands(item);
    } else if (item->getType() == ItemType::ChestArmor) {
        isEquiped = equipTorso(item);
    } else if (item->getType() == ItemType::LegArmor) {
        isEquiped = equipBoots(item);
    } else if (item->getType() == ItemType::Ring) {
        isEquiped = equipRing(item);
    } else if (item->getType() == ItemType::Amulet) {
        isEquiped = equipAmulet(item);
    } else if (item->getType() == ItemType::Consumable) {
        isEquiped = useConsumable(item);
    } else if (item->getType() == ItemType::Projectile) {
        
    } else if (item->getType() == ItemType::Container) {
        
    } else {
        throw std::runtime_error("Error ItemType unknown (Player.cpp).");
    }

    if (isEquiped) {
        // Update weight
        this->weight -= item->getWeight();
        
        if (overweight) {
            if (this->weight <= this->maxWeight) {
                overweight = false;
            }
        }

        // Update stats
        updateStatsDependants();
    }
    
}

void Character::unequipItem(Item* item) {
    if (item == leftHand) {
        unequipLeftWeapon();
    } else if (item == rightHand) {
        unequipRightWeapon();
    } else if (item == head) {
        unequipHead();
    } else if (item == torso) {
        unequipTorso();
    } else if (item == hands) {
        unequipHands();
    } else if (item == boots) {
        unequipBoots();
    } else if (item == ring1) {
        unequipRing1();
    } else if (item == ring2) {
        unequipRing2();
    } else if (item == amulet) {
        unequipAmulet();
    }

    addBackItemInInventory(item);
    
    // Update stats
    updateStatsDependants();

    // No need to calculate weight here, done in addBackInInventory
    if (this->group == GroupType::Player) {
        Logger::instance().info(LocalizationManager::instance().getText("unequip") + item->getName() + ".");
    }
}

std::vector<Item*> Character::getEquipEquipments() {
    std::vector<Item*> equipments;

    equipments.push_back(this->leftHand);
    equipments.push_back(this->rightHand);
    equipments.push_back(this->head);
    equipments.push_back(this->torso);
    equipments.push_back(this->hands);
    equipments.push_back(this->boots);
    equipments.push_back(this->ring1);
    equipments.push_back(this->ring2);
    equipments.push_back(this->amulet);

    return equipments;    
}

bool Character::isEquipedItem(Item* item) {
    if (leftHand == item || rightHand == item || head == item ||
        torso == item || hands == item || boots == item || ring1 == item ||
        ring2 == item || amulet == item)
        return true;
    else
        return false;
}

// Weapons
bool Character::equipWeapons(Item* weapon) {
    Weapon* w = static_cast<Weapon*>(weapon);
    if (w->isTwoHanded())
    {
        if (!leftHand && !rightHand)
        {
            rightHand = weapon;
            leftHand = weapon;
            auto it = std::find(inventory.begin(), inventory.end(), weapon);
            if (it != inventory.end()) {
                inventory.erase(it);
            }
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("equip") + weapon->getName() + ".");
            }
            // Use the item to get the stats
            w->use(this);
            return true;
        } else {
            if (this->group == GroupType::Player) {
                Logger::instance().warning(LocalizationManager::instance().getText("empty_hands"));
            }
            return false;
        }
        
    } else {
        if (!leftHand) {
            // If not weapon on left hand equip here
            leftHand = weapon;
            auto it = std::find(inventory.begin(), inventory.end(), weapon);
            if (it != inventory.end()) {
                inventory.erase(it);
            }
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("equip") + weapon->getName() + ".");
            }
            // Use the item to get the stats
            w->use(this);
            return true;
        } else if (!rightHand) {
            // If not weapon on right hand equip here
            rightHand = weapon;
            auto it = std::find(inventory.begin(), inventory.end(), weapon);
            if (it != inventory.end()) {
                inventory.erase(it);
            }
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("equip") + weapon->getName() + ".");
            }
            // Use the item to get the stats
            w->use(this);
            return true;
        } else {
            // Weapons already equip
            // Can't equip need to de-equip before
            if (leftHand && rightHand) {
                if (this->group == GroupType::Player) {
                    Logger::instance().warning(LocalizationManager::instance().getText("empty_hands"));
                }
            } else {
                if (this->group == GroupType::Player) {
                    Logger::instance().warning(LocalizationManager::instance().getText("unequip_weapon"));
                } 
            }
            
            return false;
        }
    }
}

void Character::unequipLeftWeapon() {
    Equipment* e = static_cast<Equipment*>(leftHand);
    GameManager::instance().stopCombatMode();
    e->use(this);
    if (leftHand == rightHand)
    {
        this->leftHand = nullptr;
        this->rightHand = nullptr;
    } else {
        this->leftHand = nullptr;
    }
}

void Character::unequipRightWeapon() {
    Equipment* e = static_cast<Equipment*>(rightHand);
    GameManager::instance().stopCombatMode();
    e->use(this);
    if (rightHand == leftHand)
    {
        this->leftHand = nullptr;
        this->rightHand = nullptr;
    } else {
        this->rightHand = nullptr;
    }
}

Item* Character::getLeftHand() const {
    return this->leftHand;
}

Item* Character::getRightHand() const {
    return this->rightHand;
}

Item* Character::getWeapon() const {
    if (leftHand && leftHand->getType() == ItemType::Weapon) {
        return leftHand;
    } else if (rightHand && rightHand->getType() == ItemType::Weapon) {
        return rightHand;
    } else {
        return nullptr;
    }
}

// Shield
bool Character::equipShield(Item* shield) {
    Shield* s = static_cast<Shield*>(shield);
    if (!leftHand) {
        // If not weapon on left hand equip here
        leftHand = shield;
        auto it = std::find(inventory.begin(), inventory.end(), shield);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + shield->getName() + ".");
        }
        // Use items to get stats
        s->use(this);
        return true;
    } else if (!rightHand) {
        // If not weapon on right hand equip here
        rightHand = shield;
        auto it = std::find(inventory.begin(), inventory.end(), shield);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + shield->getName() + ".");
        }
        // Use items to get stats
        s->use(this);
        return true;
    } else {
        // Weapons already equip
        // Can't equip need to de-equip before
        if (leftHand && rightHand) {
            if (this->group == GroupType::Player) {
                Logger::instance().warning(LocalizationManager::instance().getText("empty_hands"));
            }
        } else {
            if (this->group == GroupType::Player) {
                Logger::instance().warning(LocalizationManager::instance().getText("unequip_weapon"));
            } 
        }
        return false;
    }
}

Item* Character::getShield() const {
    if (leftHand && leftHand->getType() == ItemType::Shield) {
        return leftHand;
    } else if (rightHand && rightHand->getType() == ItemType::Shield) {
        return rightHand;
    } else {
        return nullptr;
    }
}

// Head
bool Character::equipHead(Item* helmet) {
    Helmet* h = static_cast<Helmet*>(helmet);
    if (!head) {
        head = helmet;
        auto it = std::find(inventory.begin(), inventory.end(), helmet);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + helmet->getName() + ".");
        } 
        // Use item to get stats
        h->use(this);
        return true;
    } else {
        if (this->group == GroupType::Player) {
            Logger::instance().warning(LocalizationManager::instance().getText("unequip_helmet"));
        } 
        return false;
    }
    
}

void Character::unequipHead() {
    Helmet* h = static_cast<Helmet*>(this->head);
    h->use(this);
    this->head = nullptr;
}

Item* Character::getHead() const {
    return this->head;
}

// Torso
bool Character::equipTorso(Item* armor) {
    Chests* c = static_cast<Chests*>(armor);
    if (!torso) {
        torso = armor;
        auto it = std::find(inventory.begin(), inventory.end(), armor);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + armor->getName() + ".");
        }
        // Use item to get stats
        c->use(this);
        return true;
    } else {
        if (this->group == GroupType::Player) {
            Logger::instance().warning(LocalizationManager::instance().getText("unequip_chest"));
        } 
        return false;
    }
}

void Character::unequipTorso() {
    Chests* c = static_cast<Chests*>(this->torso);
    c->use(this);
    this->torso = nullptr;
}

Item* Character::getTorso() const {
    return this->torso;
}

// Hands
bool Character::equipHands(Item* glove) {
    Gloves* g = static_cast<Gloves*>(glove);
    if (!hands) {
        hands = glove;
        auto it = std::find(inventory.begin(), inventory.end(), glove);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + glove->getName() + ".");
        }
        // Use item to get stats
        g->use(this);
        return true;
    } else {
        if (this->group == GroupType::Player) {
            Logger::instance().warning(LocalizationManager::instance().getText("unequip_hands"));
        } 
        return false;
    }
}

void Character::unequipHands() {
    Gloves* g = static_cast<Gloves*>(this->hands);
    g->use(this);
    this->hands = nullptr;
}

Item* Character::getHands() const {
    return this->hands;
}

// Boots
bool Character::equipBoots(Item* armor) {
    Leggings* l = static_cast<Leggings*>(armor);
    if (!boots) {
        boots = armor;
        auto it = std::find(inventory.begin(), inventory.end(), armor);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + armor->getName() + ".");
        }
        // Use item to get stats
        l->use(this);
        return true;
    } else {
        if (this->group == GroupType::Player) {
            Logger::instance().warning(LocalizationManager::instance().getText("unequip_boots"));
        }
        return false;
    }
    
}

void Character::unequipBoots() {
    Leggings* l = static_cast<Leggings*>(this->boots);
    l->use(this);
    this->boots = nullptr;
}

Item* Character::getBoots() const {
    return this->boots;
}

// Ring
bool Character::equipRing(Item* ring) {
    Ring* r = static_cast<Ring*>(ring);
    if (!ring1) {
        // If not weapon on left hand equip here
        ring1 = ring;
        auto it = std::find(inventory.begin(), inventory.end(), ring);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + ring->getName() + ".");
        }
        // Use item to get stats
        r->use(this);
        return true;
    } else if (!ring2) {
        // If not weapon on right hand equip here
        ring2 = ring;
        auto it = std::find(inventory.begin(), inventory.end(), ring2);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + ring->getName() + ".");
        }
        // Use item to get stats
        r->use(this);
        return true;
    } else {
        if (this->group == GroupType::Player) {
            Logger::instance().warning(LocalizationManager::instance().getText("unequip_ring"));
        }
        return false;
    }
}

void Character::unequipRing1() {
    Ring* r = static_cast<Ring*>(this->ring1);
    r->use(this);
    this->ring1 = nullptr;
}

void Character::unequipRing2() {
    Ring* r = static_cast<Ring*>(this->ring2);
    r->use(this);
    this->ring2 = nullptr;
}

Item* Character::getRing1() const {
    return this->ring1;
}

Item* Character::getRing2() const {
    return this->ring2;
}

// Amulet
bool Character::equipAmulet(Item* amulet) {
    Amulet* a = static_cast<Amulet*>(amulet);
    if (!this->amulet) {
        this->amulet = amulet;
        auto it = std::find(inventory.begin(), inventory.end(), amulet);
        if (it != inventory.end()) {
            inventory.erase(it);
        }
        if (this->group == GroupType::Player) {
            Logger::instance().info(LocalizationManager::instance().getText("equip") + amulet->getName() + ".");
        }
        // Use item to get stats
        a->use(this);
        return true;
    } else {
        if (this->group == GroupType::Player) {
            Logger::instance().warning(LocalizationManager::instance().getText("unequip_amulet"));
        } 
        return false;
    }
}

void Character::unequipAmulet() {
    Amulet* a = static_cast<Amulet*>(this->amulet);
    a->use(this);
    this->amulet = nullptr;
}

Item* Character::getAmulet() const {
    return this->amulet;
}

// Consumable
bool Character::useConsumable(Item* item) {
    Consumable* c = static_cast<Consumable*>(item);
    c->use(this);
    // Remove item from inventory
    removeItemFromInventory(item, false);
    return false;
}

void Character::setStat(EffectStat stat, bool resultType, int value) {
    switch (stat) {
        case EffectStat::Hp:
            resultType ? this->setHp(this->getHp() + value) : this->setHp(this->getHp() - value); break;
        case EffectStat::Mana:
            resultType ? this->setMana(this->getMana() + value) : this->setMana(this->getMana() - value); break;
        case EffectStat::Energy:
            resultType ? this->setEnergy(this->getEnergy() + value) : this->setEnergy(this->getEnergy() - value); break;
        case EffectStat::Stamina:
            resultType ? this->setStamina(this->getStamina() + value) : this->setStamina(this->getStamina() - value); break;
        case EffectStat::Fov:
            resultType ? this->setFov(baseFov+value) : this->setFov(baseFov); break;  
        case EffectStat::Speed:
            resultType ? this->setSpeedBonus(value) : this->setSpeedBonus(-value); break;
        case EffectStat::Fatigue:
            resultType ? this->setFatigue(this->getFatigue() + value) : this->setFatigue(this->getFatigue() - value); break;
        case EffectStat::PhyDamage:
            resultType ? this->setPhyDamage(this->getPhyDamage() + value) : this->setPhyDamage(this->getPhyDamage() - value); break;
        case EffectStat::MagDamage:
            resultType ? this->setMagDamage(this->getMagDamage() + value) : this->setMagDamage(this->getMagDamage() - value); break;
        case EffectStat::Strength:
            resultType ? this->setStrength(this->getStrength() + value) : this->setStrength(this->getStrength() - value); break;
        case EffectStat::Dexterity:
            resultType ? this->setDexterity(this->getDexterity() + value) : this->setDexterity(this->getDexterity() - value); break;
        case EffectStat::Intelligence:
            resultType ? this->setIntelligence(this->getIntelligence() + value) : this->setIntelligence(this->getIntelligence() - value); break;
        case EffectStat::Wisdom:
            resultType ? this->setWisdom(this->getWisdom() + value) : this->setWisdom(this->getWisdom() - value); break;
        case EffectStat::Constitution:
            resultType ? this->setConstitution(this->getConstitution() + value) : this->setConstitution(this->getConstitution() - value); break;
        case EffectStat::Luck:
            resultType ? this->setLuck(this->getLuck() + value) : this->setLuck(this->getLuck() - value); break;
        case EffectStat::PhyDefense:
            resultType ? this->setPhysicalDefenseBonus(value) : this->setPhysicalDefenseBonus(-value); break;
        case EffectStat::MagDefense:
            resultType ? this->setMagicalDefenseBonus(value) : this->setMagicalDefenseBonus(-value); 
        case EffectStat::Weight:
            resultType ? this->setWeight(this->getWeight() + value) : this->setWeight(this->getWeight() - value); break;
        case EffectStat::FireResistance:
            resultType ? this->setFireResistance(this->getFireResistance() + value) : this->setFireResistance(this->getFireResistance() - value); break;
        case EffectStat::WaterResistance:
            resultType ? this->setWaterResistance(this->getWaterResistance() + value) : this->setWaterResistance(this->getWaterResistance() - value); break;
        case EffectStat::EarthResistance:
            resultType ? this->setEarthResistance(this->getEarthResistance() + value) : this->setEarthResistance(this->getEarthResistance() - value); break;
        case EffectStat::AirResistance:
            resultType ? this->setAirResistance(this->getAirResistance() + value) : this->setAirResistance(this->getAirResistance() - value); break;
        case EffectStat::LightningResistance:
            resultType ? this->setLightningResistance(this->getLightningResistance() + value) : this->setLightningResistance(this->getLightningResistance() - value); break;
        case EffectStat::IceResistance:
            resultType ? this->setIceResistance(this->getIceResistance() + value) : this->setIceResistance(this->getIceResistance() - value); break;
        case EffectStat::NatureResistance:
            resultType ? this->setNatureResistance(this->getNatureResistance() + value) : this->setNatureResistance(this->getNatureResistance() - value); break;
        case EffectStat::LightResistance:
            resultType ? this->setLightResistance(this->getLightResistance() + value) : this->setLightResistance(this->getLightResistance() - value); break;
        case EffectStat::DarknessResistance:
            resultType ? this->setDarknessResistance(this->getDarknessResistance() + value) : this->setDarknessResistance(this->getDarknessResistance() - value); break;
        case EffectStat::ArcaneResistance:
            resultType ? this->setArcaneResistance(this->getArcaneResistance() + value) : this->setArcaneResistance(this->getArcaneResistance() - value); break;
        case EffectStat::PoisonResistance:
            resultType ? this->setPoisonResistance(this->getPoisonResistance() + value) : this->setPoisonResistance(this->getPoisonResistance() - value); break;
        case EffectStat::MetalResistance:
            resultType ? this->setMetalResistance(this->getMetalResistance() + value) : this->setMetalResistance(this->getMetalResistance() - value); break;
        case EffectStat::SoundResistance:
            resultType ? this->setSoundResistance(this->getSoundResistance() + value) : this->setSoundResistance(this->getSoundResistance() - value); break;
        case EffectStat::IllusionResistance:
            resultType ? this->setIllusionResistance(this->getIllusionResistance() + value) : this->setIllusionResistance(this->getIllusionResistance() - value); break;
        default: break;
    }
}

//=====================
// Getters and Setters
//=====================

const std::string& Character::getName() const { return name; }
void Character::setName(const std::string& name) { this->name = name; }

SDL_Color Character::getColor() const { return color; }
void Character::setColor(const SDL_Color color) { this->color = color; }

GroupType Character::getGroupType() const { return group; }
void Character::setGroupType(GroupType group) { this->group = group; }

const std::string& Character::getImagePath() const { return imagePath; }

const std::string& Character::getDescription() const { return description; }

char Character::getSymbol() const { return symbol; }
void Character::setSymbol(const char symbol) { this->symbol = symbol; }

float Character::getHp() const { return hp; }
void Character::setHp(float newHp) {
    hp = newHp; 
    if (hp > maxHp)
        hp = maxHp;
}

int Character::getMana() const { return mana; }
void Character::setMana(int newMana) { 
    mana = newMana; 
    if (mana > maxMana)
        mana = maxMana;
}

int Character::getEnergy() const { return energy; }
void Character::setEnergy(int newEnergy) { 
    energy = newEnergy; 
    if (energy > maxEnergy)
        energy = maxEnergy;
}

int Character::getStamina() const { return stamina; }
void Character::setStamina(int newStamina) { 
    stamina = newStamina;
    if (stamina > maxStamina)
        stamina = maxStamina;
}

float Character::getMaxHp() const { return maxHp; }
void Character::setMaxHp(float maxHp) { hp = maxHp; }

int Character::getMaxMana() const { return maxMana; }
void Character::setMaxMana(int maxMana) { mana = maxMana; }

int Character::getMaxEnergy() const { return maxEnergy; }
void Character::setMaxEnergy(int maxEnergy) { energy = maxEnergy; }

int Character::getMaxStamina() const { return maxStamina; }
void Character::setMaxStamina(int maxStamina) { stamina = maxStamina; }

int Character::getLevel() const { return level; }
void Character::setLevel(int newLevel) { level = newLevel; }
int Character::getLevelRequirement() const { return characterProgress->getLevelRequirement(); }

int Character::getExperience() const { return experience; }
void Character::setExperience(int newExperience) { experience = newExperience; }

int Character::getSpeed() const { return speed; }
// void Character::setSpeed(int newSpeed) { speed = newSpeed; }

bool Character::isCharacterAuraUser() const { return isAuraUser; }
void Character::setCharacterAuraUser(bool auraUser) { isAuraUser = auraUser; }

int Character::getFov() const { return fov; }
void Character::setFov(int newFov) { fov = newFov; }

int Character::getPhyDamage() const { return phyDamage; }
void Character::setPhyDamage(int newDamage) { phyDamage = newDamage; }

int Character::getMagDamage() const { return magDamage; }
void Character::setMagDamage(int newDamage) { magDamage = newDamage; }

int Character::getRange() const { return range; }
void Character::setRange(int newRange) { range = newRange; }

int Character::getBaseRange() const { return baseRange; }
void Character::setBaseRange(int newBaseRange) { baseRange = newBaseRange; }
void Character::resetRange() { range = baseRange; }

int Character::getStrength() const { return strength; }
void Character::setStrength(int newStrength) { strength = newStrength; }

int Character::getDexterity() const { return dexterity; }
void Character::setDexterity(int newDexterity) { dexterity = newDexterity; }

int Character::getIntelligence() const { return intelligence; }
void Character::setIntelligence(int newIntelligence) { intelligence = newIntelligence; }

int Character::getWisdom() const { return wisdom; }
void Character::setWisdom(int newWisdom) { wisdom = newWisdom; }

int Character::getConstitution() const { return constitution; }
void Character::setConstitution(int newConstitution) {constitution = newConstitution; }

int Character::getLuck() const { return luck; }
void Character::setLuck(int newLuck) { luck = newLuck; }

int Character::getPhysicalDefense() const { return physicalDefense; }
// void Character::setPhysicalDefense(int newPhyDefense) { physicalDefense = newPhyDefense; }

int Character::getMagicalDefense() const { return magicalDefense; }
// void Character::setMagicalDefense(int newMagDefense) { magicalDefense = newMagDefense; }

float Character::getWeight() const { return weight; }
void Character::setWeight(float newWeight) { weight = newWeight; }

int Character::getMaxWeight() const { return maxWeight; }

float Character::getDodge() const { return dodge; }

//=======
// Bonus
//=======
// We use bonus because in updateStatsDepandants we calcul those
// stats with other stat and we need those bonus to add a basic
// value to those calcul

void Character::setMagicalDefenseBonus(int bonus) {
    magicalDefenseBonus += bonus;
}

void Character::setPhysicalDefenseBonus(int bonus) {
    physicalDefenseBonus += bonus;
}

void Character::setSpeedBonus(int bonus) {
    speedBonus += bonus;
}

void Character::setDodgeBonus(float bonus) {
    dodgeBonus += bonus;
}

//=======
// Bools
//=======

bool Character::isOverweight() const { return overweight; }
bool Character::hasCharacterMoved() const { return hasMoved; }
void Character::resetCharacterMoved() { hasMoved = false; }
bool Character::hasCharacterDodge() const { return hasDodge; }
void Character::resetCharacterDodge() { hasDodge = false; }
bool Character::hasCharacterCastSpell() const { return hasCastSpell; }
void Character::resetCharacterCastSpell() { hasCastSpell = false; }
bool Character::hasCharacterFoundAncientSite() const { return hasFoundAncientSite; }
void Character::resetCharacterFoundAncientSite() { hasFoundAncientSite = false; }
bool Character::hasCharacterHealDamage() const { return hasHealDamage; }
void Character::resetCharacterHealDamage() { hasHealDamage = false; }

//=========
// Fatigue
//=========

int Character::getFatigue() const { return fatigue; }
void Character::setFatigue(int newFatigue) { fatigue = newFatigue; }

//=============
// Resistances
//=============

float Character::getFireResistance() const { return fireResistance; }
void Character::setFireResistance(float newFireResistance) { fireResistance = newFireResistance; }

float Character::getWaterResistance() const { return waterResistance; }
void Character::setWaterResistance(float newWaterResistance) { waterResistance = newWaterResistance; }

float Character::getEarthResistance() const { return earthResistance; }
void Character::setEarthResistance(float newEarthResistance) { earthResistance = newEarthResistance; }

float Character::getAirResistance() const { return airResistance; }
void Character::setAirResistance(float newAirResistance) { airResistance = newAirResistance; }

float Character::getLightningResistance() const { return lightningResistance; }
void Character::setLightningResistance(float newLightningResistance) { lightningResistance = newLightningResistance; }

float Character::getIceResistance() const { return iceResistance; }
void Character::setIceResistance(float newIceResistance) { iceResistance = newIceResistance; }

float Character::getNatureResistance() const { return natureResistance; }
void Character::setNatureResistance(float newNatureResistance) { natureResistance = newNatureResistance; }

float Character::getLightResistance() const { return lightResistance; }
void Character::setLightResistance(float newLightResistance) { lightResistance = newLightResistance; }

float Character::getDarknessResistance() const { return darknessResistance; }
void Character::setDarknessResistance(float newDarknessResistance) { darknessResistance = newDarknessResistance; }

float Character::getArcaneResistance() const { return arcaneResistance; }
void Character::setArcaneResistance(float newArcaneResistance) { arcaneResistance = newArcaneResistance; }

float Character::getPoisonResistance() const { return poisonResistance; }
void Character::setPoisonResistance(float newPoisonResistance) { poisonResistance = newPoisonResistance; }

float Character::getMetalResistance() const { return metalResistance; }
void Character::setMetalResistance(float newMetalResistance) { metalResistance = newMetalResistance; }

float Character::getSoundResistance() const { return soundResistance; }
void Character::setSoundResistance(float newSoundResistance) { soundResistance = newSoundResistance; }

float Character::getIllusionResistance() const { return illusionResistance; }
void Character::setIllusionResistance(float newIllusionResistance) { illusionResistance = newIllusionResistance; }

//=========
// AI
//=========

int Character::getOwnCombatStrength() const { return ownCombatStrength; }

int Character::getOwnPerceivedCombatStrength() const { return ownPerceivedCombatStrength; }
void Character::addToOwnPerceivedCombatStrength(int strengthToAdd) { ownPerceivedCombatStrength+=strengthToAdd; }

//=========
// Desires
//=========

void Character::setDesire(std::vector<int> desires) { this->desires = desires; }
std::vector<int> Character::getDesire() const { return desires; }

void Character::setDisgust(std::vector<int> disgusts) { this->disgusts = disgusts; }
std::vector<int> Character::getDisgust() const { return disgusts; }

//==========
// Spells
//==========

void Character::setCurrentActiveSpell(Spell* spell) {
    std::array<int, 5> requirements = spell->getRequirements();

    // Check for requirements
    if (!(requirements.at(0) == -1)) {
        if (this->strength < requirements.at(0)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_strength"));
            }
            return;
        }

        if (this->dexterity < requirements.at(1)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_dexterity"));
            }
            return;
        }
        
        if (this->intelligence < requirements.at(2)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_intelligence"));
            }
            return;
        }
        
        if (this->wisdom < requirements.at(3)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_wisdom"));
            }
            return;
        } 
        
        if (this->constitution < requirements.at(4)) {
            if (this->group == GroupType::Player) {
                Logger::instance().info(LocalizationManager::instance().getText("not_enough_constitution"));
            }
            return;
        }
    }

    // Check for the spell type
    SpellEnergy spellEnergy = spell->getSpellEnergyType();
    if (spellEnergy == SpellEnergy::Mana && this->isAuraUser) {
        Logger::instance().info(LocalizationManager::instance().getText("aura_user_spell"));
        return;
    } else if (spellEnergy == SpellEnergy::Energy && !this->isAuraUser) {
        Logger::instance().info(LocalizationManager::instance().getText("mana_user_spell"));
        return;
    }

    if (currentActiveSpell) {
        // If there is a current active spell, deactivate it
        currentActiveSpell->toggleActive();
        if (currentActiveSpell == spell) {
            // If the current active spell is the same as the new spell, return
            currentActiveSpell = nullptr;
            return;
        }
    }
    // Set the new active spell
    currentActiveSpell = spell;
    // Activate the new spell
    currentActiveSpell->toggleActive();
}

Spell* Character::getCurrentActiveSpell() const {
    return currentActiveSpell;
}

//==========
// Effects
//==========

void Character::addEffect(Effect* effect) {
    // Check if the effect already exists
    for (Effect* e : effects) {
        if (e->getEffectName() == effect->getEffectName()) {
            // Effect already exists, update its duration
            e->setDuration(effect->getBaseDuration());
            return;
        }
    }
    effects.push_back(effect);
}

void Character::removeEffect(Effect* effect) {
    auto it = std::find(effects.begin(), effects.end(), effect);
    if (it != effects.end()) {
        effects.erase(it);
    }
}

std::vector<Effect*> Character::getEffects() const {
    return effects;
}