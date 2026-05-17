#ifndef POMOC_HPP
#define POMOC_HPP

#include <vector>
#include <string>
#include <fstream>

// ---------- narzędzia ogólne ----------
void logujWynik(const std::string& opis, long long ns);
void zapiszDoPliku(const std::vector<int>& dane);
void zapiszCsv(std::ofstream& plik, const std::string& struktura,
               int rozmiar, const std::string& operacja, double ns);
std::vector<int> wczytajZPliku();

// ---------- wyniki jednej struktury ----------
// Trzyma sumy czasów — AVG liczone przy zapisie przez n = seedy*powtorzenia
struct WynikiJednejStruktury {
    double insert      = 0;
    double extract     = 0;
    double peek        = 0;
    double increaseKey = 0;
    double decreaseKey = 0;
    double modifyKey   = 0;
    double returnSize  = 0;

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