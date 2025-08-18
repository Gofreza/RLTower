#pragma once

#include <string>

enum class ActionType
{
    ATTACK,
    MOVE,
    WAIT,
    NONE
};

inline std::string actionTypeToString(const ActionType& actionType)
{
    switch (actionType) {
        case ActionType::ATTACK:
            return "ATTACK";
        case ActionType::MOVE:
            return "MOVE";
        case ActionType::WAIT:
            return "WAIT";
        case ActionType::NONE:
            return "NONE";
    }
    return "UNKNOWN";
}