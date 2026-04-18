#ifndef POMOCNICZE_HPP
#define POMOCNICZE_HPP

#include <vector>
#include <string>

void logujWynik(const std::string& opis, long long ns);
int losujInt32();
void zapiszDoPliku(const std::vector<int>& dane);
void zapiszCsv(std::ofstream& plik, const std::string& struktura, int rozmiar, const std::string& operacja, long long ns);
std::vector<int> wczytajZPliku();
std::vector<int> generujDane(int count);

#endif 