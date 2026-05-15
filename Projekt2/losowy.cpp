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
//ustawienie rozmiaru
static int g_rozmiar = 1;
void ustawRozmiar(int r) {g_rozmiar = r;}

int losujPozycje() {
    return std::uniform_int_distribution<int>(0, g_rozmiar)(getRng());
}

int losujPriorytet() {
    return std::uniform_int_distribution<int>(0, 2*g_rozmiar)(getRng());
}