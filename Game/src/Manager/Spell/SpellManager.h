#pragma once

#include <iostream>
#include <functional>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>

#include "../Characters/CharactersManager.h"
#include "../../Spell/Spell.h"
#include "../../Spell/SpellElement.h"
#include "../../Spell/SpellType.h"

class SpellManager
{
public:
    static SpellManager& instance() {
        static SpellManager instance;
        return instance;
    }

    void loadSpellsFromFile(const std::string& spellsFilePath);

    Spell* getSpell(short id) const;
    std::function<void(Character*)> getEffect(const std::string& key) const;
    std::string getEffectText(const std::string& key) const;

private:
    bool isInitialize;

    std::unordered_map<short, Spell*> spells;
    std::unordered_map<std::string, std::function<void(Character*)>> effectsRegistry;
    std::unordered_map<std::string, std::string> effectsTextRegistry;

    SpellManager();
    ~SpellManager();

    void createEffectsRegistry();
    void createEffectsTextRegistry();

    SpellManager(const SpellManager&) = delete;
    SpellManager& operator=(const SpellManager&) = delete;
};