#include "Pathfinding.h"
#include "../Struct/Pathfinding/PathNode.h"
#include "../Struct/Pathfinding/PairHash.h"

#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

float Pathfinding::calculateHeuristic(int x1, int y1, int x2, int y2) {
    return static_cast<float>(std::max(std::abs(x2 - x1), std::abs(y2 - y1)));
}

std::pair<int, int> Pathfinding::findNextStep(
    int startX, int startY,
    int targetX, int targetY,
    std::function<bool(int, int, int, int)> canMove,
    int maxSearchDistance,
    int maxNodes
) {
    // If we're already at the target, return no movement
    if (startX == targetX && startY == targetY) {
        return {0, 0};
    }
    
    // Priority queue for open set (min-heap based on f-score)
    std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>> openSet;
    
    // Track visited nodes and their g-scores
    std::unordered_map<std::pair<int, int>, float, PairHash> gScores;
    std::unordered_map<std::pair<int, int>, PathNode*, PairHash> allNodes;
    
    // Start node
    PathNode* startNode = new PathNode(
        startX, startY, 
        0.0f, 
        calculateHeuristic(startX, startY, targetX, targetY)
    );
    openSet.push(*startNode);
    gScores[{startX, startY}] = 0.0f;
    allNodes[{startX, startY}] = startNode;
    
    PathNode* goalNode = nullptr;
    int nodesExplored = 0;
    
    // 8 directions: N, NE, E, SE, S, SW, W, NW
    const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    
    while (!openSet.empty() && nodesExplored < maxNodes) {
        PathNode current = openSet.top();
        openSet.pop();
        nodesExplored++;
        
        // Check if we reached the goal
        if (current.x == targetX && current.y == targetY) {
            goalNode = allNodes[{current.x, current.y}];
            break;
        }
        
        // Optional: limit search distance
        if (maxSearchDistance > 0) {
            int distFromStart = std::max(
                std::abs(current.x - startX), 
                std::abs(current.y - startY)
            );
            if (distFromStart > maxSearchDistance) {
                continue;
            }
        }
        
        // Explore neighbors
        for (int i = 0; i < 8; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            
            // Check if the move is valid using the callback
            if (!canMove(current.x, current.y, dx[i], dy[i])) {
                continue;
            }
            
            // Calculate cost (diagonal moves cost sqrt(2) ≈ 1.414)
            float moveCost = (dx[i] != 0 && dy[i] != 0) ? 1.414f : 1.0f;
            float newG = current.g + moveCost;
            
            std::pair<int, int> neighborKey = {newX, newY};
            
            // Check if we found a better path to this neighbor
            if (gScores.find(neighborKey) == gScores.end() || newG < gScores[neighborKey]) {
                gScores[neighborKey] = newG;
                float h = calculateHeuristic(newX, newY, targetX, targetY);
                
                PathNode* neighborNode = new PathNode(
                    newX, newY, 
                    newG, h, 
                    allNodes[{current.x, current.y}]
                );
                allNodes[neighborKey] = neighborNode;
                openSet.push(*neighborNode);
            }
        }
    }
    
    // Reconstruct path and get first step
    std::pair<int, int> nextStep = {0, 0};
    
    if (goalNode != nullptr) {
        // Backtrack to find the first step from start
        PathNode* current = goalNode;
        PathNode* previous = nullptr;
        
        while (current->parent != nullptr) {
            previous = current;
            current = current->parent;
        }
        
        // 'previous' now contains the first step
        if (previous != nullptr) {
            nextStep = {previous->x - startX, previous->y - startY};
        }
    }
    
    // Clean up allocated nodes
    for (auto& pair : allNodes) {
        delete pair.second;
    }
    
    return nextStep;
}