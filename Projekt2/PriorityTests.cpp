#include "PriorityTests.hpp"
#include "Pomoc.hpp"
#include "FillTabRand.hpp"
#include "KopiecBinarny.hpp"
#include "kolejkaTablica.hpp"
#include "losowy.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

using namespace std;

static const vector<int> ROZMIARY = {50000, 80000, 100000, 160000, 200000, 400000, 600000, 1000000};
static const int BLOK = 100;

// Zapobiega optymalizacji przez kompilator dla operacji read-only
static volatile int kompilator = 0;

static long long zmierzCzas(function<void()> op) {
    auto s = chrono::high_resolution_clock::now();
    op();
    auto e = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(e - s).count();
}

// ============================================================
// Jeden rozmiar — obie struktury
// ============================================================
static void testujRozmiarWewn(int rozmiar, int powtorzenia, int ileSeedow,
                               ofstream& out,
                               const vector<unsigned int>& seedy) {
    WynikiStruktur wyniki; // pola double — zerowane automatycznie

    for (int s = 0; s < ileSeedow; ++s) {
        const vector<int> dane = generujLosoweDane(rozmiar, seedy[s]);

        for (int rep = 0; rep < powtorzenia; ++rep) {
            cout << "  seed " << (s+1) << "/" << ileSeedow
                 << "  rozmiar " << rozmiar
                 << "  rep " << (rep+1) << "/" << powtorzenia << "\r";
            cout.flush();

            // Losowania wspólne dla obu struktur — te same wartości w tej samej iteracji
            int pozycjaInc   = losujPozycje();
            int priorytetInc = dane[pozycjaInc] + losujPriorytet(); // zawsze >= dane[pozycjaInc]
            int pozycjaDec   = losujPozycje();
            int priorytetDec = losujNizszyPriorytet(dane[pozycjaDec]); // >= 0, <= dane[pozycjaDec]
            int pozycjaMod   = losujPozycje();
            int priorytetMod = losujPriorytet();

            // ======= KolejkaTablica =======

            // insert — reserve przed pomiarem eliminuje koszt realokacji
            {
                KolejkaTablica kt;
                kt.reserve(rozmiar + 1);
                for (int i = 0; i < (int)dane.size(); i++)
                {
                    kt.insert(dane[i], dane[i]);
                }
                int nowyElement = dane[0] + 1;
                long long t = zmierzCzas([&]() {
                    kt.insert(nowyElement, nowyElement);
                });
                wyniki.kolejkaTablica.insert += static_cast<double>(t);
            }

            // Pełna struktura — źródło kopii dla operacji modyfikujących
            KolejkaTablica ktFull;
            for (int i = 0; i < (int)dane.size(); i++)
                ktFull.insert(dane[i], dane[i]);

            // find_max — blok eliminuje fałszywe zera dla szybkich operacji
            {
                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kompilator += ktFull.find_max();
                });
                wyniki.kolejkaTablica.peek += static_cast<double>(t) / BLOK;
            }

            // return_size — blok eliminuje fałszywe zera
            {
                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kompilator += ktFull.return_size();
                });
                wyniki.kolejkaTablica.returnSize += static_cast<double>(t) / BLOK;
            }

            // extract_max — własna kopia, N elementów
            {
                KolejkaTablica ktC = ktFull;
                wyniki.kolejkaTablica.extract += zmierzCzas([&]() {
                    ktC.extract_max();
                });
            }

            // increase_key — własna kopia, N elementów, losowania przed pomiarem
            {
                KolejkaTablica ktC = ktFull;
                wyniki.kolejkaTablica.increaseKey += zmierzCzas([&]() {
                    ktC.increase_key(dane[pozycjaInc], priorytetInc);
                });
            }

            // decrease_key — własna kopia, N elementów
            {
                KolejkaTablica ktC = ktFull;
                wyniki.kolejkaTablica.decreaseKey += zmierzCzas([&]() {
                    ktC.decrease_key(dane[pozycjaDec], priorytetDec);
                });
            }

            // modify_key — własna kopia, N elementów, losowanie przed pomiarem
            {
                KolejkaTablica ktC = ktFull;
                wyniki.kolejkaTablica.modifyKey += zmierzCzas([&]() {
                    ktC.modify_key(dane[pozycjaMod], priorytetMod);
                });
            }

            // ======= KopiecBinarny =======

            // insert — reserve przed pomiarem eliminuje koszt realokacji
            {
                KopiecBinarny bh;
                bh.reserve(rozmiar + 1);
                 for (int i = 0; i < (int)dane.size(); i++){
                     bh.insert(dane[i], dane[i]);
                 }
                int nowyElement = dane[0] + 1;
                long long tb = zmierzCzas([&]{
                    bh.insert(nowyElement, nowyElement);
                });
                wyniki.kopiecBinarny.insert += static_cast<double>(tb);
            }

            // Pełna struktura — źródło kopii dla operacji modyfikujących
            KopiecBinarny bhFull;
            for (int i = 0; i < (int)dane.size(); i++)
                bhFull.insert(dane[i], dane[i]);

            // find_max — blok eliminuje fałszywe zera
            {
                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kompilator += bhFull.find_max();
                });
                wyniki.kopiecBinarny.peek += static_cast<double>(t) / BLOK;
            }

            // return_size — blok eliminuje fałszywe zera
            {
                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kompilator += bhFull.return_size();
                });
                wyniki.kopiecBinarny.returnSize += static_cast<double>(t) / BLOK;
            }

            // extract_max — własna kopia, N elementów
            {
                KopiecBinarny bhC = bhFull;
                wyniki.kopiecBinarny.extract += zmierzCzas([&]() {
                    bhC.extract_max();
                });
            }

            // increase_key — własna kopia, N elementów, te same losowania co KolejkaTablica
            {
                KopiecBinarny bhC = bhFull;
                wyniki.kopiecBinarny.increaseKey += zmierzCzas([&]() {
                    bhC.increase_key(dane[pozycjaInc], priorytetInc);
                });
            }

            // decrease_key — własna kopia, N elementów
            {
                KopiecBinarny bhC = bhFull;
                wyniki.kopiecBinarny.decreaseKey += zmierzCzas([&]() {
                    bhC.decrease_key(dane[pozycjaDec], priorytetDec);
                });
            }

            // modify_key — własna kopia, N elementów
            {
                KopiecBinarny bhC = bhFull;
                wyniki.kopiecBinarny.modifyKey += zmierzCzas([&]() {
                    bhC.modify_key(dane[pozycjaMod], priorytetMod);
                });
            }
        }
        cout << "\n";
    }

    // Zapis średnich — double przez całą drogę, brak ucinania ułamków
    double n = static_cast<double>(ileSeedow) * powtorzenia;

    auto& kt = wyniki.kolejkaTablica;
    zapiszCsv(out, "KolejkaTablica", rozmiar, "insert",       kt.insert      / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "find_max",     kt.peek        / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "return_size",  kt.returnSize  / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "increase_key", kt.increaseKey / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "decrease_key", kt.decreaseKey / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "modify_key",   kt.modifyKey   / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "extract_max",  kt.extract     / n);

    auto& bh = wyniki.kopiecBinarny;
    zapiszCsv(out, "KopiecBinarny", rozmiar, "insert",       bh.insert      / n);
    zapiszCsv(out, "KopiecBinarny", rozmiar, "find_max",     bh.peek        / n);
    zapiszCsv(out, "KopiecBinarny", rozmiar, "return_size",  bh.returnSize  / n);
    zapiszCsv(out, "KopiecBinarny", rozmiar, "increase_key", bh.increaseKey / n);
    zapiszCsv(out, "KopiecBinarny", rozmiar, "decrease_key", bh.decreaseKey / n);
    zapiszCsv(out, "KopiecBinarny", rozmiar, "modify_key",   bh.modifyKey   / n);
    zapiszCsv(out, "KopiecBinarny", rozmiar, "extract_max",  bh.extract     / n);
}

void testujRozmiar(int rozmiar, int powtorzenia, int ileSeedow,
                   ofstream& out, const vector<unsigned int>& seedy) {
    cout << "\n  === Rozmiar: " << rozmiar << " ===\n";
    testujRozmiarWewn(rozmiar, powtorzenia, ileSeedow, out, seedy);
    cout << "  [" << rozmiar << "] OK\n";
}

void testAllStructures(int powtorzenia, int ileSeedow) {
    cout << "\n===== TESTY KOLEJEK PRIORYTETOWYCH =====\n";
    cout << "Seedy: " << ileSeedow
         << "  Powtorzenia/seed: " << powtorzenia << "\n\n";

    ofstream out("wyniki_kolejek.csv");
    if (!out.is_open()) { cerr << "Blad CSV\n"; return; }

    out << "Struktura,Rozmiar,Operacja,Czas_ns,Czas_ms\n";

    for (int rozmiar : ROZMIARY) {
        const vector<unsigned int> seedy = generujSeedy(ileSeedow);
        ustawRozmiar(rozmiar);
        testujRozmiar(rozmiar, powtorzenia, ileSeedow, out, seedy);
    }

    out.close();
    cout << "\n===== TESTY ZAKONCZONE =====\n\n";
}