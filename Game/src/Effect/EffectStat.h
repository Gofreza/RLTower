#pragma once
#include <list>
#include <vector>

enum class EffectStat {
    Hp,
    Mana,
    Energy,
    Stamina,
    Speed,
    Fatigue,
    PhyDamage,
    MagDamage,
    Strength,
    Dexterity,
    Intelligence,
    Wisdom,
    Constitution,
    Luck,
    PhyDefense,
    MagDefense,
    Weight,
    FireResistance,
    WaterResistance,
    EarthResistance,
    AirResistance,
    LightningResistance,
    IceResistance,
    NatureResistance,
    LightResistance,
    DarknessResistance,
    ArcaneResistance,
    PoisonResistance,
    MetalResistance,
    SoundResistance,
    IllusionResistance,
    None
};

inline std::string to_string(EffectStat effectStat) {
    switch (effectStat) {
        case EffectStat::Hp:                  return "Hp";
        case EffectStat::Mana:                return "Mana";
        case EffectStat::Energy:              return "Energy";
        case EffectStat::Stamina:             return "Stamina";
        case EffectStat::Speed:               return "Speed";
        case EffectStat::Fatigue:             return "Fatigue";
        case EffectStat::PhyDamage:           return "PhyDamage";
        case EffectStat::MagDamage:           return "MagDamage";
        case EffectStat::Strength:            return "Strength";
        case EffectStat::Dexterity:           return "Dexterity";
        case EffectStat::Intelligence:        return "Intelligence";
        case EffectStat::Wisdom:              return "Wisdom";
        case EffectStat::Constitution:        return "Constitution";
        case EffectStat::Luck:                return "Luck";
        case EffectStat::PhyDefense:          return "PhyDefense";
        case EffectStat::MagDefense:          return "MagDefense";
        case EffectStat::Weight:              return "Weight";
        case EffectStat::FireResistance:      return "FireResistance";
        case EffectStat::WaterResistance:     return "WaterResistance";
        case EffectStat::EarthResistance:     return "EarthResistance";
        case EffectStat::AirResistance:       return "AirResistance";
        case EffectStat::LightningResistance: return "LightningResistance";
        case EffectStat::IceResistance:       return "IceResistance";
        case EffectStat::NatureResistance:    return "NatureResistance";
        case EffectStat::LightResistance:     return "LightResistance";
        case EffectStat::DarknessResistance:  return "DarknessResistance";
        case EffectStat::ArcaneResistance:    return "ArcaneResistance";
        case EffectStat::PoisonResistance:    return "PoisonResistance";
        case EffectStat::MetalResistance:     return "MetalResistance";
        case EffectStat::SoundResistance:     return "SoundResistance";
        case EffectStat::IllusionResistance:  return "IllusionResistance";
        default:                            return "None";
    }

}

const std::unordered_map<std::string, EffectStat> effectStatMap = {
    {"Hp", EffectStat::Hp},
    {"Mana", EffectStat::Mana},
    {"Energy", EffectStat::Energy},
    {"Stamina", EffectStat::Stamina},
    {"Speed", EffectStat::Speed},
    {"Fatigue", EffectStat::Fatigue},
    {"PhyDamage", EffectStat::PhyDamage},
    {"MagDamage", EffectStat::MagDamage},
    {"Strength", EffectStat::Strength},
    {"Dexterity", EffectStat::Dexterity},
    {"Intelligence", EffectStat::Intelligence},
    {"Wisdom", EffectStat::Wisdom},
    {"Constitution", EffectStat::Constitution},
    {"Luck", EffectStat::Luck},
    {"PhyDefense", EffectStat::PhyDefense},
    {"MagDefense", EffectStat::MagDefense},
    {"Weight", EffectStat::Weight},
    {"FireResistance", EffectStat::FireResistance},
    {"WaterResistance", EffectStat::WaterResistance},
    {"EarthResistance", EffectStat::EarthResistance},
    {"AirResistance", EffectStat::AirResistance},
    {"LightningResistance", EffectStat::LightningResistance},
    {"IceResistance", EffectStat::IceResistance},
    {"NatureResistance", EffectStat::NatureResistance},
    {"LightResistance", EffectStat::LightResistance},
    {"DarknessResistance", EffectStat::DarknessResistance},
    {"ArcaneResistance", EffectStat::ArcaneResistance},
    {"PoisonResistance", EffectStat::PoisonResistance},
    {"MetalResistance", EffectStat::MetalResistance},
    {"SoundResistance", EffectStat::SoundResistance},
    {"IllusionResistance", EffectStat::IllusionResistance}
};

// Function to convert a list of strings to a vector of EffectStat
inline std::vector<EffectStat> getEffectStatVector(const std::list<std::string>& statsList) {
    std::vector<EffectStat> effectStats;
    for (const auto& stat : statsList) {
        auto it = effectStatMap.find(stat);
        if (it != effectStatMap.end()) {
            effectStats.push_back(it->second);  // Add the corresponding EffectStat to the vector
        } else {
            effectStats.push_back(EffectStat::None);  // Fallback in case of unknown stat
        }
    }
    return effectStats;
}