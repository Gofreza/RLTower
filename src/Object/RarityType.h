#pragma once
#include <SDL2/SDL_image.h>

enum class RarityType {
    Poor,
    Normal,
    Good,
    Rare,
    Epic,
    Legendary,
    Mythical
};

inline std::string to_string(RarityType rarityType) {
    switch (rarityType) {
        case RarityType::Poor:          return "Poor";
        case RarityType::Normal:        return "Normal";
        case RarityType::Good:          return "Good";
        case RarityType::Rare:          return "Rare";
        case RarityType::Epic:          return "Epic";
        case RarityType::Legendary:     return "Legendary";
        case RarityType::Mythical:      return "Mythical";
        default:                      return "Unknown";
    }
}

inline SDL_Color getRarityColor(RarityType rarityType) {
    switch (rarityType) {
        case RarityType::Poor:          return {208, 162, 41, 255}; // Brown
        case RarityType::Normal:        return {215, 215, 215, 255}; // White
        case RarityType::Good:          return {17, 236, 17, 255}; // Green
        case RarityType::Rare:          return {17, 166, 236, 255}; // Blue
        case RarityType::Epic:          return {153, 17, 236, 255}; // Purple
        case RarityType::Legendary:     return {236, 232, 17, 255}; // Yellow
        case RarityType::Mythical:      return {236, 17, 17, 255}; // Red
        default:                      return {215, 215, 215, 255};
    }
}