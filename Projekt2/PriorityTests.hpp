#ifndef PRIORITYTESTS_HPP
#define PRIORITYTESTS_HPP

#include <string>
#include <fstream>
#include <vector>
#include <functional>

// Mierzy czas sortowania — dane przekazywane PRZEZ WARTOŚĆ (kopia powstaje
// przy wywołaniu), więc sorter zawsze dostaje świeżą, nieposortowaną kopię.
long long zmierzCzasSortowania(std::vector<int> dane,
                               std::function<void(std::vector<int>&)> sortFunc);

// Jeden rozmiar + jeden typ danych → zapisuje średnią z `powtorzenia` pomiarów
void testujRozmiarITyp(int rozmiar, const std::string& typ, int powtorzenia,
                       std::ofstream& out);

// Jeden rozmiar × wszystkie typy danych
void testujRozmiar(int rozmiar, int powtorzenia, std::ofstream& out);

// Jeden typ danych × wszystkie rozmiary
void testujTypDanych(const std::string& typ, int powtorzenia, std::ofstream& out);

// Pełny benchmark: wszystkie rozmiary
void testAllStructures(int powtorzenia, int ileSeedow);

#endif // PRIORITYTESTS HPP