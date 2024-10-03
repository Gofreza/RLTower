#include "MapManager.h"

MapManager::MapManager()
: bsp2(), c(0, 0, 0, 0), root(nullptr), rooms(), paths(), ascii_map()
{
}

void MapManager::generateMap(int width, int height, int iterations, float wRatio, float hRatio, bool discardByRatio)
{   
    bsp2.setWidthRatio(wRatio);
    bsp2.setHeightRatio(hRatio);
    bsp2.setDiscardByRatio(discardByRatio);

    c = Container(0, 0, width, height);
    root = bsp2.splitContainer(c, iterations);
    bsp2.createRooms(root, rooms);
    bsp2.createPaths(root, paths);
    ascii_map = std::vector<std::vector<char>>(width, std::vector<char>(height, '#'));
    bsp2.generateMap(rooms, paths, ascii_map);
}

const std::vector<std::vector<char>>& MapManager::getAsciiMap() const {
    return ascii_map;
}

MapManager::~MapManager()
{
    delete root;
    root = nullptr;
}