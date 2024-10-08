#pragma once

#include <string>
#include <functional>

#include "EffectStat.h"
#include "EffectType.h"

class Character;

class Effect
{
public:
    Effect(short id,
           const std::string& effectName, 
           const std::string& description,
           const std::string& logText, 
           EffectType effectType,
           int duration,
           std::vector<EffectStat> effectStats,
           bool resultType,
           int value);
    ~Effect();

    void trigger(Character* character, bool isReversed = false);

    short getEffectId() const;
    const std::string& getEffectName() const;
    const std::string& getLogText() const;
    const std::string& getDescription() const;
    int getDuration() const;

private:
    short id;
    const std::string effectName;
    const std::string description;
    const std::string logText;
    EffectType effectType;
    int duration;
    std::vector<EffectStat> effectStats;
    // Positive = true, negative = false
    bool resultType;
    int value;

};
