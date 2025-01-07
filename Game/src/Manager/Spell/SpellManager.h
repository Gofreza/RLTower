#pragma once

#include <iostream>
#include <functional>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>

#include "../Characters/CharactersManager.h"
#include "../Effect/EffectManager.h"
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

private:
    bool isInitialize;

    std::unordered_map<short, Spell*> spells;

    SpellManager();
    ~SpellManager();

    SpellManager(const SpellManager&) = delete;
    SpellManager& operator=(const SpellManager&) = delete;
};