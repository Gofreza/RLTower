#include "MapManager.h"
#include "../../Misc/RandomUtils.h"

MapManager::MapManager()
: bsp2(), c(0, 0, 0, 0), root(nullptr), rooms(), paths(), ascii_map()
{
}

void MapManager::initialize(Config* config)
{
    this->config = config;
}

void MapManager::generateMap(int width, int height, int iterations, float wRatio, float hRatio, bool discardByRatio)
{   
    this->width = width;
    this->height = height;

    bsp2.setWidthRatio(wRatio);
    bsp2.setHeightRatio(hRatio);
    bsp2.setDiscardByRatio(discardByRatio);

    c = Container(0, 0, width, height);
    root = bsp2.splitContainer(c, iterations);
    bsp2.createRooms(root, rooms);
    bsp2.createPaths(root, paths);

    ascii_map = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell(0, 0, '#', {100, 100, 100, 255})));
    bsp2.generateMap(rooms, paths, ascii_map);
}

void MapManager::removeCharacter(int dx, int dy) {
    this->ascii_map[dy][dx].removeCharacter();
    this->ascii_map[dy][dx].resetCell();
}

//=========
// Player
//=========

void MapManager::addPlayer(Player* player)
{
    if (rooms.empty()) {
        return;
    }

    // Pick a random room
    const Room& room = rooms[rand() % rooms.size()];
    // Place the player in the center of the room
    ascii_map[room.y + room.h / 2][room.x + room.w / 2].addCharacter(player);
    ascii_map[room.y + room.h / 2][room.x + room.w / 2].currentColor = player->getColor();
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

    if (!config->isDebugMode()) {
        for (const auto& [i, j] : circle_extremes) {
            size_t map_x = x + i;
            size_t map_y = y + j;

            if (map_x >= 0 && map_x < ascii_map[0].size() && map_y >= 0 && map_y < ascii_map.size()) {
                bresenham(x, y, map_x, map_y);
            }
        }
    } else {
        // If debug mode is on, reveal the entire map
        for (auto& row : ascii_map) {
            for (auto& cell : row) {
                cell.isInSight = true;
                cell.isExplored = true;
            }
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

    ascii_map[old_y][old_x].removeCharacter();
    ascii_map[old_y][old_x].resetCell();
    ascii_map[y][x].addCharacter(player);
    ascii_map[y][x].currentColor = player->getColor();

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

    if (!config->isDebugMode()) {
        for (const auto& [i, j] : circle_extremes) {
            size_t map_x = x + i;
            size_t map_y = y + j;

            if (map_x >= 0 && map_x < ascii_map[0].size() && map_y >= 0 && map_y < ascii_map.size()) {
                bresenham(x, y, map_x, map_y);
            }
        }
    } else {
        // If debug mode is on, reveal the entire map
        for (auto& row : ascii_map) {
            for (auto& cell : row) {
                cell.isInSight = true;
                cell.isExplored = true;
            }
        }
    }
}

bool MapManager::canPlayerMove(Player* player, int dx, int dy)
{    
    int x = player->getXPosition();
    int y = player->getYPosition();

    return ascii_map[y + dy][x + dx].isWalkable && !ascii_map[y + dy][x + dx].hasCharacter();
}

//=========
// Enemies
//=========

void MapManager::addEnemies(std::vector<Enemy*> enemies)
{
    if (rooms.empty()) {
        return;
    }

    for (auto& enemy : enemies) {
        // Get random number
        int random = RandomUtils::getRandomNumber(0, rooms.size() - 1);
        // Pick a random room
        const Room& room = rooms[random];
        // Place randomly the enemy in the room
        int x = room.x + rand() % room.w;
        int y = room.y + rand() % room.h;
        ascii_map[y][x].addCharacter(enemy);
        ascii_map[y][x].currentColor = enemy->getColor();
        enemy->setXPosition(x);
        enemy->setYPosition(y);
    }
}

void MapManager::moveCharacterInMap(Character* character, int dx, int dy)
{
    // Move player
    int x = character->getXPosition();
    int y = character->getYPosition();
    int old_x = x - dx;
    int old_y = y - dy;

    ascii_map[old_y][old_x].removeCharacter();
    ascii_map[old_y][old_x].resetCell();
    ascii_map[y][x].addCharacter(character);
    ascii_map[y][x].currentColor = character->getColor();
}

bool MapManager::canCharacterMove(Character* character, int dx, int dy)
{
    int x = character->getXPosition();
    int y = character->getYPosition();

    return ascii_map[y + dy][x + dx].isWalkable && !ascii_map[y + dy][x + dx].hasCharacter();
}

//=========
// Miscs
//=========

bool MapManager::dropItem(int x, int y, Item* item) {
    // Check if the current position already has an item
    if (ascii_map[y][x].hasItem()) {
        // Directions for adjacent cells: up, down, left, right, and diagonals
        static const int dx[] = { -1,  0,  1, -1, 1, -1, 0,  1 };
        static const int dy[] = { -1, -1, -1,  0, 0,  1, 1,  1 };

        // Try to find an empty adjacent cell
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Ensure the position is within bounds
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                // Check if the cell is empty
                if (!ascii_map[ny][nx].hasItem() && ascii_map[ny][nx].isWalkable) {
                    ascii_map[ny][nx].setItem(item);
                    return true;
                }
            }
        }

        // If no empty cell is found
        Logger::instance().warning(LocalizationManager::instance().getText("no_empty_cell_found"));
        return false;
    }

    // If the current position is empty, place the item
    ascii_map[y][x].setItem(item);
    return true;
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
            ascii_map[y1][x1].setLastSeenSymbol(ascii_map[y1][x1].getSymbol());
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
            ascii_map[y1][x1].setLastSeenSymbol(ascii_map[y1][x1].getSymbol());
            this->visibleCells.push_back(&ascii_map[y1][x1]);
 
            // Check if there is a wall
            if (ascii_map[y1][x1].getSymbol() == '#') {
                return;
            }
        }
    }
}

void MapManager::calculateFov(Player* player) {
    // Move player
    int x = player->getXPosition();
    int y = player->getYPosition();

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
        size_t map_x = x + i;
        size_t map_y = y + j;

        if (map_x >= 0 && map_x < ascii_map[0].size() && map_y >= 0 && map_y < ascii_map.size()) {
            bresenham(x, y, map_x, map_y);
        }
    }

}

const std::vector<std::vector<Cell>>& MapManager::getAsciiMap() const {
    return ascii_map;
}

Cell& MapManager::getCell(int x, int y) {
    return ascii_map[y][x];
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