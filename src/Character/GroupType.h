#pragma once

#include <string>

enum class GroupType {
    Player,
    NPC,
    Goblinoid
};

inline std::string to_string(GroupType groupType) {
    switch (groupType) {
        case GroupType::Player:    return "Player";
        case GroupType::NPC:       return "NPC";
        case GroupType::Goblinoid: return "Goblinoid";
        default:                   return "Unknown";
    }
}