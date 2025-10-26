#pragma once

struct PathNode {
    int x, y;
    float g; // Cost from start
    float h; // Heuristic to goal
    float f; // Total cost (g + h)
    PathNode* parent;
    
    PathNode(int x, int y, float g, float h, PathNode* parent = nullptr)
        : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}
    
    bool operator>(const PathNode& other) const {
        return f > other.f;
    }
};