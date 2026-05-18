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

            // ======= KolejkaTablica =======
            {
                KolejkaTablica kt;
                //kt.reserve(rozmiar);
                long long t = zmierzCzas([&]() {
                    for (int i = 0; i < (int)dane.size(); i++)
                        kt.insert(dane[i], losujPriorytet());
                });
                wyniki.kolejkaTablica.insert += t;
            }
            
            KolejkaTablica ktFull;
            for (int i = 0; i < (int)dane.size(); i++)
                ktFull.insert(dane[i], losujPriorytet());

            long long czasFindMaxT = zmierzCzas([&](){
                for (int i = 0; i < BLOK; i++)
                {
                    kompilator += ktFull.find_max();
                }
            });
            wyniki.kolejkaTablica.peek += czasFindMaxT;

            long long czasRetunSizeT = zmierzCzas([&](){
                 for (int i = 0; i < BLOK; i++)
                {
                    kompilator += ktFull.return_size();
                }
            });
            wyniki.kolejkaTablica.returnSize += czasRetunSizeT;

            // --- KOLEJKA TABLICA: extract_max ---
            {
                KolejkaTablica* kopieKT = new KolejkaTablica[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieKT[i] = ktFull; 
                }
                wyniki.kolejkaTablica.extract += zmierzCzas([&](){
                    for (int i = 0; i < BLOK; i++) {
                        kopieKT[i].extract_max();
                    }
                });
                delete[] kopieKT;
            }

            // --- KOLEJKA TABLICA: increase_key ---
            {
                KolejkaTablica* kopieKT = new KolejkaTablica[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieKT[i] = ktFull;
                }
                int wartosc = dane[losujPozycje()];
                int nowePrio = wartosc + losujPriorytet(); 

                wyniki.kolejkaTablica.increaseKey += zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++) {
                        kopieKT[i].increase_key(wartosc, nowePrio);
                    }
                });
                delete[] kopieKT;
            }

            // --- KOLEJKA TABLICA: decrease_key ---
            {
                KolejkaTablica* kopieKT = new KolejkaTablica[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieKT[i] = ktFull;
                }
                int wartosc = dane[losujPozycje()];
                int nowePrio = losujNizszyPriorytet(wartosc); 

                wyniki.kolejkaTablica.decreaseKey += zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++) {
                        kopieKT[i].decrease_key(wartosc, nowePrio);
                    }
                });
                delete[] kopieKT;
            }

            // --- KOLEJKA TABLICA: modify_key ---
            {
                KolejkaTablica* kopieKT = new KolejkaTablica[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieKT[i] = ktFull;
                }
                int wartosc = dane[losujPozycje()];

                wyniki.kolejkaTablica.modifyKey += zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++) {
                        kopieKT[i].modify_key(wartosc, losujPriorytet());
                    }
                });
                delete[] kopieKT;
            }

            // ======= KopiecBinarny =======
            {
                KopiecBinarny bh;
                //bh.reserve(rozmiar);
                long long tb = zmierzCzas([&]() {
                    for (int i = 0; i < (int)dane.size(); i++)
                        bh.insert(dane[i], losujPriorytet());
                });
                wyniki.kopiecBinarny.insert += tb;
            }

            KopiecBinarny bhFull;
            for (int i = 0; i < (int)dane.size(); i++)
                bhFull.insert(dane[i], losujPriorytet());

            long long czasFindMaxB = zmierzCzas([&](){
                for (int i = 0; i < BLOK; i++)
                {
                    kompilator += bhFull.find_max();
                }
            });
            wyniki.kopiecBinarny.peek += czasFindMaxB;

            long long czasRetunSizeB = zmierzCzas([&](){
                 for (int i = 0; i < BLOK; i++)
                {
                    kompilator += bhFull.return_size();
                }
            });
            wyniki.kopiecBinarny.returnSize += czasRetunSizeB;
            
            // --- KOPIEC BINARNY: extract_max ---
            {
                KopiecBinarny* kopieBH = new KopiecBinarny[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieBH[i] = bhFull; 
                }
                wyniki.kopiecBinarny.extract += zmierzCzas([&](){
                    for (int i = 0; i < BLOK; i++) {
                        kopieBH[i].extract_max();
                    }
                });
                delete[] kopieBH;
            }

            // --- KOPIEC BINARNY: increase_key ---
            {
                KopiecBinarny* kopieBH = new KopiecBinarny[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieBH[i] = bhFull;
                }
                int wartosc = dane[losujPozycje()];
                int nowePrio = wartosc + losujPriorytet(); 

                wyniki.kopiecBinarny.increaseKey += zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++) {
                        kopieBH[i].increase_key(wartosc, nowePrio);
                    }
                });
                delete[] kopieBH;
            }

            // --- KOPIEC BINARNY: decrease_key ---
            {
                KopiecBinarny* kopieBH = new KopiecBinarny[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieBH[i] = bhFull;
                }
                int wartosc = dane[losujPozycje()];
                int nowePrio = losujNizszyPriorytet(wartosc); 

                wyniki.kopiecBinarny.decreaseKey += zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++) {
                        kopieBH[i].decrease_key(wartosc, nowePrio);
                    }
                });
                delete[] kopieBH;
            }

            // --- KOPIEC BINARNY: modify_key ---
            {
                KopiecBinarny* kopieBH = new KopiecBinarny[BLOK];
                for (int i = 0; i < BLOK; i++) {
                    kopieBH[i] = bhFull;
                }
                int wartosc = dane[losujPozycje()];

                wyniki.kopiecBinarny.modifyKey += zmierzCzas([&]() {
                    for (int i = 0; i < BLOK; i++) {
                        kopieBH[i].modify_key(wartosc, losujPriorytet());
                    }
                });
                delete[] kopieBH;
            }
        }
        cout << "\n";
    }

    // Zapis średnich
    long long n = (long long)ileSeedow * powtorzenia;

    auto& kt = wyniki.kolejkaTablica;
    zapiszCsv(out, "KolejkaTablica", rozmiar, "insert",       (double)kt.insert       / (n * rozmiar));
    zapiszCsv(out, "KolejkaTablica", rozmiar, "find_max",     (double)kt.peek         / (n * BLOK));
    zapiszCsv(out, "KolejkaTablica", rozmiar, "return_size",  (double)kt.returnSize   / (n * BLOK));
    zapiszCsv(out, "KolejkaTablica", rozmiar, "increase_key", (double)kt.increaseKey / (n * BLOK));
    zapiszCsv(out, "KolejkaTablica", rozmiar, "decrease_key", (double)kt.decreaseKey / (n * BLOK));
    zapiszCsv(out, "KolejkaTablica", rozmiar, "modify_key",   (double)kt.modifyKey   / (n * BLOK));
    zapiszCsv(out, "KolejkaTablica", rozmiar, "extract_max",  (double)kt.extract     / (n * BLOK));

    auto& bh = wyniki.kopiecBinarny;
    zapiszCsv(out, "KopiecBinarny", rozmiar, "insert",       (double)bh.insert       / (n * rozmiar));
    zapiszCsv(out, "KopiecBinarny", rozmiar, "find_max",     (double)bh.peek         / (n * BLOK));
    zapiszCsv(out, "KopiecBinarny", rozmiar, "return_size",  (double)bh.returnSize   / (n * BLOK));
    zapiszCsv(out, "KopiecBinarny", rozmiar, "increase_key", (double)bh.increaseKey / (n * BLOK));
    zapiszCsv(out, "KopiecBinarny", rozmiar, "decrease_key", (double)bh.decreaseKey / (n * BLOK));
    zapiszCsv(out, "KopiecBinarny", rozmiar, "modify_key",   (double)bh.modifyKey   / (n * BLOK));
    zapiszCsv(out, "KopiecBinarny", rozmiar, "extract_max",  (double)bh.extract     / (n * BLOK));
} // NAPRAWIONE: Usunięto nadmiarową klamrę stąd

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