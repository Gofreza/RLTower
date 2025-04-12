#include "Effect.h"
#include "../Character/Character.h"

Effect::Effect(short id,
            const std::string& effectName, 
            const std::string& description,
            const std::string& logText, 
            const std::string& imagePath,
            EffectType effectType,
            SpellElement element,
            int duration,
            std::vector<EffectStat> effectStats,
            bool resultType,
            std::vector<int> value)
: id(id), effectName(effectName), description(description),
  logText(logText), imagePath(imagePath), effectType(effectType), element(element), baseDuration(duration), duration(duration),
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

const std::string& Effect::getImagePath() const { return imagePath; }

EffectType Effect::getEffectType() const { return effectType; }

SpellElement Effect::getElement() const { return element; }

int Effect::getBaseDuration() const { return baseDuration; }

int Effect::getDuration() const { return duration; }

void Effect::setDuration(int newDuration) { duration = newDuration; }

void Effect::reduceDuration() { duration--; }


Effect::~Effect()
{
}
