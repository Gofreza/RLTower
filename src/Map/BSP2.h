#pragma once

// #include <SDL2/SDL.h>
#include <iostream>
#include <random>

#include "Container.h"
#include "Cell.h"

template <typename T>
class Tree {
public:
    T value;
    Tree<T>* left;
    Tree<T>* right;

    Tree(T value) : value(value), left(nullptr), right(nullptr) {}
    ~Tree() {
        delete left;
        delete right;
    }

    // void drawLeafContainers(SDL_Renderer* renderer) {
    //     if (left == nullptr && right == nullptr) {
    //         // This is a leaf node, draw the rectangle for the container
    //         drawContainer(renderer, value);
    //     } else {
    //         // Recursively call on left and right children
    //         if (left) left->drawLeafContainers(renderer);
    //         if (right) right->drawLeafContainers(renderer);
    //     }
    // }

    // void drawContainer(SDL_Renderer* renderer, const Container& container) {
    //     SDL_Rect rect;
    //     rect.x = container.x;
    //     rect.y = container.y;
    //     rect.w = container.w;
    //     rect.h = container.h;
    //     // Generate a unique color based on the container's address
    //     uint32_t colorSeed = reinterpret_cast<uintptr_t>(&container);
    //     uint8_t r = (colorSeed & 0xFF0000) >> 16;
    //     uint8_t g = (colorSeed & 0x00FF00) >> 8;
    //     uint8_t b = (colorSeed & 0x0000FF);
    //     // Set color for the rectangle
    //     SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    //     SDL_RenderFillRect(renderer, &rect);
    // }
};

class BSP2 {
private:
    float wRatio;
    float hRatio;
    bool discardByRatio;
public:
    BSP2();

    Tree<Container>* splitContainer(Container c, int iterations);

    void createRooms(Tree<Container>* node, std::vector<Room>& rooms);

    void createPaths(Tree<Container>* node, std::vector<Path>& paths);

    void generateMap(std::vector<Room>& rooms, std::vector<Path>& paths, std::vector<std::vector<Cell>>& map);

    // void drawRooms(SDL_Renderer* renderer, std::vector<Room>& rooms) {
    //     for (const auto& room : rooms) {
    //         SDL_Rect rect;
    //         rect.x = room.x;
    //         rect.y = room.y;
    //         rect.w = room.w;
    //         rect.h = room.h;
    //         // Set color for the rectangle
    //         SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
    //         SDL_RenderFillRect(renderer, &rect);
    //     }
    // }

    // void drawPaths(SDL_Renderer* renderer, std::vector<Path>& paths) {
    //     for (const auto& path : paths) {
    //         SDL_Rect rect;
    //         rect.x = path.x;
    //         rect.y = path.y;
    //         rect.w = path.w;
    //         rect.h = path.h;
    //         // Set color for the rectangle
    //         SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
    //         SDL_RenderFillRect(renderer, &rect);
    //     }
    // }

    // void drawTree(Tree<Container>* node, std::vector<std::vector<int>>& map, int containerNumber = 1) {
    //     if (node == nullptr) return;
    //     // Fill the map with the container number
    //     for (int i = node->value.y; i < node->value.y + node->value.h; ++i) {
    //         if (i < 0 || i >= map.size()) continue; // Boundary check for rows
    //         for (int j = node->value.x; j < node->value.x + node->value.w; ++j) {
    //             if (j < 0 || j >= map[i].size()) continue; // Boundary check for columns
    //             map[i][j] = containerNumber;
    //         }
    //     }
    //     // Recursively draw the left and right subtrees with incremented container numbers
    //     drawTree(node->left, map, containerNumber * 2);
    //     drawTree(node->right, map, containerNumber * 2 + 1);
    // }

    // void printDungeonMap(Tree<Container>* root, int width, int height) {
    // Initialize the map with zeros
    //     std::vector<std::vector<int>> map(height, std::vector<int>(width, 0));
    //     // Fill the map using the tree
    //     drawTree(root, map);
    //     // Print the map
    //     for (const auto& row : map) {
    //         for (int cell : row) {
    //             if (cell == 0) {
    //                 std::cout << ". ";
    //             } else {
    //                 std::cout << cell % 10 << ' ';
    //             }
    //         }
    //         std::cout << std::endl;
    //     }
    // }

    void setWidthRatio(float ratio);

    void setHeightRatio(float ratio);

    void setDiscardByRatio(bool discard);

private:
    std::vector<Container> randomSplit(Container c);
};