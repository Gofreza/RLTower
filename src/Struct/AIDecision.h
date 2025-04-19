#pragma once

#include "../Enum/Direction.h"
#include <iostream>

struct AIDecision
{
    int aggression = 0;
    int fear = 0;
    int desire = 0;
    int wander = 0;
    int misc = 0;
    bool blocked = false;
};

inline std::ostream& operator<<(std::ostream& os, const AIDecision& decision)
{
    os << "Aggression: " << decision.aggression << std::endl;
    os << "Fear: " << decision.fear << std::endl;
    os << "Desire: " << decision.desire << std::endl;
    os << "Wander: " << decision.wander << std::endl;
    os << "Misc: " << decision.misc << std::endl;
    return os;
}

