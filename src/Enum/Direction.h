#pragma once

enum class Direction {
    North,
    East,
    South,
    West,
    None
};

inline std::pair<int, int> getDirectionOffset(Direction direction)
{
    switch (direction) {
        case Direction::North:
            return {0, -1};
        case Direction::East:
            return {1, 0};
        case Direction::South:
            return {0, 1};
        case Direction::West:
            return {-1, 0};
        case Direction::None:
            return {0, 0};
    }
    return {0, 0};
}