#pragma once

#include "Character.h"
#include "../Struct/AIDecision.h"
#include "../Enum/ActionType.h"
#include "../Struct/AICells.h"
#include "../Pathfinding/Pathfinding.h"

struct AICells;

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

    UpdateState update() override;
    int getValue() const;
    
    void addLastVisitedCell(Cell* cell);
    bool isLastVisitedCell(Cell* cell) const;
    std::vector<Cell*>& getLastVisitedCells();

    int getBasicAggression() const;
    int getBasicFear() const;
    int getBasicDesire() const;
    int getBasicWander() const;
    int getBasicMisc() const;

    int getWanderValue() const;
    void setWanderValue(int value);

    AICells getAICells() const;
    ActionType getActionType() const;

    virtual Enemy* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
private:
    int minSpawnLevel;
    int maxSpawnLevel;
    int value;

    AICells aiCells;
    ActionType actionType;
    std::vector<Cell*> lastVisitedCells;

    float basicAggression;
    float basicFear;
    float bascDesire;
    float basicWander;
    float basicMisc;

    float wanderValue;
};