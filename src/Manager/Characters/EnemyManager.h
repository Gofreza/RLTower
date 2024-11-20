#pragma once

#include <map>
#include "../../Character/Enemy.h"

class EnemyManager
{
public:
    static EnemyManager& instance() {
        static EnemyManager instance;
        return instance;
    }

    void loadEnemiesFromFile(const std::string& filePath);

    void initialize(int towerLevel, int numberOfEnemies);
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);
    void clearEnemies();
    std::map<int, Enemy*>& getEnemies();

    void update();
private:
    bool isInitialized;
    int enemyCount;
    std::map<int, Enemy*> enemies;

    EnemyManager();
    ~EnemyManager();

    // Prevent copying
    EnemyManager(const EnemyManager&) = delete;
    EnemyManager& operator=(const EnemyManager&) = delete;
};
