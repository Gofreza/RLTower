#pragma once
#include <string>

enum class DamageType {
    Blunt,
    Sharp,
    None
};

inline std::string to_string(DamageType damageType) {
    switch (damageType) {
        case DamageType::Blunt: return "Blunt";
        case DamageType::Sharp: return "Sharp";
        default:                return "None";
    }
}

inline DamageType getDamageType(const std::string& type) {
    if (type == "Blunt") {
        return DamageType::Blunt;
    } else if (type == "Sharp") {
        return DamageType::Sharp;
    } else {
        return DamageType::None;
    } 
}