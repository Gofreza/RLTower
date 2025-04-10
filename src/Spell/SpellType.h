#pragma once
#include <string>

enum class SpellType {
    Attack,
    Defense,
    Support,
    None
};

inline std::string to_string(SpellType spellType) {
    switch (spellType) {
        case SpellType::Attack:     return "Attack";
        case SpellType::Defense:    return "Defense";
        case SpellType::Support:    return "Support";
        default:                    return "Unknown";
    }
}

inline SpellType getSpellType(const std::string& type) {
    if (type == "Attack") {
        return SpellType::Attack;
    } else if (type == "Defense") {
        return SpellType::Defense;
    } else if (type == "Support") {
        return SpellType::Support;
    } else {
        return SpellType::None;
    }
}