#pragma once
#include <string>
#include <SDL2/SDL.h>

enum class SpellElement {
    Fire,
    Water,
    Earth,
    Air,
    Lightning,
    Ice,
    Nature,
    Light,
    Darkness,
    Arcane,
    Poison,
    Metal,
    Sound,
    Illusion,
    Time,
    Gravity,
    None
};

inline std::string to_string(SpellElement spellElement) {
    switch (spellElement) {
        case SpellElement::Fire:        return "Fire";
        case SpellElement::Water:       return "Water";
        case SpellElement::Earth:       return "Earth";
        case SpellElement::Air:         return "Air";
        case SpellElement::Lightning:   return "Lightning";
        case SpellElement::Ice:         return "Ice";
        case SpellElement::Nature:      return "Nature";
        case SpellElement::Light:       return "Light";
        case SpellElement::Darkness:    return "Darkness";
        case SpellElement::Arcane:      return "Arcane";
        case SpellElement::Poison:      return "Poison";
        case SpellElement::Metal:       return "Metal";
        case SpellElement::Sound:       return "Sound";
        case SpellElement::Illusion:    return "Illusion";
        case SpellElement::Time:        return "Time";
        case SpellElement::Gravity:     return "Gravity";
        default:                        return "None";
    }
}

inline SpellElement getSpellElement(const std::string& type) {
    if (type == "Fire") {
        return SpellElement::Fire;
    } else if (type == "Water") {
        return SpellElement::Water;
    } else if (type == "Earth") {
        return SpellElement::Earth;
    } else if (type == "Air") {
        return SpellElement::Air;
    } else if (type == "Lightning") {
        return SpellElement::Lightning;
    } else if (type == "Ice") {
        return SpellElement::Ice;
    } else if (type == "Nature") {
        return SpellElement::Nature;
    } else if (type == "Light") {
        return SpellElement::Light;
    } else if (type == "Darkness") {
        return SpellElement::Darkness;
    } else if (type == "Arcane") {
        return SpellElement::Arcane;
    } else if (type == "Poison") {
        return SpellElement::Poison;
    } else if (type == "Metal") {
        return SpellElement::Metal;
    } else if (type == "Sound") {
        return SpellElement::Sound;
    } else if (type == "Illusion") {
        return SpellElement::Illusion;
    } else if (type == "Time") {
        return SpellElement::Time;
    } else if (type == "Gravity") {
        return SpellElement::Gravity;
    } else {
        return SpellElement::None;
    }
}

inline SDL_Color getElementColor(SpellElement element) {
    switch (element) {
        case SpellElement::Fire:        return {255, 0, 0, 255};
        case SpellElement::Water:       return {0, 102, 255, 255};
        case SpellElement::Earth:       return {23, 139, 10, 255};
        case SpellElement::Air:         return {212, 237, 188, 255};
        case SpellElement::Lightning:   return {255, 229, 160, 255};
        case SpellElement::Ice:         return {47, 219, 255, 255};
        case SpellElement::Nature:      return {170, 126, 55, 255};
        case SpellElement::Light:       return {255, 243, 217, 255};
        case SpellElement::Darkness:    return {61, 61, 61, 255};
        case SpellElement::Arcane:      return {232, 234, 237, 255};
        case SpellElement::Poison:      return {96, 114, 50, 255};
        case SpellElement::Metal:       return {168, 182, 202, 255};
        case SpellElement::Sound:       return {198, 219, 225, 255};
        case SpellElement::Illusion:    return {230, 207, 242, 255};
        case SpellElement::Time:        return {33, 90, 108, 255};
        case SpellElement::Gravity:     return {90, 50, 134, 255};
        default:                        return {215, 215, 215, 255};
    }
} 

inline SDL_Color getElementColor(const std::string& element) {
    if (element == "Fire")              return {255, 0, 0, 255};
    else if (element == "Water")        return {0, 102, 255, 255};
    else if (element == "Earth")        return {23, 139, 10, 255};
    else if (element == "Air")          return {212, 237, 188, 255};
    else if (element == "Lightning")    return {255, 229, 160, 255};
    else if (element == "Ice")          return {47, 219, 255, 255};
    else if (element == "Nature")       return {170, 126, 55, 255};
    else if (element == "Light")        return {255, 243, 217, 255};
    else if (element == "Darkness")     return {61, 61, 61, 255};
    else if (element == "Arcane")       return {232, 234, 237, 255};
    else if (element == "Poison")       return {96, 114, 50, 255};
    else if (element == "Metal")        return {168, 182, 202, 255};
    else if (element == "Sound")        return {198, 219, 225, 255};
    else if (element == "Illusion")     return {230, 207, 242, 255};
    else if (element == "Time")         return {33, 90, 108, 255};
    else if (element == "Gravity")      return {90, 50, 134, 255};
    else                                return {215, 215, 215, 255}; 
}
