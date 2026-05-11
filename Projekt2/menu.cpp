#include "menu.hpp"
#include <iostream>
using namespace std;

StructureType showMainMenu(int& count) {
    cout << "\n=== MENU GLOWNE — KOLEJKI PRIORYTETOWE ===\n";
    cout << "1. Wygeneruj dane i zapisz do pliku\n";
    cout << "2. Wczytaj dane z pliku i testuj recznie\n";
    cout << "3. Pelny benchmark (wszystkie rozmiary)\n";
    cout << "4. Wyjscie\n";
    cout << "Wybor: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Podaj liczbe elementow do wygenerowania: ";
            cin >> count;
            return KolejkaTablicowa;

        case 2: {
            cout << "\nWybierz strukture:\n";
            cout << "1. Kolejka Tablicowa\n";
            cout << "2. Kopiec Binarny\n";
            cout << "Wybor: ";
            int s; cin >> s;
            count = 0; // sygnał: wczytaj z pliku
            return (s == 1) ? KolejkaTablicowa : KopiecBinarnyTyp;
        }

        case 3:
            count = -2; // sygnał: pełny benchmark
            return KolejkaTablicowa;

        case 4:
            exit(0);

        default:
            cout << "Nieprawidlowy wybor.\n";
            return showMainMenu(count); // ponów pytanie
    }
}

int showOperationsMenu() {
    cout << "\n=== OPERACJE NA KOLEJCE PRIORYTETOWEJ ===\n";
    cout << "1. insert(wartosc, priorytet)\n";
    cout << "2. extract_max\n";
    cout << "3. find_max / peek\n";
    cout << "4. increaseKey\n";
    cout << "5. decreaseKey\n";
    cout << "6. return_size\n";
    cout << "7. Powrot\n";
    cout << "Wybor: ";

    int op; cin >> op;
    return op;
}