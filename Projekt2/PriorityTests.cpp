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

static long long zmierzCzas(function<void()> op) {
    auto s = chrono::high_resolution_clock::now();
    op();
    auto e = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(e - s).count();
}

// ============================================================
// Jeden rozmiar — obie struktury
// Używa WynikiStruktur z Pomoc.hpp zamiast lokalnych zmiennych
// ============================================================
static void testujRozmiarWewn(int rozmiar, int powtorzenia, int ileSeedow,
                               ofstream& out,
                               const vector<unsigned int>& seedy) {
    WynikiStruktur wyniki; // zerowane automatycznie przez = 0 w strukturze

    for (int s = 0; s < ileSeedow; ++s) {
        const vector<int> dane = generujLosoweDane(rozmiar, seedy[s]);

        for (int rep = 0; rep < powtorzenia; ++rep) {
            cout << "  seed " << (s+1) << "/" << ileSeedow
                 << "  rozmiar " << rozmiar
                 << "  rep " << (rep+1) << "/" << powtorzenia << "\r";
            cout.flush();

            // ======= KolejkaTablica =======
            {
                KolejkaTablica kt;
                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < (int)dane.size(); i++)
                        kt.insert(dane[i], dane[i]);
                });
                wyniki.kolejkaTablica.insert += t / rozmiar;
            }

            KolejkaTablica ktFull;
            for (int i = 0; i < (int)dane.size(); i++)
                ktFull.insert(dane[i], dane[i]);

            wyniki.kolejkaTablica.peek       += zmierzCzas([&]() { ktFull.find_max(); });
            wyniki.kolejkaTablica.returnSize += zmierzCzas([&]() { ktFull.return_size(); });
            wyniki.kolejkaTablica.extract    += zmierzCzas([&]() { ktFull.extract_max(); });

            {
                KolejkaTablica ktC = ktFull;
                int t = dane[rozmiar/2];
                wyniki.kolejkaTablica.increaseKey += zmierzCzas([&]() {
                    ktC.increase_key(t, t + losujPozycje(1, 999999));
                });
            }
            {
                KolejkaTablica ktC = ktFull;
                int t = dane[rozmiar/2];
                wyniki.kolejkaTablica.decreaseKey += zmierzCzas([&]() {
                    ktC.decrease_key(t, t - losujPozycje(1, 999999));
                });
            }
            {
                KolejkaTablica ktC = ktFull;
                int t = dane[rozmiar/2];
                wyniki.kolejkaTablica.modifyKey += zmierzCzas([&]() {
                    ktC.modify_key(t, losujInt32());
                });
            }

            // ======= BinaryHeap =======
            {
                BinaryHeap bh;
                long long tb = zmierzCzas([&]() {
                    for (int i = 0; i < (int)dane.size(); i++)
                        bh.insert("e" + to_string(i), dane[i]);
                });
                wyniki.kopiecBinarny.insert += tb / rozmiar;
            }

            BinaryHeap bhFull;
            for (int i = 0; i < (int)dane.size(); i++)
                bhFull.insert("e" + to_string(i), dane[i]);

            wyniki.kopiecBinarny.peek       += zmierzCzas([&]() { bhFull.peek(); });
            wyniki.kopiecBinarny.returnSize += zmierzCzas([&]() { bhFull.returnSize(); });
            wyniki.kopiecBinarny.extract    += zmierzCzas([&]() { bhFull.extractMax(); });

            {
                BinaryHeap bhC = bhFull;
                wyniki.kopiecBinarny.increaseKey += zmierzCzas([&]() {
                    bhC.increaseKey("e" + to_string(rozmiar/2),
                                    dane[rozmiar/2] + losujPozycje(1, 999999));
                });
            }
            {
                BinaryHeap bhC = bhFull;
                wyniki.kopiecBinarny.decreaseKey += zmierzCzas([&]() {
                    bhC.decreaseKey("e" + to_string(rozmiar/2),
                                    dane[rozmiar/2] - losujPozycje(1, 999999));
                });
            }
            {
                BinaryHeap bhC = bhFull;
                wyniki.kopiecBinarny.modifyKey += zmierzCzas([&]() {
                    bhC.modifyKey("e" + to_string(rozmiar/2), losujInt32());
                });
            }
        }
        cout << "\n";
    }

    // Zapis średnich
    long long n = (long long)ileSeedow * powtorzenia;

    auto& kt = wyniki.kolejkaTablica;
    zapiszCsv(out, "KolejkaTablica", rozmiar, "insert",       kt.insert      / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "find_max",     kt.peek        / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "return_size",  kt.returnSize  / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "increase_key", kt.increaseKey / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "decrease_key", kt.decreaseKey / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "modify_key",   kt.modifyKey   / n);
    zapiszCsv(out, "KolejkaTablica", rozmiar, "extract_max",  kt.extract     / n);

    auto& bh = wyniki.kopiecBinarny;
    zapiszCsv(out, "BinaryHeap", rozmiar, "insert",      bh.insert      / n);
    zapiszCsv(out, "BinaryHeap", rozmiar, "peek",        bh.peek        / n);
    zapiszCsv(out, "BinaryHeap", rozmiar, "returnSize",  bh.returnSize  / n);
    zapiszCsv(out, "BinaryHeap", rozmiar, "increaseKey", bh.increaseKey / n);
    zapiszCsv(out, "BinaryHeap", rozmiar, "decreaseKey", bh.decreaseKey / n);
    zapiszCsv(out, "BinaryHeap", rozmiar, "modifyKey",   bh.modifyKey   / n);
    zapiszCsv(out, "BinaryHeap", rozmiar, "extractMax",  bh.extract     / n);
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
        testujRozmiar(rozmiar, powtorzenia, ileSeedow, out, seedy);
    }

    out.close();
    cout << "\n===== TESTY ZAKONCZONE =====\n\n";
}