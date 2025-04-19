#pragma once

#include "../Map/Cell.h"
#include "AIDecision.h"

struct AICells
{
    std::vector<Cell*> all;
    std::vector<Cell*> north;
    int northDistance = 0;
    int nortValue = 0;
    Character* closestNorthCharacter = nullptr;
    std::vector<Cell*> east;
    int eastDistance = 0;
    int eastValue = 0;
    Character* closestEastCharacter = nullptr;
    std::vector<Cell*> south;
    int southDistance = 0;
    int southValue = 0;
    Character* closestSouthCharacter = nullptr;
    std::vector<Cell*> west;
    int westDistance = 0;
    int westValue = 0;
    Character* closestWestCharacter = nullptr;
    AIDecision decision;
};

inline std::ostream& operator<<(std::ostream& os, const AICells& aiCells) {
    os << "AICells:" << std::endl;
    os << "All: " << aiCells.all.size() << std::endl;
    os << "North: " << aiCells.north.size() << std::endl;
    os << "North Distance: " << aiCells.northDistance << std::endl;
    os << "North Value: " << aiCells.nortValue << std::endl;
    os << "East: " << aiCells.east.size() << std::endl;
    os << "East Distance: " << aiCells.eastDistance << std::endl;
    os << "East Value: " << aiCells.eastValue << std::endl;
    os << "South: " << aiCells.south.size() << std::endl;
    os << "South Distance: " << aiCells.southDistance << std::endl;
    os << "South Value: " << aiCells.southValue << std::endl;
    os << "West: " << aiCells.west.size() << std::endl;
    os << "West Distance: " << aiCells.westDistance << std::endl;
    os << "West Value: " << aiCells.westValue << std::endl;
    os << "Decision: " << std::endl;
    os << aiCells.decision;

    return os;
}

