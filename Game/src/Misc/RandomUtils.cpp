#include "RandomUtils.h"

namespace RandomUtils {
    std::random_device rd;
    std::mt19937 rng(rd());

    int getRandomNumber(int min, int max) {
        if (min > max) {
            throw std::invalid_argument("Min cannot be greater than Max");
        }

        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
}