#pragma once

#include "../Enum/Direction.h"
#include <iostream>

struct AIDecision
{
    Direction dir;
    int aggression;
    int fear;
    int desire;
    int wander;
    int misc;
};

inline std::ostream& operator<<(std::ostream& os, const AIDecision& decision)
{
    os << "Direction: " << static_cast<int>(decision.dir) << std::endl;
    os << "Aggression: " << decision.aggression << std::endl;
    os << "Fear: " << decision.fear << std::endl;
    os << "Desire: " << decision.desire << std::endl;
    os << "Wander: " << decision.wander << std::endl;
    os << "Misc: " << decision.misc << std::endl;
    return os;
}

