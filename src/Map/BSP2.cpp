#include "BSP2.h"
#include <set>

BSP2::BSP2()
: wRatio(0.45f), hRatio(0.45f), discardByRatio(true) 
{}

Tree<Container>* BSP2::splitContainer(Container c, int iterations) {
    Tree<Container>* root = new Tree<Container>(c);
    if (iterations != 0) {
        std::vector<Container> split = randomSplit(c);
        root->left = splitContainer(split[0], iterations - 1);
        root->right = splitContainer(split[1], iterations - 1);
    }
    return root;
}

void BSP2::createRooms(Tree<Container>* node, std::vector<Room>& rooms) {
    if (node == nullptr) return;

    if (node->left == nullptr && node->right == nullptr) {
        // This is a leaf node, create a room
        Room room(node->value);
        rooms.push_back(room);
    } else {
        // Recursively call on left and right children
        createRooms(node->left, rooms);
        createRooms(node->right, rooms);
    }
    
}

void BSP2::createPaths(Tree<Container>* node, std::vector<Path>& paths) {
    if (node == nullptr) return;

    if (node->left == nullptr || node->right == nullptr) return;

    Path path(node->left->value, node->right->value);
    paths.push_back(path);
    createPaths(node->left, paths);
    createPaths(node->right, paths);
}

void BSP2::generateMap(std::vector<Room>& rooms, std::vector<Path>& paths, std::vector<std::vector<Cell>>& map) {
    // Fill the map with rooms
    std::set<std::pair<int, int>> visitedCells;

    // Fill the map with rooms
    for (const auto& room : rooms) {
        for (size_t i = room.y; i < room.y + room.h; ++i) {
            if (i < 0 || i >= map.size()) continue; // Boundary check for rows
            for (size_t j = room.x; j < room.x + room.w; ++j) {
                if (j < 0 || j >= map[i].size()) continue; // Boundary check for columns
                std::pair<int, int> cellPos = {i, j};
                if (visitedCells.find(cellPos) == visitedCells.end()) {
                    SDL_Color color = {
                        static_cast<Uint8>(std::max(0, map[i][j].baseColor.r - 50)),
                        static_cast<Uint8>(std::max(0, map[i][j].baseColor.g - 50)),
                        static_cast<Uint8>(std::max(0, map[i][j].baseColor.b - 50)),
                        map[i][j].baseColor.a // Assuming alpha channel remains unchanged
                    };
                    map[i][j] = Cell('.', color);
                    visitedCells.insert(cellPos);
                }
            }
        }
    }

    // Fill the map with paths
    for (const auto& path : paths) {
        for (size_t i = path.y; i < path.y + path.h; ++i) {
            if (i < 0 || i >= map.size()) continue; // Boundary check for rows
            for (size_t j = path.x; j < path.x + path.w; ++j) {
                if (j < 0 || j >= map[i].size()) continue; // Boundary check for columns
                std::pair<int, int> cellPos = {i, j};
                if (visitedCells.find(cellPos) == visitedCells.end()) {
                    SDL_Color color = {
                        static_cast<Uint8>(std::max(0, map[i][j].baseColor.r - 50)),
                        static_cast<Uint8>(std::max(0, map[i][j].baseColor.g - 50)),
                        static_cast<Uint8>(std::max(0, map[i][j].baseColor.b - 50)),
                        map[i][j].baseColor.a // Assuming alpha channel remains unchanged
                    };
                    map[i][j] = Cell('.', color);
                    visitedCells.insert(cellPos);
                }
            }
        }
    }
}

void BSP2::setWidthRatio(float ratio) {
    wRatio = ratio;
}

void BSP2::setHeightRatio(float ratio) {
    hRatio = ratio;
}

void BSP2::setDiscardByRatio(bool discard) {
    discardByRatio = discard;
}

std::vector<Container> BSP2::randomSplit(Container c) {
    Container r1(0, 0, 0, 0), r2(0, 0, 0, 0);

    if (RandomUtils::getRandomNumber(0, 1) == 0) {
        r1 = Container(
            c.x, c.y,
            RandomUtils::getRandomNumber(1, c.w), c.h
        );
        r2 = Container(
            c.x + r1.w, c.y,
            c.w - r1.w, c.h
        );

        if (discardByRatio) {
            float r1_w_ratio = static_cast<float>(r1.w) / r1.h;
            float r2_w_ratio = static_cast<float>(r2.w) / r2.h;
            if (r1_w_ratio < wRatio || r2_w_ratio < wRatio) {
                return randomSplit(c);
            }
        }
    } else {
        r1 = Container(
            c.x, c.y,
            c.w, RandomUtils::getRandomNumber(1, c.h)
        );
        r2 = Container(
            c.x, c.y + r1.h,
            c.w, c.h - r1.h
        );

        if (discardByRatio) {
            float r1_h_ratio = static_cast<float>(r1.h) / r1.w;
            float r2_h_ratio = static_cast<float>(r2.h) / r2.w;
            if (r1_h_ratio < hRatio || r2_h_ratio < hRatio) {
                return randomSplit(c);
            }
        }
    }

    return {r1, r2};
}