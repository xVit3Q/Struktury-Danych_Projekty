#include "PriorityTests.hpp"
#include "Pomoc.hpp"
#include "FillTabRand.hpp"
#include "KopiecBinarny.hpp"
#include "KolejkaTablica.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

using namespace std;

static const vector<int> ROZMIARY = {10000, 50000, 100000, 500000, 1000000};

static long long zmierzCzas(function<void()> op) {
    auto s = chrono::high_resolution_clock::now();
    op();
    auto e = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(e - s).count();
}

static void zapiszWynik(ofstream& out, const string& struktura,
                        int rozmiar, const string& operacja, long long ns) {
    out << struktura << ","
        << rozmiar   << ","
        << operacja  << ","
        << ns        << ","
        << ns / 1'000'000.0 << "\n";
}

// ============================================================
// KolejkaTablica — oryginalne nazwy metod bez zmian
// ============================================================
static void testujKolejkaTablica(int rozmiar, int powtorzenia,
                                  ofstream& out,
                                  const vector<unsigned int>& seedy) {
    long long sumaInsert  = 0, sumaExtract = 0, sumaFind = 0,
              sumaModInc  = 0, sumaModDec  = 0, sumaSize = 0;

    for (int rep = 0; rep < powtorzenia; ++rep) {
        // Generujemy losowe dane — bez żadnego sortowania
        vector<int> dane = generujLosoweDane(rozmiar, seedy[rep]);

        // ---- insert — nowa instancja per powtórzenie ----
        {
            KolejkaTablica kt;
            flushCache();
            long long t = zmierzCzas([&]() {
                for (int i = 0; i < (int)dane.size(); i++)
                    kt.insert(dane[i], dane[i]); // wartosc = priorytet = dane[i]
            });
            sumaInsert += t / rozmiar; // średni czas jednego insertu
        }

        // Wypełniona instancja do pozostałych operacji
        KolejkaTablica ktFull;
        for (int i = 0; i < (int)dane.size(); i++)
            ktFull.insert(dane[i], dane[i]);

        // ---- find_max ----
        {
            flushCache();
            sumaFind += zmierzCzas([&]() { ktFull.find_max(); });
        }

        // ---- return_size ----
        {
            flushCache();
            sumaSize += zmierzCzas([&]() { ktFull.return_size(); });
        }

        // ---- modify_key increase — środkowy element, priorytet + 999999 ----
        {
            KolejkaTablica ktCopy = ktFull;
            int target = dane[rozmiar / 2];
            flushCache();
            sumaModInc += zmierzCzas([&]() {
                ktCopy.modify_key(target, target + 999999);
            });
        }

        // ---- modify_key decrease — środkowy element, priorytet - 999999 ----
        {
            KolejkaTablica ktCopy = ktFull;
            int target = dane[rozmiar / 2];
            flushCache();
            sumaModDec += zmierzCzas([&]() {
                ktCopy.modify_key(target, target - 999999);
            });
        }

        // ---- extract_max ----
        {
            flushCache();
            sumaExtract += zmierzCzas([&]() { ktFull.extract_max(); });
        }
    }

    zapiszWynik(out, "KolejkaTablica", rozmiar, "insert",
                sumaInsert  / powtorzenia);
    zapiszWynik(out, "KolejkaTablica", rozmiar, "find_max",
                sumaFind    / powtorzenia);
    zapiszWynik(out, "KolejkaTablica", rozmiar, "return_size",
                sumaSize    / powtorzenia);
    zapiszWynik(out, "KolejkaTablica", rozmiar, "modify_key_inc",
                sumaModInc  / powtorzenia);
    zapiszWynik(out, "KolejkaTablica", rozmiar, "modify_key_dec",
                sumaModDec  / powtorzenia);
    zapiszWynik(out, "KolejkaTablica", rozmiar, "extract_max",
                sumaExtract / powtorzenia);
}

// ============================================================
// BinaryHeap
// ============================================================
static void testujBinaryHeap(int rozmiar, int powtorzenia,
                              ofstream& out,
                              const vector<unsigned int>& seedy) {
    long long sumaInsert = 0, sumaExtract = 0, sumaFind = 0,
              sumaInc    = 0, sumaDec     = 0, sumaSize = 0;

    for (int rep = 0; rep < powtorzenia; ++rep) {
        vector<int> dane = generujLosoweDane(rozmiar, seedy[rep]);

        // ---- insert ----
        {
            BinaryHeap bh;
            flushCache();
            long long t = zmierzCzas([&]() {
                for (int i = 0; i < (int)dane.size(); i++)
                    bh.insert("e" + to_string(i), dane[i]);
            });
            sumaInsert += t / rozmiar;
        }

        // Wypełniona instancja
        BinaryHeap bhFull;
        for (int i = 0; i < (int)dane.size(); i++)
            bhFull.insert("e" + to_string(i), dane[i]);

        // ---- peek ----
        {
            flushCache();
            sumaFind += zmierzCzas([&]() { bhFull.peek(); });
        }

        // ---- returnSize ----
        {
            flushCache();
            sumaSize += zmierzCzas([&]() { bhFull.returnSize(); });
        }

        // ---- increaseKey ----
        {
            BinaryHeap bhCopy = bhFull;
            flushCache();
            sumaInc += zmierzCzas([&]() {
                bhCopy.increaseKey("e" + to_string(rozmiar / 2),
                                   dane[rozmiar / 2] + 999999);
            });
        }

        // ---- decreaseKey ----
        {
            BinaryHeap bhCopy = bhFull;
            flushCache();
            sumaDec += zmierzCzas([&]() {
                bhCopy.decreaseKey("e" + to_string(rozmiar / 2),
                                   dane[rozmiar / 2] - 999999);
            });
        }

        // ---- extractMax ----
        {
            flushCache();
            sumaExtract += zmierzCzas([&]() { bhFull.extractMax(); });
        }
    }

    zapiszWynik(out, "BinaryHeap", rozmiar, "insert",
                sumaInsert / powtorzenia);
    zapiszWynik(out, "BinaryHeap", rozmiar, "peek",
                sumaFind   / powtorzenia);
    zapiszWynik(out, "BinaryHeap", rozmiar, "returnSize",
                sumaSize   / powtorzenia);
    zapiszWynik(out, "BinaryHeap", rozmiar, "increaseKey",
                sumaInc    / powtorzenia);
    zapiszWynik(out, "BinaryHeap", rozmiar, "decreaseKey",
                sumaDec    / powtorzenia);
    zapiszWynik(out, "BinaryHeap", rozmiar, "extractMax",
                sumaExtract/ powtorzenia);
}

// ============================================================
// Jeden rozmiar — obie struktury
// ============================================================
void testujRozmiar(int rozmiar, int powtorzenia, ofstream& out,
                   const vector<unsigned int>& seedy) {
    cout << "  Rozmiar: " << rozmiar << "\n";
    testujKolejkaTablica(rozmiar, powtorzenia, out, seedy);
    testujBinaryHeap    (rozmiar, powtorzenia, out, seedy);
    cout << "    OK\n";
}

// ============================================================
// Pełny benchmark
// ============================================================
void testStructuresSr(int powtorzenia) {
    cout << "\n===== TESTY KOLEJEK PRIORYTETOWYCH =====\n\n";

    ofstream out("wyniki_kolejek.csv");
    if (!out.is_open()) { cerr << "Blad otwarcia pliku CSV\n"; return; }

    out << "Struktura,Rozmiar,Operacja,Czas_ns,Czas_ms\n";

    for (int rozmiar : ROZMIARY) {
        cout << "\n--- Rozmiar: " << rozmiar << " ---\n";
        vector<unsigned int> seedy = generujSeedy(powtorzenia);
        testujRozmiar(rozmiar, powtorzenia, out, seedy);
    }

    out.close();
    cout << "\n===== TESTY ZAKONCZONE =====\n\n";
}