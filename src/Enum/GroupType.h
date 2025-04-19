#pragma once

#include <string>

enum class GroupType {
    Player,
    NPC,
    Goblinoid,
    Undead,
    Unknown
};

inline std::string to_string(GroupType groupType) {
    switch (groupType) {
        case GroupType::Player:    return "Player";
        case GroupType::NPC:       return "NPC";
        case GroupType::Goblinoid: return "Goblinoid";
        case GroupType::Undead:    return "Undead";
        default:                   return "Unknown";
    }
}

inline GroupType getGroupType(const std::string& groupType) {
    if (groupType == "Player") {
        return GroupType::Player;
    } else if (groupType == "NPC") {
        return GroupType::NPC;
    } else if (groupType == "Goblinoid") {
        return GroupType::Goblinoid;
    } else if (groupType == "Undead") {
        return GroupType::Undead;
    } else {
        return GroupType::Unknown;
    }
}