#include "MieszanieTests.hpp"
#include "Pomoc.hpp"
#include "FillTabRand.hpp"
#include "TablicaCuckoo.hpp"
#include "TablicaOtwarta.hpp"
#include "DrzewoAVL.hpp"
#include "losowy.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

using namespace std;

static const vector<int> ROZMIARY = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000};
static const int BLOK = 100;
static volatile int kompilator = 0;

static long long zmierzCzas(function<void()> op) {
    auto s = chrono::high_resolution_clock::now();
    op();
    auto e = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(e - s).count();
}

static void testujRozmiarWewn(int rozmiar, int powtorzenia, int ileSeedow,
                               ofstream& out,
                               const vector<unsigned int>& seedy) {
    WynikiStruktur wyniki;

    for (int s = 0; s < ileSeedow; ++s) {
        const vector<int> dane = generujLosoweDane(rozmiar, seedy[s]);

        for (int rep = 0; rep < powtorzenia; ++rep) {
            cout << "  seed " << (s+1) << "/" << ileSeedow
                 << "  rozmiar " << rozmiar
                 << "  rep " << (rep+1) << "/" << powtorzenia << "\r";

            // ======= TablicaCuckoo =======

            TablicaCuckoo tcFull;
            for (int i = 0; i < (int)dane.size(); i++)
                tcFull.insert(dane[i], i);

            // --- insert: BLOK kopii pełnej struktury, każda dostaje jeden nowy insert ---
            {
                TablicaCuckoo* kopie = new TablicaCuckoo[BLOK];
                for (int i = 0; i < BLOK; i++)
                    kopie[i] = tcFull;

                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kopie[i].insert(losujKlucz(), losujWartosc());
                });
                wyniki.TablicaCuckoo.insert += t;

                delete[] kopie;
            }

            // --- remove: BLOK kopii pełnej struktury, każda dostaje jedno remove ---
            {
                TablicaCuckoo* kopie = new TablicaCuckoo[BLOK];
                for (int i = 0; i < BLOK; i++)
                    kopie[i] = tcFull;

                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kopie[i].remove(dane[losujPozycje()]);
                });
                wyniki.TablicaCuckoo.remove += t;

                delete[] kopie;
            }

            // ======= TablicaOtwarta =======

            TablicaOtwarta toFull;
            for (int i = 0; i < (int)dane.size(); i++)
                toFull.insert(dane[i], i);

            // --- insert ---
            {
                TablicaOtwarta* kopie = new TablicaOtwarta[BLOK];
                for (int i = 0; i < BLOK; i++)
                    kopie[i] = toFull;

                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kopie[i].insert(losujKlucz(), losujWartosc());
                });
                wyniki.TablicaOtwarta.insert += t;

                delete[] kopie;
            }

            // --- remove ---
            {
                TablicaOtwarta* kopie = new TablicaOtwarta[BLOK];
                for (int i = 0; i < BLOK; i++)
                    kopie[i] = toFull;

                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kopie[i].remove(dane[losujPozycje()]);
                });
                wyniki.TablicaOtwarta.remove += t;

                delete[] kopie;
            }

            // ======= DrzewoAVL =======

            DrzewoAVL avlFull;
            for (int i = 0; i < (int)dane.size(); i++)
                avlFull.insert(dane[i], i);

            // --- insert ---
            {
                DrzewoAVL* kopie = new DrzewoAVL[BLOK];
                for (int i = 0; i < BLOK; i++)
                    kopie[i] = avlFull;

                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kopie[i].insert(losujKlucz(), losujWartosc());
                });
                wyniki.DrzewoAVL.insert += t;

                delete[] kopie;
            }

            // --- remove ---
            {
                DrzewoAVL* kopie = new DrzewoAVL[BLOK];
                for (int i = 0; i < BLOK; i++)
                    kopie[i] = avlFull;

                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++)
                        kopie[i].remove(dane[losujPozycje()]);
                });
                wyniki.DrzewoAVL.remove += t;

                delete[] kopie;
            }
        }
        cout << "\n";
    }
    //Srednie czasy w nanosekundach, dzielone przez n = seedy*powtorzenia, oraz przez BLOK, bo tyle operacji wykonujemy w kazdym pomiarze
    long long n = (long long)ileSeedow * powtorzenia;

    zapiszCsv(out, "TablicaCuckoo",  rozmiar, "insert", (double)wyniki.TablicaCuckoo.insert  / (n * BLOK));
    zapiszCsv(out, "TablicaCuckoo",  rozmiar, "remove", (double)wyniki.TablicaCuckoo.remove  / (n * BLOK));
    zapiszCsv(out, "TablicaOtwarta", rozmiar, "insert", (double)wyniki.TablicaOtwarta.insert / (n * BLOK));
    zapiszCsv(out, "TablicaOtwarta", rozmiar, "remove", (double)wyniki.TablicaOtwarta.remove / (n * BLOK));
    zapiszCsv(out, "DrzewoAVL",      rozmiar, "insert", (double)wyniki.DrzewoAVL.insert      / (n * BLOK));
    zapiszCsv(out, "DrzewoAVL",      rozmiar, "remove", (double)wyniki.DrzewoAVL.remove      / (n * BLOK));
}

void testujRozmiar(int rozmiar, int powtorzenia, int ileSeedow,
                   ofstream& out, const vector<unsigned int>& seedy) {
    cout << "\n  === Rozmiar: " << rozmiar << " ===\n";
    testujRozmiarWewn(rozmiar, powtorzenia, ileSeedow, out, seedy);
    cout << "  [" << rozmiar << "] OK\n";
}

void testAllStructures(int powtorzenia, int ileSeedow) {
    cout << "\n===== TESTY TABLIC MIESZAJACYCH =====\n";
    cout << "Seedy: " << ileSeedow
         << "  Powtorzenia/seed: " << powtorzenia << "\n\n";

    ofstream out("wyniki_tablic.csv");
    if (!out.is_open()) { cerr << "Blad CSV\n"; return; }

    out << "Struktura,Rozmiar,Operacja,Czas_ns,Czas_ms\n";

    const vector<unsigned int> seedy = generujSeedy(ileSeedow);

    for (int rozmiar : ROZMIARY) {
        ustawRozmiar(rozmiar);
        testujRozmiar(rozmiar, powtorzenia, ileSeedow, out, seedy);
    }

    out.close();
    cout << "\n===== TESTY ZAKONCZONE =====\n\n";
}