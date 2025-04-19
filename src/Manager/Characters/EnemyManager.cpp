#include "EnemyManager.h"
#include "../Item/ItemManager.h"

EnemyManager::EnemyManager() 
: isInitialized(false), enemyCount(0)
{
}

EnemyManager::~EnemyManager() {
    for (auto& [id, enemy] : enemies) {
        delete enemy;
    }
    enemies.clear();
    enemyCount = 0;
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
            int id = enemyJson.value("id", enemyCount);

            // Color
            std::array<int, 4> color = enemyJson.value("color", std::array<int, 4>{255, 255, 255, 255});
            SDL_Color sdlColor = {static_cast<Uint8>(color[0]), static_cast<Uint8>(color[1]), static_cast<Uint8>(color[2]), static_cast<Uint8>(color[3])};

            // Symbol
            std::string symbol = enemyJson.value("symbol", "b");
            char c = symbol[0];

            // Desire
            std::vector<int> desires;
            for (const auto& element : enemyJson["desires"]) {
                desires.push_back(element.get<int>());
            }
            std::vector<int> disgusts;
            for (const auto& element : enemyJson["disgusts"]) {
                disgusts.push_back(element.get<int>());
            }

            // Create the enemy
            Enemy* enemy = new Enemy(
                enemyJson.value("name", "Unknown"),
                sdlColor,
                getGroupType(enemyJson.value("group", "Unknown")),
                enemyJson.value("imagePath", "default.png"),
                enemyJson.value("description", "No description"),
                enemyJson.value("health", 0.0f),
                enemyJson.value("mana", 0),
                enemyJson.value("energy", 0),
                enemyJson.value("stamina", 0),
                enemyJson.value("auraUser", false),
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
                desires,
                disgusts,
                enemyJson.value("minSpawnLevel", 0),
                enemyJson.value("maxSpawnLevel", 0),
                enemyJson.value("value", 0),
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
            if (enemy) {
                enemies.emplace(id, enemy);
                enemyCount++;
            }
        }
    }
    isInitialized = true;
}

// TODO: Implement this function
void EnemyManager::initialize(std::vector<Enemy*>& enemiesVector, int towerLevel, int numberOfEnemies) {
    // Add ennemies based on the tower level
    while(numberOfEnemies > 0) {
        // Get a random enemy
        int randomEnemy = rand() % enemyCount;
        Enemy* enemy = getEnemy(randomEnemy);
        enemiesVector.push_back(enemy);
        numberOfEnemies -= enemy->getValue();
    }
    // Enemy* enemy = getEnemy(1);
    // enemiesVector.push_back(enemy);
    // numberOfEnemies -= enemy->getValue();
    // Enemy* enemy1 = getEnemy(0);
    // enemiesVector.push_back(enemy1);
    // numberOfEnemies -= enemy1->getValue();
    // Enemy* enemy2 = getEnemy(2);
    // enemiesVector.push_back(enemy2);
    // numberOfEnemies -= enemy2->getValue();
    // Enemy* enemy3 = getEnemy(3);
    // enemiesVector.push_back(enemy3);
    // numberOfEnemies -= enemy3->getValue();

}

void EnemyManager::addEnemy(Enemy* enemy) {
    enemies[enemyCount] = enemy;
    enemyCount++;
}

std::map<int, Enemy*>& EnemyManager::getEnemies() {
    return enemies;
}

Enemy* EnemyManager::getEnemy(int id) {
    if (!isInitialized) {
        throw std::runtime_error("EnemyManager is not initialized. (getEnemy)");
    }

    auto it = enemies.find(id);
    if (it != enemies.end()) {
        return it->second->clone();
    }

    throw std::runtime_error("Item with ID " + std::to_string(id) + " not found.");
}