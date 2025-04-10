#include "EffectManager.h"

EffectManager::EffectManager()
: isInitialize(false)
{
}

void EffectManager::loadEffectsFromFile(const std::string& effectsFilePath) {
    std::ifstream file(effectsFilePath);
    if (!file.is_open()) {
        isInitialize = false;
        std::cout << "Error loading effects" << std::endl;
    } else {
        nlohmann::json jsonData;
        try {
            file >> jsonData;
            //std::cout << jsonData.dump(4) << std::endl;  // Pretty prints the JSON with 4 spaces of indentation
        } catch (nlohmann::json::parse_error& e) {
            std::cout << "Error parsing JSON: " << e.what() << std::endl;
            isInitialize = false;
            return;
        }

        if (!jsonData.contains("effects") || !jsonData["effects"].is_array()) {
            std::cout << "Invalid JSON format: 'effects' key missing or not an array." << std::endl;
            isInitialize = false;
            return;
        }


        for (const auto& effectJson : jsonData["effects"]) {
            Effect* effect = new Effect(effectJson.value("id", -1),
                                        effectJson.value("name", "Unknown"),
                                        effectJson.value("description", "Unknown"),
                                        effectJson.value("log", "Unknown"),
                                        effectJson.value("imagePath", "default.png"),
                                        getEffectType(effectJson.value("type", "None")),
                                        getSpellElement(effectJson.value("element", "None")),
                                        effectJson.value("duration", 0),
                                        getEffectStatVector(effectJson.value("stats", std::list<std::string>{})),
                                        effectJson.value("resultType", false),
                                        effectJson.value("value", std::vector<int>{}));

            effects.emplace(effect->getEffectId(), effect);
        }

        isInitialize = true;
        std::cout << "Effects loaded" << std::endl;
    }
}

Effect* EffectManager::getEffect(short id) const {
    if (!isInitialize) {
        throw std::runtime_error("EffectManager is not initialized. (getEffect)");
    }

    auto it = effects.find(id);
    if (it != effects.end()) {
        return it->second;
    }

    throw std::runtime_error("Effect with ID " + std::to_string(id) + " not found.");

}

std::vector<Effect*> EffectManager::getEffect(std::list<std::string> effectsList) const {
    if (!isInitialize) {
        throw std::runtime_error("EffectManager is not initialized. (getEffect)");
    }   

    std::vector<Effect*> effectsVector;

    for (const auto& name : effectsList) {
        for (auto& effect : effects) {
            if (effect.second->getEffectName() == name) {
                effectsVector.push_back(effect.second);
            }
        }
    }

    return effectsVector;
}

EffectManager::~EffectManager()
{
    for (auto& pair : effects) {
        if (pair.second)
            delete pair.second;
    }
}
