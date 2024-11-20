#include "EnemyManager.h"
#include "../Item/ItemManager.h"

EnemyManager::EnemyManager() 
: isInitialized(false), enemyCount(0)
{
}

EnemyManager::~EnemyManager() {
    clearEnemies();
}

void EnemyManager::loadEnemiesFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        isInitialized = false;
        std::cerr << "Error loading enemies" << std::endl;
    } else {
        nlohmann::json jsonData;
        try {
            file >> jsonData;
        } catch (nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            isInitialized = false;
            return;
        }

        if (!jsonData.contains("enemies") || !jsonData["enemies"].is_array()) {
            std::cerr << "Invalid JSON format: 'items' key missing or not an array." << std::endl;
            isInitialized = false;
            return;
        }

        for (const auto& enemyJson : jsonData["enemies"]) {
            // Enemy ID
            int id = enemyJson.value("id", -1);

            // Color
            std::array<int, 4> color = enemyJson.value("color", std::array<int, 4>{255, 255, 255, 255});
            SDL_Color sdlColor = {static_cast<Uint8>(color[0]), static_cast<Uint8>(color[1]), static_cast<Uint8>(color[2]), static_cast<Uint8>(color[3])};

            // Symbol
            std::string symbol = enemyJson.value("symbol", "b");
            char c = symbol[0];

            // Create the enemy
            Enemy* enemy = new Enemy(
                enemyJson.value("name", "Unknown"),
                sdlColor,
                getGroupType(enemyJson.value("group", "Unknown")),
                enemyJson.value("health", 0.0f),
                enemyJson.value("mana", 0),
                enemyJson.value("energy", 0),
                enemyJson.value("stamina", 0),
                enemyJson.value("fov", 0),
                enemyJson.value("speed", 0),
                enemyJson.value("phyDamage", 0),
                enemyJson.value("magDamage", 0),
                enemyJson.value("strength", 0),
                enemyJson.value("dexterity", 0),
                enemyJson.value("intelligence", 0),
                enemyJson.value("wisdom", 0),
                enemyJson.value("constitution", 0),
                enemyJson.value("luck", 0),
                c,
                enemyJson.value("aggression", 0.0f),
                enemyJson.value("fear", 0.0f),
                enemyJson.value("desire", 0.0f),
                enemyJson.value("wander", 0.0f),
                enemyJson.value("misc", 0.0f)
            );

            // Set Money
            std::array<int, 3> money = enemyJson.value("money", std::array<int, 3>{0, 0, 0});
            enemy->setGold(money[0]);
            enemy->setSilver(money[1]);
            enemy->setCopper(money[2]);

            // Update enemy resistance
            std::array<int, 14> resistances = enemyJson.value("resistances", std::array<int, 14>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            enemy->setFireResistance(resistances[0]);
            enemy->setWaterResistance(resistances[1]);
            enemy->setEarthResistance(resistances[2]);
            enemy->setAirResistance(resistances[3]);
            enemy->setLightningResistance(resistances[4]);
            enemy->setIceResistance(resistances[5]);
            enemy->setNatureResistance(resistances[6]);
            enemy->setLightResistance(resistances[7]);
            enemy->setDarknessResistance(resistances[8]);
            enemy->setArcaneResistance(resistances[9]);
            enemy->setPoisonResistance(resistances[10]);
            enemy->setMetalResistance(resistances[11]);
            enemy->setSoundResistance(resistances[12]);
            enemy->setIllusionResistance(resistances[13]);

            // Add equipment to the enemy
            std::array<int, 9> equipments = enemyJson.value("equipments", std::array<int, 9>{-1, -1, -1, -1, -1, -1, -1, -1, -1});
            for (int i = 0; i < 9; i++) {
                if (equipments[i] != -1) {
                    enemy->equipItem(ItemManager::instance().getItem(equipments[i]));
                }
            }

            // Add the enemy to the list
            addEnemy(enemy);
        }
    }

}

void EnemyManager::initialize(int towerLevel, int numberOfEnemies) {
    // Add ennemies based on the tower level
}

void EnemyManager::addEnemy(Enemy* enemy) {
    enemies[enemyCount] = enemy;
    enemyCount++;
}

void EnemyManager::removeEnemy(Enemy* enemy) {
    
}

void EnemyManager::clearEnemies() {
    for (auto& [id, enemy] : enemies) {
        delete enemy;
    }
    enemies.clear();
    enemyCount = 0;
}

void EnemyManager::update() {
    for (auto& [id, enemy] : enemies) {
        enemy->check();
    }

    for (auto& [id, enemy] : enemies) {
        enemy->update();
    }
}

std::map<int, Enemy*>& EnemyManager::getEnemies() {
    return enemies;
}