#pragma once

#include <map>
#include "../../Character/Enemy.h"

/**
 * @brief Manager for the enemies
 * It loads the enemies from a file and allow to get a
 * copy of an enemy based on its id when needed in
 * the game.
 */
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
