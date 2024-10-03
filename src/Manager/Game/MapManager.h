#pragma once

#include "../../Map/BSP2.h"

class MapManager
{
public:
    static MapManager& instance() {
        static MapManager instance;
        return instance;
    }

    void generateMap(int width, int height, int iterations, float wRatio = 0.45f, float hRatio = 0.45f, bool discardByRatio = true);

    const std::vector<std::vector<char>>& getAsciiMap() const;
private:   
    MapManager();
    ~MapManager();

    BSP2 bsp2;

    Container c;
    Tree<Container>* root;
    std::vector<Room> rooms;
    std::vector<Path> paths;
    std::vector<std::vector<char>> ascii_map;

    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;
};