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

class Character
{
protected:
    int gold, silver, copper;

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

    // Speed
    int baseSpeed;
    int speed;

    // Progress
    CharacterProgress* characterProgress;
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

    // Insert status effect here
    // Struct with a name and the modified stats

public:
    Character(float hp, int mana, int energy, int stamina, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck);
    ~Character();

    void updateStatsDependants();
    void update();

    int getGold() const;
    void setGold(int gold);
    int getSilver() const;
    void setSilver(int silver);
    int getCopper() const;
    void setCopper(int copper);

    void addItemInInventory(Item* item);
    void addBackItemInInventory(Item* item);
    std::vector<Item*>& getInventory();
    void removeItemFromInventory(Item* item);
    
    void addSpellInSpellBook(Spell* spell);
    std::vector<Spell*> getSpells() const;

    void equipItem(Item* item);
    void unequipItem(Item* item);
    std::vector<Item*> getEquipEquipments();
    bool isEquipedItem(Item* item);

    Item* getLeftHand() const;
    Item* getRightHand() const;

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

    bool isOverweight() const;
    bool hasCharacterDodge() const;
    bool hasCharacterCastSpell() const;
    bool hasCharacterFoundAncientSite() const;
    bool hasCharacterHealDamage() const;

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

    int getFatigue() const;
    void setFatigue(int newFatigue);

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
