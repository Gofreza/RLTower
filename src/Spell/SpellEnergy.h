#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "../Misc/Utils.h"

enum class SpellEnergy {
    Mana,
    Energy,
    None
};

inline std::string to_string(SpellEnergy spellEnergy) {
    switch (spellEnergy) {
        case SpellEnergy::Mana:     return "Mana";
        case SpellEnergy::Energy:   return "Energy";
        default:                    return "Unknown";
    }
}

inline SpellEnergy getSpellEnergyType(const std::string& type) {
    if (type == "Mana") {
        return SpellEnergy::Mana;
    } else if (type == "Energy") {
        return SpellEnergy::Energy;
    } else {
        return SpellEnergy::None;
    }
}

inline SDL_Color getSpellEnergyTypeColor(SpellEnergy energyType) {
    switch (energyType) {
        case SpellEnergy::Mana:     return Utils::manaFillColor;
        case SpellEnergy::Energy:   return Utils::energyFillColor;
        default:                    return {215, 215, 215, 255};
    }
}