#pragma once

#include <random>
#include <stdexcept>

namespace RandomUtils {
    extern std::mt19937 rng;

    int getRandomNumber(int min, int max);
}