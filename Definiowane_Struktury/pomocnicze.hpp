#ifndef POMOCNICZE_HPP
#define POMOCNICZE_HPP

#include <vector>
#include <string>

void logujWynik(const std::string& opis, long long ns);
int losujInt32();
void zapiszDoPliku(const std::vector<int>& dane);
std::vector<int> wczytajZPliku();
std::vector<int> generujDane(int count);

#endif 