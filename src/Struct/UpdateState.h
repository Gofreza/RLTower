#pragma once

#include "../Enum/ActionType.h"

class Cell;

class UpdateState
{
public:
    bool hasPlayed;
    ActionType actionType;
    Cell* target;
    bool isAI;
};