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
           const std::string& imagePath,
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
    const std::string& getDescription() const;
    const std::string& getLogText() const;
    const std::string& getImagePath() const;
    EffectType getEffectType() const;
    SpellElement getElement() const;
    int getBaseDuration() const;
    int getDuration() const;
    void setDuration(int newDuration);
    void reduceDuration();

private:
    short id;
    const std::string effectName;
    const std::string description;
    const std::string logText;
    const std::string imagePath;
    EffectType effectType;
    SpellElement element;
    int baseDuration;
    int duration;
    std::vector<EffectStat> effectStats;
    // Positive = true, negative = false
    bool resultType;
    std::vector<int> value;
};
