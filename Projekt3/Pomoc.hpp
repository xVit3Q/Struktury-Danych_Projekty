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
    double insert    = 0;
    double remove    = 0;

    // Zeruje wszystkie pola — wołaj przed każdym nowym rozmiarem
    void reset() {
        insert = remove = 0;
    }
};

// ---------- wyniki obu struktur łącznie ----------
struct WynikiStruktur {
    WynikiJednejStruktury TablicaCuckoo;
    WynikiJednejStruktury TablicaOtwarta;
    WynikiJednejStruktury DrzewoAVL;

    void reset() {
        TablicaCuckoo.reset();
        TablicaOtwarta.reset();
        DrzewoAVL.reset();
    }
};

#endif // POMOC_HPP