#include "CharacterProgress.h"
#include "Character.h"

CharacterProgress::CharacterProgress(Character* character)
: character(character),
levelRequirement(1),
strengthLevel(0), strengthLevelRequirement(100),
dexterityLevel(0), dexterityLevelRequirement(100),
intelligenceLevel(0), intelligenceLevelRequirement(100),
wisdomLevel(0), wisdomLevelRequirement(1),
constitutionLevel(0), constitutionLevelRequirement(100)
{
    initializeExperiencesArray();
}

void CharacterProgress::progress() {
    progressStrength();
    progressDexterity();
    progressIntelligence();
    progressWisdom();
    progressConstitution();
}

//==========
// Progress
//==========

int CharacterProgress::getLevelRequirement() const {
    return levelRequirement;
}

void CharacterProgress::levelUp() {

    if (character->getExperience() > levelRequirement) {
        character->setLevel(character->getLevel() + 1);
        character->setExperience(0);
        levelRequirement = experiencesArray.at(character->getLevel() - 1);  
    } 
}

void CharacterProgress::initializeExperiencesArray() {
    experiencesArray = {
        100, 150, 200, 250, 300, 350, 400, 450, 500, 550,
        600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050,
        1100, 1150, 1200, 1250, 1300, 1350, 1400, 1450, 1500, 1550
    };
}

//==========
// Progress
//==========

void CharacterProgress::progressStrength() {
    if (character->getFatigue() <= 100) {
        if (character->isOverweight()) {
            strengthLevel++;
            character->setFatigue(character->getFatigue() + 1);

            if (strengthLevel == strengthLevelRequirement) {
                character->setStrength(character->getStrength() + 1);
                strengthLevelRequirement += strengthLevelRequirement / 2;
                strengthLevel = 0;
            }   
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::progressDexterity() {
    if (character->getFatigue() <= 100) {
        if (character->hasCharacterDodge()) {
            dexterityLevel++;
            character->setFatigue(character->getFatigue() + 1);

            if (dexterityLevel == dexterityLevelRequirement) {
                character->setDexterity(character->getDexterity() + 1);
                dexterityLevelRequirement += dexterityLevelRequirement / 2;
                dexterityLevel = 0;
            }
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::progressIntelligence() {
    if (character->getFatigue() <= 100) {
        if (character->hasCharacterCastSpell()) {
            intelligenceLevel++;
            character->setFatigue(character->getFatigue() + 1);

            if (intelligenceLevel == intelligenceLevelRequirement) {
                character->setIntelligence(character->getIntelligence() + 1);
                intelligenceLevelRequirement += intelligenceLevelRequirement / 2;
                intelligenceLevel = 0;
            }
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::progressWisdom() {
    if (character->getFatigue() <= 100) {
        if (character->hasCharacterFoundAncientSite()) {
            wisdomLevel++;
            character->setFatigue(character->getFatigue() + 1);

            if (wisdomLevel == wisdomLevelRequirement) {
                character->setWisdom(character->getWisdom() + 1);
                if (wisdomLevelRequirement < 8)
                    wisdomLevelRequirement *= 2;
                else
                    wisdomLevelRequirement += 2;
                wisdomLevel = 0;
            }
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::progressConstitution() {
    if (character->getFatigue() <= 100) {
        if (character->hasCharacterHealDamage()) {
            constitutionLevel++;
            character->setFatigue(character->getFatigue() + 1);

            if (constitutionLevel == constitutionLevelRequirement) {
                character->setConstitution(character->getConstitution() + 1);
                constitutionLevelRequirement += constitutionLevelRequirement / 2;
                constitutionLevel = 0;
            }
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

//==========
// Training
//==========

void CharacterProgress::trainStrength() {
    if (character->getFatigue() <= 100) {
        strengthLevel++;
        character->setFatigue(character->getFatigue() + 1);

        if (strengthLevel == strengthLevelRequirement) {
            character->setStrength(character->getStrength() + 1);
            strengthLevelRequirement += strengthLevelRequirement / 2;
            strengthLevel = 0;
        }   
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::trainDexterity() {
    if (character->getFatigue() <= 100) {
        dexterityLevel++;
        character->setFatigue(character->getFatigue() + 1);

        if (dexterityLevel == dexterityLevelRequirement) {
            character->setDexterity(character->getDexterity() + 1);
            dexterityLevelRequirement += dexterityLevelRequirement / 2;
            dexterityLevel = 0;
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::trainIntelligence() {
    if (character->getFatigue() <= 100) {
        intelligenceLevel++;
        character->setFatigue(character->getFatigue() + 1);

        if (intelligenceLevel == intelligenceLevelRequirement) {
            character->setIntelligence(character->getIntelligence() + 1);
            intelligenceLevelRequirement += intelligenceLevelRequirement / 2;
            intelligenceLevel = 0;
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::trainWisdom() {
    if (character->getFatigue() <= 100) {
        wisdomLevel++;
        character->setFatigue(character->getFatigue() + 1);

        if (wisdomLevel == wisdomLevelRequirement) {
            character->setWisdom(character->getWisdom() + 1);
            if (wisdomLevelRequirement < 8)
                wisdomLevelRequirement *= 2;
            else
                wisdomLevelRequirement += 2;
            wisdomLevel = 0;
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

void CharacterProgress::trainConstitution() {
    if (character->getFatigue() <= 100) {
        constitutionLevel++;
        character->setFatigue(character->getFatigue() + 1);

        if (constitutionLevel == constitutionLevelRequirement) {
            character->setConstitution(character->getConstitution() + 1);
            constitutionLevelRequirement += constitutionLevelRequirement / 2;
            constitutionLevel = 0;
        }
    } else {
        Logger::instance().warning(LocalizationManager::instance().getText("exhausted_message"));
    }
}

CharacterProgress::~CharacterProgress()
{
}