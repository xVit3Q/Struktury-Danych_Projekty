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
    WynikiStruktur wyniki;

    for (int s = 0; s < ileSeedow; ++s) {
        const vector<int> dane = generujLosoweDane(rozmiar, seedy[s]);

        for (int rep = 0; rep < powtorzenia; ++rep) {
            cout << "  seed " << (s+1) << "/" << ileSeedow
                 << "  rozmiar " << rozmiar
                 << "  rep " << (rep+1) << "/" << powtorzenia << "\r";

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

            long long czasFindMaxT = zmierzCzas([&](){
                for  (int i = 0; i < BLOK; i++)
                {
                    ktFull.find_max();
                }
            });
            wyniki.kolejkaTablica.peek += czasFindMaxT /BLOK;
            long long czasRetunSizeT = zmierzCzas([&](){
                     for  (int i = 0; i < BLOK; i++)
                {
                    ktFull.return_size();
                }
            });
            wyniki.kolejkaTablica.returnSize += czasRetunSizeT /BLOK;
            
            {
                KolejkaTablica  ktC = ktFull;
                wyniki.kolejkaTablica.extract += zmierzCzas([&](){
                    ktC.extract_max();
                });
            
            }


            {
                KolejkaTablica ktC = ktFull;
                int wartosc = dane[losujPozycje()];
                int nowePrio = wartosc + losujPriorytet(); // zawsze >= wartosc, czyli >= 0
                wyniki.kolejkaTablica.increaseKey += zmierzCzas([&]() {
                    ktC.increase_key(wartosc, nowePrio);
                });
            }
            {
                KolejkaTablica ktC = ktFull;
                int wartosc = dane[losujPozycje()];
                int nowePrio = losujNizszyPriorytet(wartosc); 
                wyniki.kolejkaTablica.decreaseKey += zmierzCzas([&]() {
                    ktC.decrease_key(wartosc, nowePrio);
                });
            }
            {
                KolejkaTablica ktC = ktFull;
                int wartosc = dane[losujPozycje()];
                wyniki.kolejkaTablica.modifyKey += zmierzCzas([&]() {
                    ktC.modify_key(wartosc, losujPriorytet()); // dowolny nowy priorytet
                });
            }

            // ======= KopiecBinarny =======
            {
                KopiecBinarny bh;
                long long tb = zmierzCzas([&]() {
                    for (int i = 0; i < (int)dane.size(); i++)
                        bh.insert(dane[i], dane[i]);
                });
                wyniki.kopiecBinarny.insert += tb / rozmiar;
            }

            KopiecBinarny bhFull;
            for (int i = 0; i < (int)dane.size(); i++)
                bhFull.insert(dane[i], dane[i]);

                   long long czasFindMaxB = zmierzCzas([&](){
                for  (int i = 0; i < BLOK; i++)
                {
                    bhFull.find_max();
                }
            });
            wyniki.kopiecBinarny.peek += czasFindMaxB /BLOK;
            long long czasRetunSizeB = zmierzCzas([&](){
                     for  (int i = 0; i < BLOK; i++)
                {
                    bhFull.return_size();
                }
            });
            wyniki.kopiecBinarny.returnSize += czasRetunSizeB / BLOK;
            {
                KopiecBinarny  bhC = bhFull;
                wyniki.kopiecBinarny.extract += zmierzCzas([&](){
                    bhC.extract_max();
                });
            
            }

            {
                KopiecBinarny bhC = bhFull;
                int wartosc = dane[losujPozycje()];
                int nowePrio = wartosc + losujPriorytet(); // zawsze >= wartosc
                wyniki.kopiecBinarny.increaseKey += zmierzCzas([&]() {
                    bhC.increase_key(wartosc, nowePrio);
                });
            }
            {
                KopiecBinarny bhC = bhFull;
                int wartosc = dane[losujPozycje()];
                int nowePrio = losujNizszyPriorytet(wartosc); // >= 0
                wyniki.kopiecBinarny.decreaseKey += zmierzCzas([&]() {
                    bhC.decrease_key(wartosc, nowePrio);
                });
            }
            {
                KopiecBinarny bhC = bhFull;
                int wartosc = dane[losujPozycje()];
                wyniki.kopiecBinarny.modifyKey += zmierzCzas([&]() {
                    bhC.modify_key(wartosc, losujPriorytet());
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