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

void MapManager::addPlayer()
{
    if (rooms.empty()) {
        return;
    }

    // Pick a random room
    const Room& room = rooms[rand() % rooms.size()];
    // Place the player in the center of the room
    ascii_map[room.y + room.h / 2][room.x + room.w / 2] = '@';
    Player* player = CharactersManager::instance().getPlayer();
    player->setXPosition(room.x + room.w / 2);
    player->setYPosition(room.y + room.h / 2);
}

const std::vector<std::vector<char>>& MapManager::getAsciiMap() const {
    return ascii_map;
}

void MapManager::printDungeonMap() {
    for (const auto& row : ascii_map) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

MapManager::~MapManager()
{
    delete root;
    root = nullptr;
}