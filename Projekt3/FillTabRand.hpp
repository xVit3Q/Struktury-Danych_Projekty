#ifndef FILLTABRAND_HPP
#define FILLTABRAND_HPP

#include <vector>

// Generuje n losowych liczb int z zakresu [-1 000 000 000, 1 000 000 000]
// przy użyciu podanego seeda – wynik jest deterministyczny dla tego samego seeda.
std::vector<int>generujLosoweDane(int n, unsigned int seed);

// Generuje 'ile' niezależnych seedów ze sprzętowego źródła entropii.
std::vector<unsigned int> generujSeedy(int ile);

#endif  // FILLTABRAND_HPP
