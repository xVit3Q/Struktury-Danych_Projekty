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

// ---------- wyniki jednej struktury ----------
// Trzyma sumy czasów — AVG liczone przy zapisie przez n = seedy*powtorzenia
struct WynikiJednejStruktury {
    long long insert      = 0;
    long long extract     = 0;
    long long peek        = 0;
    long long increaseKey = 0;
    long long decreaseKey = 0;
    long long modifyKey   = 0;
    long long returnSize  = 0;

    // Zeruje wszystkie pola — wołaj przed każdym nowym rozmiarem
    void reset() {
        insert = extract = peek = 0;
        increaseKey = decreaseKey = modifyKey = returnSize = 0;
    }
};

// ---------- wyniki obu struktur łącznie ----------
struct WynikiStruktur {
    WynikiJednejStruktury kolejkaTablica;
    WynikiJednejStruktury kopiecBinarny;

    void reset() {
        kolejkaTablica.reset();
        kopiecBinarny.reset();
    }
};

#endif // POMOC_HPP