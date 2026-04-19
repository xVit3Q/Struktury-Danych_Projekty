#include "losowanie.hpp"
#include <random>
#include <limits>
#include <chrono>

static std::mt19937& getRng() {
    static std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );
    return rng;
}

// Losowanie z zakresu [min, max]
int losujPozycje(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(getRng());
}

// Losowanie z pełnego zakresu int
int losujInt32() {
    static std::uniform_int_distribution<int> dist(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    return dist(getRng());
}