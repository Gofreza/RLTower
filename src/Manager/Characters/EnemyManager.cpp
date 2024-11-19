#include "EnemyManager.h"

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
    clearEnemies();
}

void EnemyManager::loadEnemies() {
    // Load enemies from file
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