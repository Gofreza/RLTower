#include "Effect.h"
#include "../Character/Character.h"

Effect::Effect(short id,
            const std::string& effectName, 
            const std::string& description,
            const std::string& logText, 
            EffectType effectType,
            SpellElement element,
            int duration,
            std::vector<EffectStat> effectStats,
            bool resultType,
            std::vector<int> value)
: id(id), effectName(effectName), description(description),
  logText(logText), effectType(effectType), element(element), duration(duration),
  effectStats(effectStats), resultType(resultType), value(value)
{
}

Effect* Effect::clone() const {
    return new Effect(*this);
}

void Effect::trigger(Character* character, bool isReversed) {
    for (size_t i = 0; i < effectStats.size(); ++i) {
        character->setStat(effectStats[i], isReversed ? !this->resultType : this->resultType, this->value[i]);
    }
}

//=========
// GETTERS
//=========

short Effect::getEffectId() const { return id; }

const std::string& Effect::getEffectName() const { return effectName; }

const std::string& Effect::getDescription() const { return description; }

const std::string& Effect::getLogText() const { return logText; }

EffectType Effect::getEffectType() const { return effectType; }

SpellElement Effect::getElement() const { return element; }

int Effect::getDuration() const { return duration; }

void Effect::reduceDuration() { duration--; }


Effect::~Effect()
{
}
