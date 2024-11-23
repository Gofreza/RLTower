#pragma once

#include <string>

enum class EffectType {
    Dot,
    Burst,
    Permanent,
    None
};

inline std::string to_string(EffectType effectType) {
    switch (effectType) {
        case EffectType::Dot:       return "Dot";
        case EffectType::Burst:     return "Burst";
        case EffectType::Permanent: return "Permanent";
        default:                    return "None";
    }
}

inline EffectType getEffectType(const std::string& type) {
    if (type == "Dot") { return EffectType::Dot; }
    else if (type == "Burst") { return EffectType::Burst; }
    else if (type == "Permanent") { return EffectType::Permanent; }
    else { return EffectType::None; }
}