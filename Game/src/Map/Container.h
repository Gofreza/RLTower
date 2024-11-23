#pragma once

#include <random>
#include <cmath>
#include <stdexcept>
#include "../Misc/RandomUtils.h"

class Container
{
public:
    std::mt19937 rng;
    int x, y;
    int w, h;
    int centerX, centerY;

    Container(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), centerX(x + (w/2)), centerY(y + (h/2)) {}
};

class Room {
public:
    int gutter = 2;
    int x, y;
    int w, h;
    int centerX, centerY;

    Room(Container& c) {
        // Calculate x and y with gutter applied
        x = c.x + gutter + RandomUtils::getRandomNumber(0, std::floor((c.w - 2 * gutter) / 3));
        y = c.y + gutter + RandomUtils::getRandomNumber(0, std::floor((c.h - 2 * gutter) / 3));

        // Calculate width and height with gutter applied
        w = c.w - (x - c.x) - gutter;
        h = c.h - (y - c.y) - gutter;

        // Further reduce width and height randomly, with gutter taken into account
        w -= RandomUtils::getRandomNumber(0, w / 3);
        h -= RandomUtils::getRandomNumber(0, h / 3);

        centerX = x + (w / 2);
        centerY = y + (h / 2);
    }
};

class Path {
public:
    int x, y;
    int w, h;

    Path(Container& c, Container& c2) {
        int startX = c.centerX;
        int startY = c.centerY;
        int endX = c2.centerX;
        int endY = c2.centerY;
        
        x = std::min(startX, endX);
        y = std::min(startY, endY);

        w = std::abs(endX - startX);
        if (w == 0) {
            w = 3;
        }

        h = std::abs(endY - startY);
        if (h == 0) {
            h = 3;
        }
    }
};
