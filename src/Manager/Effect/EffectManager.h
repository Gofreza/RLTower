#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../../Character/Character.h"
#include "../../Effect/Effect.h"

class EffectManager
{
public:
    static EffectManager& instance() {
        static EffectManager instance;
        return instance;
    }
    
    void loadEffectsFromFile(const std::string& effectsFilePath);
    Effect* getEffect(short id) const;
    std::vector<Effect*> getEffect(std::list<std::string>) const;

private:
    bool isInitialize;

    EffectManager();
    ~EffectManager();

    std::unordered_map<short, Effect*> effects;

    EffectManager(const EffectManager&) = delete;
    EffectManager& operator=(const EffectManager&) = delete;

};
