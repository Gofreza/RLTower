#pragma once

#include "../Misc/Logger.h"
#include "../Manager/Localization/LocalizationManager.h"

class Character;

class CharacterProgress 
{
public:
    CharacterProgress(Character* character);
    ~CharacterProgress();

    void progress();

    int getLevelRequirement() const;
    void levelUp();
    
    void trainStrength();
    void trainDexterity();
    void trainIntelligence();
    void trainWisdom();
    void trainConstitution();
private:
    Character* character;

    int levelRequirement;
    std::array<int, 30> experiencesArray;

    short strengthLevel;
    short strengthLevelRequirement;
    short dexterityLevel;
    short dexterityLevelRequirement;
    short intelligenceLevel;
    short intelligenceLevelRequirement;
    short wisdomLevel;
    short wisdomLevelRequirement;
    short constitutionLevel;
    short constitutionLevelRequirement;

    void initializeExperiencesArray();

    void progressStrength();
    void progressDexterity();
    void progressIntelligence();
    void progressWisdom();
    void progressConstitution();
};
