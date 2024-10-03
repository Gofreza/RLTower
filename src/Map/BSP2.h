#pragma once

#include <SDL2/SDL.h>
#include "Container.h"
#include <iostream>
#include <random>

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

    void drawLeafContainers(SDL_Renderer* renderer) {
        if (left == nullptr && right == nullptr) {
            // This is a leaf node, draw the rectangle for the container
            drawContainer(renderer, value);
        } else {
            // Recursively call on left and right children
            if (left) left->drawLeafContainers(renderer);
            if (right) right->drawLeafContainers(renderer);
        }
    }

    void drawContainer(SDL_Renderer* renderer, const Container& container) {
        SDL_Rect rect;
        rect.x = container.x;
        rect.y = container.y;
        rect.w = container.w;
        rect.h = container.h;

        // Generate a unique color based on the container's address
        uint32_t colorSeed = reinterpret_cast<uintptr_t>(&container);
        uint8_t r = (colorSeed & 0xFF0000) >> 16;
        uint8_t g = (colorSeed & 0x00FF00) >> 8;
        uint8_t b = (colorSeed & 0x0000FF);

        // Set color for the rectangle
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};

class BSP2 {
private:
    std::mt19937 rng;
    float wRatio;
    float hRatio;
    bool discardByRatio;
public:
    BSP2() : rng(std::random_device{}()), wRatio(0.45f), hRatio(0.45f), discardByRatio(true) {}

    Tree<Container>* splitContainer(Container c, int iterations) {
        Tree<Container>* root = new Tree<Container>(c);
        if (iterations != 0) {
            std::vector<Container> split = randomSplit(c);
            root->left = splitContainer(split[0], iterations - 1);
            root->right = splitContainer(split[1], iterations - 1);
        }
        return root;
    }

    void createRooms(Tree<Container>* node, std::vector<Room>& rooms) {
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

    void createPaths(Tree<Container>* node, std::vector<Path>& paths) {
        if (node == nullptr) return;

        if (node->left == nullptr || node->right == nullptr) return;

        Path path(node->left->value, node->right->value);
        paths.push_back(path);
        createPaths(node->left, paths);
        createPaths(node->right, paths);
    }

    void generateMap(std::vector<Room>& rooms, std::vector<Path>& paths, std::vector<std::vector<char>>& map) {
        // Fill the map with rooms
        for (const auto& room : rooms) {
            for (int i = room.y; i < room.y + room.h; ++i) {
                if (i < 0 || i >= map.size()) continue; // Boundary check for rows
                for (int j = room.x; j < room.x + room.w; ++j) {
                    if (j < 0 || j >= map[i].size()) continue; // Boundary check for columns
                    map[i][j] = '.';
                }
            }
        }

        // Fill the map with paths
        for (const auto& path : paths) {
            for (int i = path.y; i < path.y + path.h; ++i) {
                if (i < 0 || i >= map.size()) continue; // Boundary check for rows
                for (int j = path.x; j < path.x + path.w; ++j) {
                    if (j < 0 || j >= map[i].size()) continue; // Boundary check for columns
                    map[i][j] = '.';
                }
            }
        }
    }

    void drawRooms(SDL_Renderer* renderer, std::vector<Room>& rooms) {
        for (const auto& room : rooms) {
            SDL_Rect rect;
            rect.x = room.x;
            rect.y = room.y;
            rect.w = room.w;
            rect.h = room.h;

            // Set color for the rectangle
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    void drawPaths(SDL_Renderer* renderer, std::vector<Path>& paths) {
        for (const auto& path : paths) {
            SDL_Rect rect;
            rect.x = path.x;
            rect.y = path.y;
            rect.w = path.w;
            rect.h = path.h;

            // Set color for the rectangle
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    void drawTree(Tree<Container>* node, std::vector<std::vector<int>>& map, int containerNumber = 1) {
        if (node == nullptr) return;

        // Fill the map with the container number
        for (int i = node->value.y; i < node->value.y + node->value.h; ++i) {
            if (i < 0 || i >= map.size()) continue; // Boundary check for rows
            for (int j = node->value.x; j < node->value.x + node->value.w; ++j) {
                if (j < 0 || j >= map[i].size()) continue; // Boundary check for columns
                map[i][j] = containerNumber;
            }
        }

        // Recursively draw the left and right subtrees with incremented container numbers
        drawTree(node->left, map, containerNumber * 2);
        drawTree(node->right, map, containerNumber * 2 + 1);
    }

    void printDungeonMap(Tree<Container>* root, int width, int height) {
        // Initialize the map with zeros
        std::vector<std::vector<int>> map(height, std::vector<int>(width, 0));

        // Fill the map using the tree
        drawTree(root, map);

        // Print the map
        for (const auto& row : map) {
            for (int cell : row) {
                if (cell == 0) {
                    std::cout << ". ";
                } else {
                    std::cout << cell % 10 << ' ';
                }
            }
            std::cout << std::endl;
        }
    }

    void setWidthRatio(float ratio) {
        wRatio = ratio;
    }

    void setHeightRatio(float ratio) {
        hRatio = ratio;
    }

    void setDiscardByRatio(bool discard) {
        discardByRatio = discard;
    }

private:
    std::vector<Container> randomSplit(Container c) {
        Container r1(0, 0, 0, 0), r2(0, 0, 0, 0);

        if (getRandomNumber(0, 1) == 0) {
            r1 = Container(
                c.x, c.y,
                getRandomNumber(1, c.w), c.h
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
                c.w, getRandomNumber(1, c.h)
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

    int getRandomNumber(int min, int max) {
        if (min > max) {
            throw std::invalid_argument("Min cannot be greater than Max");
        }

        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
};