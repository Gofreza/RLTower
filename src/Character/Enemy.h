#pragma once

#include "Character.h"
#include "../Struct/AIDecision.h"

class Enemy : public Character 
{
public:
    Enemy(const std::string& name, SDL_Color color, GroupType group, const std::string& imagePath, const std::string& description,
            float hp, int mana, int energy, int stamina, bool isAuraUser, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            std::vector<int> desire, std::vector<int> disgust,
            int minSpawnLevel, int maxSpawnLevel, int value,
            float basicAggression, float basicFear, float bascDesire, float basicWander, float basicMisc);
    Enemy(const Enemy& enemy);
    ~Enemy();

    bool update() override;
    int getValue() const;

    virtual Enemy* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
private:
    int minSpawnLevel;
    int maxSpawnLevel;
    int value;

    float basicAggression;
    float basicFear;
    float bascDesire;
    float basicWander;
    float basicMisc;
    
    AIDecision check();
};