#pragma once
#include <string>

enum class WeaponType {
    Sword,
    Spear,
    Mace,
    Bow,
    Staff,
    None
};

inline std::string to_string(WeaponType rarityType) {
    switch (rarityType) {
        case WeaponType::Sword:     return "Sword";
        case WeaponType::Spear:     return "Spear";
        case WeaponType::Mace:      return "Mace";
        case WeaponType::Bow:       return "Bow";
        case WeaponType::Staff:     return "Staff";
        default:                    return "Unknown";
    }
}