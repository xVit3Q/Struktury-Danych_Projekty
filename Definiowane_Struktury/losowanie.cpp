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

int losujPozycje(int min, int max) {
    // tworzymy distribution na stosie — kompilator to zoptymalizuje
    // ale zakres jest zawsze poprawny
    return std::uniform_int_distribution<int>(min, max)(getRng());
}

int losujInt32() {
    // tu zakres to pełny int — distribution nie jest potrzebny
    return (int)getRng()();
}