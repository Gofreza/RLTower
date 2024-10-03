#include "Character.h"
#include <cmath>

static float SPEED_SCALAR = 10.0f;

static float PHY_DEFENSE_SCALAR = 0.20f;
static float MAG_DEFENSE_SCALAR = 0.20f;
static float MAX_WEIGHT_SCALAR = 10.0f;

static float DODGE_SCALAR = 1.0f;
static float DODGE_DEXTERITY_SCALAR = 0.7f;
static float DODGE_LUCK_SCALAR = 0.3f;

Character::Character(float hp, int mana, int energy, int stamina, int speed,
                    int phyDamage, int magDamage, int strength, int dexterity,
                    int intelligence, int wisdom, int constitution, int luck)
    : xPosition(0), yPosition(0),
    hp(hp), mana(mana), energy(energy), stamina(stamina), 
    maxHp(hp), maxMana(mana), maxEnergy(energy), maxStamina(stamina), gold(0), silver(0), copper(0),
    // Level
    level(0), experience(0),
    // Speed
    baseSpeed(speed), speed(0), 
    // Progress
    characterProgress(new CharacterProgress(this)), overweight(false), hasDodge(false), hasCastSpell(false), hasFoundAncientSite(false), hasHealDamage(false),
    fatigue(0), exhausted(false), hasMoved(false), hasAttack(false),
    // Stats
    phyDamage(phyDamage), magDamage(magDamage), strength(strength),
    dexterity(dexterity), intelligence(intelligence), wisdom(wisdom), constitution(constitution), luck(luck),
    // Stats Dependants
    physicalDefense(0), magicalDefense(0), weight(0.f), maxWeight(0), dodge(0.0f),
    // Bonus
    magicalDefenseBonus(0), physicalDefenseBonus(0), speedBonus(0), dodgeBonus(0.f),
    // Resistances
    fireResistance(0.0f), waterResistance(0.0f), earthResistance(0.0f), airResistance(0.0f),
    lightningResistance(0.0f), iceResistance(0.0f), natureResistance(0.0f),
    lightResistance(0.0f), darknessResistance(0.0f), arcaneResistance(0.0f),
    poisonResistance(0.0f), metalResistance(0.0f), soundResistance(0.0f),
    illusionResistance(0.0f)
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
}

void Character::updateStatsDependants() {
    // Speed
    if (overweight) {
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
}

void Character::update() {
    // Fatigue
    if (fatigue > 100) {
        exhausted = true;
        speed = 0;
    }
    
    // Level
    characterProgress->levelUp();

    // Progress
    if (hasMoved) {
        characterProgress->progress();
    } else {
        if (!hasAttack) {
            fatigue--;
            if (fatigue <= 100) {
                exhausted = false;
            }
        }
    }
    updateStatsDependants();
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
    Item* newItem = item->clone();

    // If new items is a containers, check for possible objects to put in
    if (newItem->getType() == ItemType::Container) {
        Containers* c = static_cast<Containers*>(newItem);
        c->use(this);
    }

    inventory.push_back(newItem);

    if (this->weight > this->maxWeight) {        
        Logger::instance().info(LocalizationManager::instance().getText("too_heavy_message"));
        overweight = true;
        updateStatsDependants();
    }

    // If there is a container, use it in case the new object can be added in
    for (auto& item : this->inventory) {
        if (item->getType() == ItemType::Container) {
            Containers* c = static_cast<Containers*>(item);
            c->use(this);
        }
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

void Character::removeItemFromInventory(Item* item) {
    // Drop item from the inventory

    // Placeholder
    if (isEquipedItem(item)) {
        unequipItem(item);
    }
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
    delete (item);
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
// EQUIPMENTS
//===============

void Character::equipItem(Item* item) {
    std::array<int, 5> requirements = item->getRequirements();

    // Check for requirements
    if (!(requirements.at(0) == -1)) {
        if (requirements.at(0) >= this->strength) {
            Logger::instance().info(LocalizationManager::instance().getText("not_enough_strength"));
            return;
        }

        if (requirements.at(1) >= this->dexterity) {
            Logger::instance().info(LocalizationManager::instance().getText("not_enough_dexterity"));
            return;
        }
        
        if (requirements.at(2) >= this->intelligence) {
            Logger::instance().info(LocalizationManager::instance().getText("not_enough_intelligence"));
            return;
        }
        
        if (requirements.at(3) >= this->wisdom) {
            Logger::instance().info(LocalizationManager::instance().getText("not_enough_wisdom"));
            return;
        } 
        
        if (requirements.at(4) >= this->constitution) {
            Logger::instance().info(LocalizationManager::instance().getText("not_enough_constitution"));
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
    // std::cout << "Item: " << item << std::endl;
    // std::cout << "LH: " << this->leftHand << std::endl;
    // std::cout << "RH: " << this->rightHand << std::endl;
    // std::cout << "Head: " << this->head << std::endl;
    // std::cout << "Torso: " << this->torso << std::endl;
    // std::cout << "Hands: " << this->hands << std::endl;
    // std::cout << "Foots: " << this->boots << std::endl;
    // std::cout << "Ring1: " << this->ring1 << std::endl;
    // std::cout << "Ring2: " << this->ring2 << std::endl;
    // std::cout << "Amulet: " << this->amulet << std::endl;

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

    Logger::instance().info(LocalizationManager::instance().getText("unequip") + item->getName() + ".");
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
            Logger::instance().info(LocalizationManager::instance().getText("equip") + weapon->getName() + ".");
            // Use the item to get the stats
            w->use(this);
            return true;
        } else {
            Logger::instance().warning(LocalizationManager::instance().getText("empty_hands"));
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
            Logger::instance().info(LocalizationManager::instance().getText("equip") + weapon->getName() + ".");
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
            Logger::instance().info(LocalizationManager::instance().getText("equip") + weapon->getName() + ".");
            // Use the item to get the stats
            w->use(this);
            return true;
        } else {
            // Weapons already equip
            // Can't equip need to de-equip before
            if (leftHand && rightHand)
                Logger::instance().warning(LocalizationManager::instance().getText("empty_hands"));
            else
                Logger::instance().warning(LocalizationManager::instance().getText("unequip_weapon"));
            
            return false;
        }
    }
}

void Character::unequipLeftWeapon() {
    Equipment* e = static_cast<Equipment*>(leftHand);
    e->use(this);
    if (leftHand == rightHand)
    {
        this->leftHand = nullptr;
        this->rightHand = nullptr;
    } else 
        this->leftHand = nullptr;
}

void Character::unequipRightWeapon() {
    Equipment* e = static_cast<Equipment*>(leftHand);
    e->use(this);
    if (rightHand == leftHand)
    {
        this->leftHand = nullptr;
        this->rightHand = nullptr;
    } else 
        this->rightHand = nullptr;
}

Item* Character::getLeftHand() const {
    return this->leftHand;
}

Item* Character::getRightHand() const {
    return this->rightHand;
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + shield->getName() + ".");
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + shield->getName() + ".");
        // Use items to get stats
        s->use(this);
        return true;
    } else {
        // Weapons already equip
        // Can't equip need to de-equip before
        if (leftHand && rightHand)
            Logger::instance().warning(LocalizationManager::instance().getText("empty_hands"));
        else
            Logger::instance().warning(LocalizationManager::instance().getText("unequip_weapon"));
        return false;
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + helmet->getName() + ".");
        // Use item to get stats
        h->use(this);
        return true;
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("unequip_helmet"));
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + armor->getName() + ".");
        // Use item to get stats
        c->use(this);
        return true;
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("unequip_chest"));
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + glove->getName() + ".");
        // Use item to get stats
        g->use(this);
        return true;
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("unequip_hands"));
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + armor->getName() + ".");
        // Use item to get stats
        l->use(this);
        return true;
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("unequip_boots"));
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + ring->getName() + ".");
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + ring->getName() + ".");
        // Use item to get stats
        r->use(this);
        return true;
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("unequip_ring"));
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
        Logger::instance().info(LocalizationManager::instance().getText("equip") + amulet->getName() + ".");
        // Use item to get stats
        a->use(this);
        return true;
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("unequip_amulet"));
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
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
    return true;
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

//=========
// Getters
//=========

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

int Character::getPhyDamage() const { return phyDamage; }
void Character::setPhyDamage(int newDamage) { phyDamage = newDamage; }

int Character::getMagDamage() const { return magDamage; }
void Character::setMagDamage(int newDamage) { magDamage = newDamage; }

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
bool Character::hasCharacterDodge() const { return hasDodge; }
bool Character::hasCharacterCastSpell() const { return hasCastSpell; }
bool Character::hasCharacterFoundAncientSite() const { return hasFoundAncientSite; }
bool Character::hasCharacterHealDamage() const { return hasHealDamage; }

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