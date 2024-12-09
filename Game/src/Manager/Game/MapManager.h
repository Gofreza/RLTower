#pragma once

#include "../../Map/BSP2.h"
#include "../Characters/CharactersManager.h"
#include "../../Character/Enemy.h"

class MapManager
{
public:
    static MapManager& instance() {
        static MapManager instance;
        return instance;
    }

    void generateMap(int width, int height, int iterations, float wRatio = 0.45f, float hRatio = 0.45f, bool discardByRatio = true);
    void removeCharacter(int dx, int dy);

    void addPlayer(Player* player);
    void movePlayerInMap(Player* player, int dx, int dy);
    bool canPlayerMove(Player* player, int dx, int dy);

    void addEnemies(std::vector<Enemy*> enemies);
    void moveCharacterInMap(Character* character, int dx, int dy);
    bool canCharacterMove(Character* character, int dx, int dy);

    bool dropItem(int x, int y, Item* item);

    const std::vector<std::vector<Cell>>& getAsciiMap() const;
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

    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;
};