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
    return std::uniform_int_distribution<int>(0, g_rozmiar-1)(getRng());
}

int losujWartosc() {
    return std::uniform_int_distribution<int>(INT_MIN, INT_MAX)(getRng());
}
int losujKlucz() {
    return std::uniform_int_distribution<int>(0, std::numeric_limits<uint32_t>::max())(getRng());
}