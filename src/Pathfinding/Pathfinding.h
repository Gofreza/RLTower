#pragma once

#include <utility>
#include <functional>

class Pathfinding
{
public:
    static std::pair<int, int> findNextStep(
        int startX, int startY,
        int targetX, int targetY,
        std::function<bool(int, int, int, int)> canMove,
        int maxSearchDistance = 0,
        int maxNodes = 500
    );
private:
    Pathfinding() = delete;

    static float calculateHeuristic(int x1, int y1, int x2, int y2);
};