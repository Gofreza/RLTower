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
        case EffectStat::MagDefense:        return "MagDefense";
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