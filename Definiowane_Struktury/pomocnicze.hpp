#ifndef POMOCNICZE_HPP
#define POMOCNICZE_HPP

#include <vector>
#include <string>

void logujWynik(const std::string& opis, long long ns);
void zapiszDoPliku(const std::vector<int>& dane);
void zapiszCsv(std::ofstream& plik, const std::string& struktura, int rozmiar, const std::string& operacja, long long ns);
std::vector<int> wczytajZPliku();
std::vector<int> generujDane(int count);

struct WynikiOperacji {
    long long dodP = 0, dodK = 0, dodPos = 0, dodLos = 0;
    long long usP = 0, usK = 0, usPos = 0, usLos = 0;
    long long szuk0 = 0, szuk25 = 0, szuk50 = 0, szuk75 = 0, szuk100 = 0;

        void resetujWyniki() {
            dodP = dodK = dodPos = dodLos = 0;
            usP = usK = usPos = usLos = 0;
            szuk0 = szuk25 = szuk50 = szuk75 = szuk100 = 0;
        }
};
struct WynikiStruktur {
    WynikiOperacji tablica;
    WynikiOperacji jednokierunkowa;
    WynikiOperacji dwukierunkowa;

    void reset() {
        tablica.resetujWyniki();
        jednokierunkowa.resetujWyniki();
        dwukierunkowa.resetujWyniki();
    }
};


#endif  // POMOCNICZE_HPP
