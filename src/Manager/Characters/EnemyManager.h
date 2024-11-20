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

    void initialize(std::vector<Enemy*>& enemies, int towerLevel, int numberOfEnemies);
    void addEnemy(Enemy* enemy);

    std::map<int, Enemy*>& getEnemies();
    Enemy* getEnemy(int id);

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
