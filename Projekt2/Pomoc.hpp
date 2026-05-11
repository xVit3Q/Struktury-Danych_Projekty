#ifndef POMOC_HPP
#define POMOC_HPP

#include <vector>
#include <string>
#include <fstream>

// ---------- narzędzia ogólne ----------
void logujWynik(const std::string& opis, long long ns);
void zapiszDoPliku(const std::vector<int>& dane);
void zapiszCsv(std::ofstream& plik, const std::string& struktura,
               int rozmiar, const std::string& operacja, long long ns);
std::vector<int> wczytajZPliku();
void flushCache();

// ---------- przygotowanie danych testowych ----------
// Tworzy wariant tablicy o zadanym stopniu posortowania.
// Obsługiwane typy: "Random", "25%Sorted", "50%Sorted", "75%Sorted",
//                   "95%Sorted", "99%Sorted", "99.7%Sorted", "Reversed"
std::vector<int> przygotujDane(const std::vector<int>& baza,
                               const std::string& typ);

// ---------- struktury wyników ----------
struct WynikiOperacji {
    long long dodP   = 0, dodK   = 0, dodPos = 0, dodLos = 0;
    long long usP    = 0, usK    = 0, usPos  = 0, usLos  = 0;
    long long szuk0  = 0, szuk25 = 0, szuk50 = 0, szuk75 = 0, szuk100 = 0;

    void resetujWyniki() {
        dodP = dodK = dodPos = dodLos = 0;
        usP  = usK  = usPos  = usLos  = 0;
        szuk0 = szuk25 = szuk50 = szuk75 = szuk100 = 0;
    }
};

struct WynikiStruktur {
    WynikiOperacji wyniki_MergeSort;
    WynikiOperacji wyniki_QuickSort;
    WynikiOperacji wyniki_IntroSort;

    void reset() {
        wyniki_MergeSort.resetujWyniki();
        wyniki_QuickSort.resetujWyniki();
        wyniki_IntroSort.resetujWyniki();
    }
};

#endif // POMOC_HPP