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

    ascii_map = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell('#')));
    bsp2.generateMap(rooms, paths, ascii_map);
}

void MapManager::addPlayer(Player* player)
{
    if (rooms.empty()) {
        return;
    }

    // Pick a random room
    const Room& room = rooms[rand() % rooms.size()];
    // Place the player in the center of the room
    ascii_map[room.y + room.h / 2][room.x + room.w / 2].addPlayer(player);
    // ascii_map[room.y + room.h / 2][room.x + room.w / 2].setSymbol('@');
    player->setXPosition(room.x + room.w / 2);
    player->setYPosition(room.y + room.h / 2);
}

void MapManager::movePlayerInMap(Player* player, int dx, int dy)
{
    int x = player->getXPosition();
    int y = player->getYPosition();
    int old_x = x - dx;
    int old_y = y - dy;

    ascii_map[old_y][old_x].removePlayer();
    ascii_map[y][x].addPlayer(player);
}

bool MapManager::canPlayerMove(Player* player, int dx, int dy)
{    
    int x = player->getXPosition();
    int y = player->getYPosition();

    return ascii_map[y + dy][x + dx].isWalkable;
}

const std::vector<std::vector<Cell>>& MapManager::getAsciiMap() const {
    return ascii_map;
}

void MapManager::printDungeonMap() {
    for (const auto& row : ascii_map) {
        for (const auto& cell : row) {
            std::cout << cell.getSymbol();
        }
        std::cout << std::endl;
    }
}

MapManager::~MapManager()
{
    delete root;
    root = nullptr;
}