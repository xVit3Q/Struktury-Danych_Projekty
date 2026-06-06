#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <functional>

#include "menu.hpp"
#include "DrzewoAVL.hpp"
#include "TablicaCuckoo.hpp"
#include "TablicaOtwarta.hpp"
#include "Pomoc.hpp"
#include "FillTabRand.hpp"
#include "MieszanieTests.hpp"

using namespace std;

static void zmierzIWyswietl(const string& opis, function<void()> op) {
    auto s  = chrono::high_resolution_clock::now();
    op();
    auto e  = chrono::high_resolution_clock::now();
    long long ns = chrono::duration_cast<chrono::nanoseconds>(e - s).count();
    cout << "\n=== WYNIK ===\n" << opis << "\n"
         << "Czas: " << ns << " ns  (" << ns / 1'000'000.0 << " ms)\n"
         << "=============\n";
}

// ============================================================
// Menu reczne — TablicaCuckoo
// ============================================================
static void menuCuckoo(TablicaCuckoo& tc) {
    while (true) {
        int op = showOperationsMenu();
        int klucz, wartosc;

        switch (op) {
            case 1:
                cout << "Klucz:   "; cin >> klucz;
                cout << "Wartosc: "; cin >> wartosc;
                zmierzIWyswietl("TablicaCuckoo::insert",
                    [&]() { tc.insert(klucz, wartosc); });
                break;

            case 2:
                cout << "Klucz do usuniecia: "; cin >> klucz;
                zmierzIWyswietl("TablicaCuckoo::remove",
                    [&]() { tc.remove(klucz); });
                break;

            case 3:
                cout << "Rozmiar struktury: " << tc.returnSize() << endl;
                break;

            case 4: return;
            default: cout << "Nieprawidlowa opcja\n";
        }
    }
}

// ============================================================
// Menu reczne — TablicaOtwarta
// ============================================================
static void menuOtwarta(TablicaOtwarta& to) {
    while (true) {
        int op = showOperationsMenu();
        int klucz, wartosc;

        switch (op) {
            case 1:
                cout << "Klucz:   "; cin >> klucz;
                cout << "Wartosc: "; cin >> wartosc;
                zmierzIWyswietl("TablicaOtwarta::insert",
                    [&]() { to.insert(klucz, wartosc); });
                break;

            case 2:
                cout << "Klucz do usuniecia: "; cin >> klucz;
                zmierzIWyswietl("TablicaOtwarta::remove",
                    [&]() { to.remove(klucz); });
                break;
            case 3:
                cout << "Rozmiar struktury: " << to.returnSize() << endl;
                break;

            case 4: return;
            default: cout << "Nieprawidlowa opcja\n";
        }
    }
}

// ============================================================
// Menu reczne — DrzewoAVL
// ============================================================
static void menuAVL(DrzewoAVL& avl) {
    while (true) {
        int op = showOperationsMenu();
        int klucz, wartosc;

        switch (op) {
            case 1:
                cout << "Klucz:   "; cin >> klucz;
                cout << "Wartosc: "; cin >> wartosc;
                zmierzIWyswietl("DrzewoAVL::insert",
                    [&]() { avl.insert(klucz, wartosc); });
                break;

            case 2:
                cout << "Klucz do usuniecia: "; cin >> klucz;
                zmierzIWyswietl("DrzewoAVL::remove",
                    [&]() { avl.remove(klucz); });
                break;
              case 3:
                cout << "Rozmiar struktury: " << avl.returnSize() << endl;
                break;
            case 4: return;
            default: cout << "Nieprawidlowa opcja\n";
        }
    }
}

// ============================================================
// main
// ============================================================
int main() {
    while (true) {
        int count = 0;
        StructureType type = showMainMenu(count);

        // 1. Generowanie danych
        if (count > 0) {
            vector<int> dane = generujLosoweDane(count, generujSeedy(1)[0]);
            zapiszDoPliku(dane);
            cout << "Wygenerowano " << count << " elementow -> dane.txt\n";
            continue;
        }

        // 2. Tryb reczny — wczytaj z pliku
        if (count == 0) {
            vector<int> dane = wczytajZPliku();
            if (dane.empty()) {
                cout << "Plik dane.txt pusty lub nie istnieje.\n";
                continue;
            }
            cout << "Wczytano " << dane.size() << " elementow.\n";

            if (type == TypCuckoo) {
                TablicaCuckoo tc;
                for (int i = 0; i < (int)dane.size(); i++)
                    tc.insert(dane[i], i);
                cout << "Wypelniono TabliceCuckoo (" << tc.returnSize() << " elem.)\n";
                menuCuckoo(tc);
            } else if (type == TypOtwarta) {
                TablicaOtwarta to;
                for (int i = 0; i < (int)dane.size(); i++)
                    to.insert(dane[i], i);
                cout << "Wypelniono TabliceOtwarta (" << to.returnSize() << " elem.)\n";
                menuOtwarta(to);
            } else {
                DrzewoAVL avl;
                for (int i = 0; i < (int)dane.size(); i++)
                    avl.insert(dane[i], i);
                cout << "Wypelniono DrzewoAVL (" << avl.returnSize() << " elem.)\n";
                menuAVL(avl);
            }
            continue;
        }

        // 3. Pelny benchmark
        if (count == -2) {
            int powtorzenia, ileSeedow;
            cout << "Dla ilu roznych seedow benchmark? ";
            cin >> ileSeedow;
            cout << "Podaj liczbe powtorzen (np. 20): ";
            cin >> powtorzenia;
            testAllStructures(powtorzenia, ileSeedow);
            continue;
        }
    }

    return 0;
}