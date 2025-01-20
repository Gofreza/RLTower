#pragma once

#include <string>
#include <functional>

#include "EffectStat.h"
#include "EffectType.h"
#include "../Spell/SpellElement.h"

class Character;

class Effect
{
public:
    Effect(short id,
           const std::string& effectName, 
           const std::string& description,
           const std::string& logText, 
           EffectType effectType,
           SpellElement element,
           int duration,
           std::vector<EffectStat> effectStats,
           bool resultType,
           std::vector<int> value);
    ~Effect();

    Effect* clone() const;
    void trigger(Character* character, bool isReversed = false);

    short getEffectId() const;
    const std::string& getEffectName() const;
    const std::string& getLogText() const;
    const std::string& getDescription() const;
    EffectType getEffectType() const;
    SpellElement getElement() const;
    int getDuration() const;
    void reduceDuration();

private:
    short id;
    const std::string effectName;
    const std::string description;
    const std::string logText;
    EffectType effectType;
    SpellElement element;
    int duration;
    std::vector<EffectStat> effectStats;
    // Positive = true, negative = false
    bool resultType;
    std::vector<int> value;
};
