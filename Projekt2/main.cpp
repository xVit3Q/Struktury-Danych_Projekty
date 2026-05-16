#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <functional>

#include "menu.hpp"
#include "KopiecBinarny.hpp"
#include "kolejkaTablica.hpp"
#include "pomoc.hpp"
#include "FillTabRand.hpp"
#include "PriorityTests.hpp"

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
// Menu ręczne — KolejkaTablica (oryginalne nazwy metod)
// ============================================================
static void menuKolejkaTablica(KolejkaTablica& kt) {
    while (true) {
        int op = showOperationsMenu();
        int wartosc, priorytet;

        switch (op) {
            case 1: // insert(int, int)
                cout << "Wartosc (int):   "; cin >> wartosc;
                cout << "Priorytet (int): "; cin >> priorytet;
                zmierzIWyswietl("KolejkaTablica::insert",
                    [&]() { kt.insert(wartosc, priorytet); });
                break;

            case 2: // extract_max
                zmierzIWyswietl("KolejkaTablica::extract_max",
                    [&]() {
                        int v = kt.extract_max();
                        cout << "  Usunieto max: " << v << "\n";
                    });
                break;

            case 3: // find_max
                zmierzIWyswietl("KolejkaTablica::find_max",
                    [&]() {
                        cout << "  Max: " << kt.find_max() << "\n";
                    });
                break;

            case 4: // modify_key (increase)
                cout << "Wartosc elementu:  "; cin >> wartosc;
                cout << "Nowy priorytet:    "; cin >> priorytet;
                zmierzIWyswietl("KolejkaTablica::modify_key (increase)",
                    [&]() { kt.modify_key(wartosc, priorytet); });
                break;

            case 5: // modify_key (decrease)
                cout << "Wartosc elementu:  "; cin >> wartosc;
                cout << "Nowy priorytet:    "; cin >> priorytet;
                zmierzIWyswietl("KolejkaTablica::modify_key (decrease)",
                    [&]() { kt.modify_key(wartosc, priorytet); });
                break;

            case 6: // return_size
                zmierzIWyswietl("KolejkaTablica::return_size",
                    [&]() {
                        cout << "  Rozmiar: " << kt.return_size() << "\n";
                    });
                break;

            case 7: return;
            default: cout << "Nieprawidlowa opcja\n";
        }
    }
}

// ============================================================
// Menu ręczne — BinaryHeap
// ============================================================
static void menuKopiecBinarny(KopiecBinarny& kb) {
    while (true) {
        int op = showOperationsMenu();
        int wartosc, priorytet;

        switch (op) {
            case 1: // insert(int, int)
                cout << "Wartosc (int):   "; cin >> wartosc;
                cout << "Priorytet (int): "; cin >> priorytet;
                zmierzIWyswietl("KolejkaTablica::insert",
                    [&]() { kb.insert(wartosc, priorytet); });
                break;

            case 2: // extract_max
                zmierzIWyswietl("KolejkaTablica::extract_max",
                    [&]() {
                        int v = kb.extract_max();
                        cout << "  Usunieto max: " << v << "\n";
                    });
                break;

            case 3: // find_max
                zmierzIWyswietl("KolejkaTablica::find_max",
                    [&]() {
                        cout << "  Max: " << kb.find_max() << "\n";
                    });
                break;

            case 4: // modify_key (increase)
                cout << "Wartosc elementu:  "; cin >> wartosc;
                cout << "Nowy priorytet:    "; cin >> priorytet;
                zmierzIWyswietl("KolejkaTablica::modify_key (increase)",
                    [&]() { kb.modify_key(wartosc, priorytet); });
                break;

            case 5: // modify_key (decrease)
                cout << "Wartosc elementu:  "; cin >> wartosc;
                cout << "Nowy priorytet:    "; cin >> priorytet;
                zmierzIWyswietl("KolejkaTablica::modify_key (decrease)",
                    [&]() { kb.modify_key(wartosc, priorytet); });
                break;

            case 6: // return_size
                zmierzIWyswietl("KolejkaTablica::return_size",
                    [&]() {
                        cout << "  Rozmiar: " << kb.return_size() << "\n";
                    });
                break;

            case 7: return;
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
            vector<int> dane = generujLosoweDane(count, 12345);
            zapiszDoPliku(dane);
            cout << "Wygenerowano " << count << " elementow -> dane.txt\n";
            continue;
        }

        // 2. Tryb ręczny — wczytaj z pliku
        if (count == 0) {
            vector<int> dane = wczytajZPliku();
            if (dane.empty()) {
                cout << "Plik dane.txt pusty lub nie istnieje.\n";
                continue;
            }
            cout << "Wczytano " << dane.size() << " elementow.\n";

            if (type == KolejkaTablicowa) {
                KolejkaTablica kt;
                for (int i = 0; i < (int)dane.size(); i++)
                    kt.insert(dane[i], i); // insert(int wartosc, int priorytet)
                cout << "Wypelniono KolejkaTablica (" << kt.return_size() << " elem.)\n";
                menuKolejkaTablica(kt);
            } else {
                KopiecBinarny kb;
                for (int i = 0; i < (int)dane.size(); i++)
                    kb.insert(dane[i], i); // insert(int wartosc, int priorytet)
                cout << "Wypelniono KopiecBinarny (" << kb.return_size() << " elem.)\n";
                menuKopiecBinarny(kb);
            }
            continue;
        }

        // 3. Pełny benchmark
        if (count == -2) {
            int powtorzenia, ileSeedow;
            cout << "Dla ilu różncy seedów benchmark?";
            cin >> ileSeedow;
            cout << "Podaj liczbe powtorzen (np. 20): ";
            cin >> powtorzenia;
            testAllStructures(powtorzenia, ileSeedow);
            continue;
        }
    }

    return 0;
}
