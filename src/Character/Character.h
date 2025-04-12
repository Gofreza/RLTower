#pragma once

#include "CharacterProgress.h"
#include "../Effect/EffectStat.h"
#include "../Object/Item.h"
#include "../Spell/Spell.h"
#include "../Object/Equipment/Weapon.h"
#include "../Object/Equipment/Shield.h"
#include "../Object/Equipment/Helmet.h"
#include "../Object/Equipment/Gloves.h"
#include "../Object/Equipment/Chests.h"
#include "../Object/Equipment/Leggings.h"
#include "../Object/Equipment/Ring.h"
#include "../Object/Equipment/Amulet.h"
#include "../Object/Misc/Consumable.h"
#include "../Object/Misc/Containers.h"
#include "../Enum/GroupType.h"

class Cell;

class Character
{
protected:
    std::string name;
    SDL_Color color;
    GroupType group;
    std::string imagePath;
    std::string description;

    int xPosition;
    int yPosition;

    int gold, silver, copper;
    char symbol;

    Item* leftHand;
    Item* rightHand;
    Item* head;
    Item* torso;
    Item* hands;
    Item* boots;
    Item* ring1;
    Item* ring2;
    Item* amulet;

    std::vector<Item*> inventory;
    std::vector<Spell*> spells;

    // Character attributes
    float hp;
    int mana;
    int energy;
    int stamina;
    float maxHp;
    int maxMana;
    int maxEnergy;
    int maxStamina;

    int level;
    int experience;

    bool isAuraUser;

    // Field of vision
    int fov; // Define the radius of the circle of vision around the character

    // Speed
    int baseSpeed;
    int speed;

    // Progress
    CharacterProgress* characterProgress;
    bool hasWaited;
    bool overweight;
    bool hasDodge; // Tell if the character has dodge this turn, use for progress
    bool hasCastSpell; // Tell if the character has cast a spell this turn, use for progress
    bool hasFoundAncientSite; // Tell if the character has found an ancient site this turn, use for progress
    bool hasHealDamage;

    int fatigue;
    bool exhausted;
    bool hasMoved;
    bool hasAttack;

    // Stats
    int phyDamage;
    int magDamage;
    int baseRange;
    int range;
    int strength;
    int dexterity;
    int intelligence;
    int wisdom;
    int constitution;
    int luck;

    // Stats dependants
    int physicalDefense;
    int magicalDefense;
    float weight;
    int maxWeight;
    float dodge;

    // Bonus
    int magicalDefenseBonus;
    int physicalDefenseBonus;
    int speedBonus;
    float dodgeBonus;
    int fovBonus;

    // Resistance
    float fireResistance;
    float waterResistance;
    float earthResistance;
    float airResistance;
    float lightningResistance;
    float iceResistance;
    float natureResistance;
    float lightResistance;
    float darknessResistance;
    float arcaneResistance;
    float poisonResistance;
    float metalResistance;
    float soundResistance;
    float illusionResistance;

    // Desire
    std::vector<int> desires;
    std::vector<int> disgusts;

    // Spells
    Spell* currentActiveSpell;

    // Effects
    std::vector<Effect*> effects;

public:
    Character(const std::string& name, SDL_Color color, GroupType group, const std::string& imagePath, const std::string& description, float hp, int mana, int energy, int stamina, bool isAuraUser, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            std::vector<int> desires, std::vector<int> disgusts);
    Character(const Character& other);
    virtual ~Character();

    // Next turn
    void updateStatsDependants();
    void updateProgress();
    virtual bool update();

    void addItemInInventory(Item* item);
    void addBackItemInInventory(Item* item);
    std::vector<Item*>& getInventory();
    void removeItemFromInventory(Item* item, bool drop);
    
    void addSpellInSpellBook(Spell* spell);
    std::vector<Spell*> getSpells() const;

    void equipItem(Item* item);
    void unequipItem(Item* item);
    std::vector<Item*> getEquipEquipments();
    bool isEquipedItem(Item* item);

    virtual void move(int x, int y);

    void attack(Cell& cell, std::vector<Cell*>& cellsAffectedByEffects);
    virtual void defend(Cell& cell, Character* attacker, std::vector<Cell*>& cellsAffectedByEffects);
    virtual void support(Cell& cell, std::vector<Cell*>& cellsAffectedByEffects);
    bool canDodge();

    //=====================
    // Getters and Setters
    //=====================

    // Name
    const std::string& getName() const;
    void setName(const std::string& newName);

    // Color
    SDL_Color getColor() const;
    void setColor(SDL_Color newColor);

    // Group
    GroupType getGroupType() const;
    void setGroupType(GroupType newGroup);

    // Image
    const std::string& getImagePath() const;

    // Description
    const std::string& getDescription() const;

    // Position
    int getXPosition() const;
    void setXPosition(int newXPosition);
    int getYPosition() const;
    void setYPosition(int newYPosition);

    // Symbol
    char getSymbol() const;
    void setSymbol(const char newSymbol);

    // Money
    int getGold() const;
    void setGold(int gold);
    int getSilver() const;
    void setSilver(int silver);
    int getCopper() const;
    void setCopper(int copper);

    Item* getLeftHand() const;
    Item* getRightHand() const;
    Item* getWeapon() const;
    Item* getShield() const;

    Item* getHead() const;

    Item* getTorso() const;

    Item* getHands() const;

    Item* getBoots() const;

    Item* getRing1() const;
    Item* getRing2() const;

    Item* getAmulet() const;

    void setStat(EffectStat stat, bool resultType, int value);

    float getHp() const;
    void setHp(float newHp);
    int getMana() const;
    void setMana(int newMana);
    int getEnergy() const;
    void setEnergy(int newEnergy);
    int getStamina() const;
    void setStamina(int newStamina);

    int getLevel() const;
    void setLevel(int newLevel);
    int getLevelRequirement() const;
    int getExperience() const;
    void setExperience(int newExperience);
    int getSpeed() const;
    // void setSpeed(int newSpeed); // Use bonus

    bool isCharacterAuraUser() const;
    void setCharacterAuraUser(bool isAuraUser);

    int getFov() const;
    void setFov(int newFov);

    bool isOverweight() const;
    bool hasCharacterMoved() const;
    void resetCharacterMoved();
    bool hasCharacterDodge() const;
    void resetCharacterDodge();
    bool hasCharacterCastSpell() const;
    void resetCharacterCastSpell();
    bool hasCharacterFoundAncientSite() const;
    void resetCharacterFoundAncientSite();
    bool hasCharacterHealDamage() const;
    void resetCharacterHealDamage();

    void setMaxHp(float maxHp);
    float getMaxHp() const;
    void setMaxMana(int maxMana);
    int getMaxMana() const;
    void setMaxEnergy(int maxEnergy);
    int getMaxEnergy() const;
    void setMaxStamina(int maxStamina);
    int getMaxStamina() const;

    int getPhyDamage() const;
    void setPhyDamage(int newDamage);
    int getMagDamage() const;
    void setMagDamage(int newDamage);
    int getRange() const;
    void setRange(int newRange);
    int getBaseRange() const;
    void setBaseRange(int newBaseRange);
    void resetRange();
    int getStrength() const;
    void setStrength(int newStrength);
    int getDexterity() const;
    void setDexterity(int newDexterity);
    int getIntelligence() const;
    void setIntelligence(int newIntelligence);
    int getWisdom() const;
    void setWisdom(int newWisdom);
    int getConstitution() const;
    void setConstitution(int newConstitution);
    int getLuck() const;
    void setLuck(int newLuck);

    int getPhysicalDefense() const;
    // void setPhysicalDefense(int newPhyDefense); // Use Bonus
    int getMagicalDefense() const;
    // void setMagicalDefense(int newMagDefense); // Use Bonus
    float getWeight() const;
    void setWeight(float newWeight);
    int getMaxWeight() const;
    float getDodge() const;

    void setMagicalDefenseBonus(int bonus);
    void setPhysicalDefenseBonus(int bonus);
    void setSpeedBonus(int bonus);
    void setDodgeBonus(float bonus);
    void setFovBonus(int bonus);

    // Fatigue
    int getFatigue() const;
    void setFatigue(int newFatigue);

    // Resistances
    float getFireResistance() const;
    void setFireResistance(float newFireResistance);
    float getWaterResistance() const;
    void setWaterResistance(float newWaterResistance);
    float getEarthResistance() const;
    void setEarthResistance(float newEarthResistance);
    float getAirResistance() const;
    void setAirResistance(float newAirResistance);
    float getLightningResistance() const;
    void setLightningResistance(float newLightningResistance);
    float getIceResistance() const;
    void setIceResistance(float newIceResistance);
    float getNatureResistance() const;
    void setNatureResistance(float newNatureResistance);
    float getLightResistance() const;
    void setLightResistance(float newLightResistance);
    float getDarknessResistance() const;
    void setDarknessResistance(float newDarknessResistance);
    float getArcaneResistance() const;
    void setArcaneResistance(float newArcaneResistance);
    float getPoisonResistance() const;
    void setPoisonResistance(float newPoisonResistance);
    float getMetalResistance() const;
    void setMetalResistance(float newMetalResistance);
    float getSoundResistance() const;
    void setSoundResistance(float newSoundResistance);
    float getIllusionResistance() const;
    void setIllusionResistance(float newIllusionResistance);

    void setDesire(std::vector<int> newDesire);
    std::vector<int> getDesire() const;
    void setDisgust(std::vector<int> newDisgust);
    std::vector<int> getDisgust() const;

    void setCurrentActiveSpell(Spell* spell);
    Spell* getCurrentActiveSpell() const;

    // Effects
    void addEffect(Effect* effect);
    void removeEffect(Effect* effect);
    std::vector<Effect*> getEffects() const;
private:
    bool equipWeapons(Item* weapon);
    void unequipLeftWeapon();
    void unequipRightWeapon();
    bool equipShield(Item* shield);
    bool equipHead(Item* helmet);
    void unequipHead();
    bool equipTorso(Item* armor);
    void unequipTorso();
    bool equipHands(Item* glove);
    void unequipHands();
    bool equipBoots(Item* armor);
    void unequipBoots();
    bool equipRing(Item* ring);
    void unequipRing1();
    void unequipRing2();
    bool equipAmulet(Item* amulet);
    void unequipAmulet();

    bool useConsumable(Item* item);
};
