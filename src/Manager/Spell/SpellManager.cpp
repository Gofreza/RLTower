#include "SpellManager.h"

SpellManager::SpellManager()
: isInitialize(false)
{
    createEffectsRegistry();
    createEffectsTextRegistry();
}

void SpellManager::loadSpellsFromFile(const std::string& spellsFilePath) {
    std::ifstream file(spellsFilePath);
    if(!file.is_open()) {
        isInitialize = false;
        std::cout << "Error loading spells" << std::endl;
    } else {
        nlohmann::json jsonData;
        try {
            file >> jsonData;
        } catch(nlohmann::json::parse_error& e) {
            std::cout << "Error parsing JSON: " << e.what() << std::endl;
            isInitialize = false;
            return;
        }

        if (!jsonData.contains("spells") || !jsonData["spells"].is_array()) {
            std::cout << "Invalid JSON format: 'spells' key missing or not an array." << std::endl;
            isInitialize = false;
            return;
        }

        for (const auto& spellJson : jsonData["spells"]) {
            Spell* spell = new Spell(spellJson.value("id", -1),
                                    spellJson.value("name", "Unknown"),
                                    spellJson.value("description", "Unknown"),
                                    getSpellEnergyType(spellJson.value("energyType", "None")),
                                    getSpellType(spellJson.value("type", "None")),
                                    getSpellElement(spellJson.value("element", "None")),
                                    spellJson.value("damage", 0),
                                    spellJson.value("range", 0),
                                    spellJson.value("consumption", -1),
                                    spellJson.value("effect", "Error"),
                                    getEffect(spellJson.value("effect", "Error")),
                                    spellJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1, -1}));

            spells.emplace(spell->getId(), spell);
        }

        isInitialize = true;
        std::cout << "Spells loaded" << std::endl;
    }
}  

Spell* SpellManager::getSpell(short id) const {
    if (!isInitialize) {
        throw std::runtime_error("SpellManager is not initialized. (getSpell)");
    }

    auto it = spells.find(id);
    if (it != spells.end()) {
        return it->second;
    }

    throw std::runtime_error("Spell with ID " + std::to_string(id) + " not found.");

}

std::function<void(Character*)> SpellManager::getEffect(const std::string& key) const {
    auto it = effectsRegistry.find(key);
    if (it != effectsRegistry.end()) {
        return it->second;
    }

    throw std::runtime_error("Effect with ID " + key + " not found. (SpellManager)");
}

std::string SpellManager::getEffectText(const std::string& key) const {
    auto it = effectsTextRegistry.find(key);
    if (it != effectsTextRegistry.end()) {
        return it->second;
    }
    
    throw std::runtime_error("EffectText with ID " + key + " not found. (SpellManager)");
}

void SpellManager::createEffectsRegistry() {
    effectsRegistry = {
        {"burn_effect", [](Character* character) { 
            // Log and apply burn to passed character          
        }},
    };
}

void SpellManager::createEffectsTextRegistry() {
    effectsTextRegistry = {
        {"burn_effect", LocalizationManager::instance().getText("burn_effect")}
    };
}

SpellManager::~SpellManager()
{
    for (auto& pair : spells) {
        if (pair.second)
            delete pair.second;
    }
}
