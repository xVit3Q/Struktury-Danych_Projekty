#include "FillTabRand.hpp"
#include <random>
#include <vector>

std::vector<int> generujLosoweDane(int n, unsigned int seed) {
    std::mt19937 rng(seed);                 
    // ZMIANA: Zakres losowania zależy teraz bezpośrednio od rozmiaru n
    // Losujemy liczby w zakresie int32 od INT_MIN do INT_MAX, aby zapewnić pełną różnorodność danych
      std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    std::vector<int> dane;
    dane.reserve(n);

    for (int i = 0; i < n; i++) {
        dane.push_back(dist(rng));
    }

    return dane;
}

std::vector<unsigned int> generujSeedy(int ile) {
    std::random_device rd;                  
    std::vector<unsigned int> seedy;
    seedy.reserve(ile);

    for (int i = 0; i < ile; i++) {
        seedy.push_back(rd());              
    }

    return seedy;
}