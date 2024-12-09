#pragma once
#include <SDL2/SDL.h>

enum class ItemType {
    Weapon,
    Shield,
    Helmet,
    Gloves,
    ChestArmor,
    LegArmor,
    Ring,
    Amulet,
    Consumable,
    Projectile,
    Container,
    QuestItem,
    Miscellaneous
};

inline char to_char(ItemType itemType) {
    switch (itemType) {
        case ItemType::Weapon:        return 'E';
        case ItemType::Shield:        return 'E';
        case ItemType::Helmet:        return 'E';
        case ItemType::Gloves:        return 'E';
        case ItemType::ChestArmor:    return 'E';
        case ItemType::LegArmor:      return 'E';
        case ItemType::Ring:          return 'A';
        case ItemType::Amulet:        return 'A';
        case ItemType::Consumable:    return 'C';
        case ItemType::Projectile:    return 'P';
        case ItemType::Container:     return 'C';
        case ItemType::QuestItem:     return 'Q';
        case ItemType::Miscellaneous: return 'M';
        default:                      return 'U';
    }
}

inline SDL_Color to_color(ItemType itemType) {
    std::array<Uint8, 4> color = {0, 0, 0, 255};
    switch (itemType) {
        case ItemType::Weapon:        color = {255, 0, 0, 255}; break;
        case ItemType::Shield:        color = {255, 0, 0, 255}; break;
        case ItemType::Helmet:        color = {255, 0, 0, 255}; break;
        case ItemType::Gloves:        color = {255, 0, 0, 255}; break;
        case ItemType::ChestArmor:    color = {255, 0, 0, 255}; break;
        case ItemType::LegArmor:      color = {255, 0, 0, 255}; break;
        case ItemType::Ring:          color = {0, 255, 0, 255}; break;
        case ItemType::Amulet:        color = {0, 255, 0, 255}; break;
        case ItemType::Consumable:    color = {53, 53, 220, 255}; break;
        case ItemType::Projectile:    color = {255, 255, 255, 255}; break;
        case ItemType::Container:     color = {220, 150, 50, 255}; break;
        case ItemType::QuestItem:     color = {255, 255, 0, 255}; break;
        case ItemType::Miscellaneous: color = {100, 100, 100, 255}; break;
        default:                      color = {0, 0, 0, 255}; break;
    }
    return {static_cast<Uint8>(color[0]), static_cast<Uint8>(color[1]), static_cast<Uint8>(color[2]), static_cast<Uint8>(color[3])};
}

inline std::string to_string(ItemType itemType) {
    switch (itemType) {
        case ItemType::Weapon:        return "Weapon";
        case ItemType::Shield:        return "Shield";
        case ItemType::Helmet:        return "Helmet";
        case ItemType::Gloves:        return "Gloves";
        case ItemType::ChestArmor:    return "Chest Armor";
        case ItemType::LegArmor:      return "Leg Armor";
        case ItemType::Ring:          return "Ring";
        case ItemType::Amulet:        return "Amulet";
        case ItemType::Consumable:    return "Consumable";
        case ItemType::Projectile:    return "Projectile";
        case ItemType::Container:     return "Container";
        case ItemType::QuestItem:     return "Quest Item";
        case ItemType::Miscellaneous: return "Miscellaneous";
        default:                      return "Unknown";
    }
}