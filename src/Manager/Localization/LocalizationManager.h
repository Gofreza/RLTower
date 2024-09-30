#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>

class LocalizationManager
{
public:
    static LocalizationManager& instance() {
        static LocalizationManager instance;
        return instance;
    }

    void loadLocalizationFromFile(const std::string& LocalizationFilePath) {
        std::ifstream file(LocalizationFilePath);
        if (!file.is_open()) {
            isInitialize = false;
            std::cout << "Error loading localization" << std::endl;
        } else {
            nlohmann::json jsonData;
            file >> jsonData;

            for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
                localizedStrings[it.key()] = it.value();
            }

            isInitialize = true;
            std::cout << "Localization loaded" << std::endl;
        }
    }

    std::string getText(const std::string& key) const {
        if (isInitialize) {
            auto it = localizedStrings.find(key);
            if (it != localizedStrings.end()) {
                return it->second;
            }
            return "{" + key + "}"; 
        } else {
            throw std::runtime_error("LocalizationManager is not initialized.");
        }
    }

private:
    bool isInitialize;

    std::unordered_map<std::string, std::string> localizedStrings;

    LocalizationManager() : isInitialize(false)
    {}
    ~LocalizationManager() {}

    LocalizationManager(const LocalizationManager&) = delete;
    LocalizationManager& operator=(const LocalizationManager&) = delete;
};
