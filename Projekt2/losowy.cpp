#include "losowy.hpp"
#include <random>
#include <limits>
#include <chrono>

static std::mt19937& getRng() {
    static std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );
    return rng;
}

int losujPozycje(int min, int max) {
    return std::uniform_int_distribution<int>(min, max)(getRng());
}

int losujInt32() {
    // Ograniczamy do dodatnich żeby uniknąć problemów z decrease_key
    // (target - losujInt32() może overflow gdy losujInt32() jest ujemne)
    return std::uniform_int_distribution<int>(0,
        std::numeric_limits<int>::max())(getRng());
}