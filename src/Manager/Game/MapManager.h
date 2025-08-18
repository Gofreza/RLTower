#pragma once

#include "../../Map/BSP2.h"
#include "../Characters/CharactersManager.h"
#include "../../Character/Enemy.h"
#include "../Config/Config.h"
#include "../../Struct/AICells.h"

class MapManager
{
public:
    static MapManager& instance() {
        static MapManager instance;
        return instance;
    }

    void initialize();

    void generateMap(int width, int height, int iterations, float wRatio = 0.45f, float hRatio = 0.45f, bool discardByRatio = true);
    void removeCharacter(int dx, int dy);

    void addPlayer(Player* player);
    void movePlayerInMap(Player* player, int dx, int dy);
    bool canPlayerMove(Player* player, int dx, int dy);

    void addEnemies(std::vector<Enemy*> enemies);
    void moveCharacterInMap(Character* character, int dx, int dy);
    bool canCharacterMove(Character* character, int dx, int dy);
    void highlightEnemy(Enemy* enemy, bool reset = false);
    void hightlightEnemyFov(Enemy* enemy, bool reset = false, int x = -1, int y = -1);

    bool dropItem(int x, int y, Item* item);

    void calculateFov(Player* player);
    AICells calculateCharacterFov(Enemy* character, int x, int y, int fov);

    void getAffectedCells(int x, int y, int radius, std::vector<std::pair<int, int>>& affectedCells);

    const std::vector<std::vector<Cell>>& getAsciiMap() const;
    Cell& getCell(int x, int y);
    void printDungeonMap();

private:   
    MapManager();
    ~MapManager();
    
    int width, height;

    BSP2 bsp2;

    Container c;
    Tree<Container>* root;
    std::vector<Room> rooms;
    std::vector<Path> paths;
    std::vector<std::vector<Cell>> ascii_map;

    std::vector<Cell*> visibleCells;
    void bresenham(int x1, int y1, int const x2, int const y2);
    void characterBresenham(Enemy* character, int x1, int y1, int const x2, int const y2, AICells& visibleCells);

    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;
};