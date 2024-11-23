#include "Effect.h"
#include "../Character/Character.h"

Effect::Effect(short id,
            const std::string& effectName, 
            const std::string& description,
            const std::string& logText, 
            EffectType effectType,
            int duration,
            std::vector<EffectStat> effectStats,
            bool resultType,
            int value)
: id(id), effectName(effectName), description(description),
  logText(logText), effectType(effectType), duration(duration),
  effectStats(effectStats), resultType(resultType), value(value)
{
}

void Effect::trigger(Character* character, bool isReversed) {
    if (duration > 0) {
        for (auto& stat : effectStats) {
            character->setStat(stat,  isReversed ? !this->resultType : this->resultType, this->value);
        }
    }
}

//=========
// GETTERS
//=========

short Effect::getEffectId() const { return id; }

const std::string& Effect::getEffectName() const { return effectName; }

const std::string& Effect::getDescription() const { return description; }

const std::string& Effect::getLogText() const { return logText; }

int Effect::getDuration() const { return duration; }



Effect::~Effect()
{
}
