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

    // Set cells visibility around the player
    int x = player->getXPosition();
    int y = player->getYPosition();
    int fov = player->getFov();

    // Get all circle extremes
    std::vector<std::pair<int, int>> circle_extremes;
    for (int i = -fov; i <= fov; i++) {
        for (int j = -fov; j <= fov; j++) {
            if (i * i + j * j <= fov * fov) {
                circle_extremes.push_back(std::make_pair(i, j));
            }
        }
    }

    for (const auto& [i, j] : circle_extremes) {
        int map_x = x + i;
        int map_y = y + j;

        if (map_x >= 0 && map_x < ascii_map[0].size() && map_y >= 0 && map_y < ascii_map.size()) {
            bresenham(x, y, map_x, map_y);
        }
    }
}

void MapManager::movePlayerInMap(Player* player, int dx, int dy)
{
    // Move player
    int x = player->getXPosition();
    int y = player->getYPosition();
    int old_x = x - dx;
    int old_y = y - dy;

    ascii_map[old_y][old_x].removePlayer();
    ascii_map[y][x].addPlayer(player);

    // Check cells visibility
    int fov = player->getFov();

    // Get all circle extremes
    std::vector<std::pair<int, int>> circle_extremes;
    for (int i = -fov; i <= fov; i++) {
        for (int j = -fov; j <= fov; j++) {
            if (i * i + j * j <= fov * fov) {
                circle_extremes.push_back(std::make_pair(i, j));
            }
        }
    }
    
    for (auto& cell : visibleCells) {
        cell->isInSight = false;
    }
    visibleCells.clear();

    for (const auto& [i, j] : circle_extremes) {
        int map_x = x + i;
        int map_y = y + j;

        if (map_x >= 0 && map_x < ascii_map[0].size() && map_y >= 0 && map_y < ascii_map.size()) {
            bresenham(x, y, map_x, map_y);
        }
    }
}

bool MapManager::canPlayerMove(Player* player, int dx, int dy)
{    
    int x = player->getXPosition();
    int y = player->getYPosition();

    return ascii_map[y + dy][x + dx].isWalkable;
}

void MapManager::bresenham(int x1,
    int y1,
    int const x2,
    int const y2)
{
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    // Set the player cell as explored
    ascii_map[y1][x1].isInSight = true;
    ascii_map[y1][x1].isExplored = true;

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;

            ascii_map[y1][x1].isInSight = true;
            ascii_map[y1][x1].isExplored = true;
            this->visibleCells.push_back(&ascii_map[y1][x1]);

            // Check if there is a wall
            if (ascii_map[y1][x1].getSymbol() == '#') {
                return;
            }
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;

            ascii_map[y1][x1].isInSight = true;
            ascii_map[y1][x1].isExplored = true;
            this->visibleCells.push_back(&ascii_map[y1][x1]);
 
            // Check if there is a wall
            if (ascii_map[y1][x1].getSymbol() == '#') {
                return;
            }
        }
    }
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