#pragma once

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