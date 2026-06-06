#include "menu.hpp"
#include <iostream>
using namespace std;

StructureType showMainMenu(int& count) {
    cout << "\n=== MENU GLOWNE — TABLICE MIESZAJACE ===\n";
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
            return TypCuckoo;

        case 2: {
            cout << "\nWybierz strukture:\n";
            cout << "1. TablicaCuckoo\n";
            cout << "2. TablicaOtwarta\n";
            cout << "3. DrzewoAVL\n";
            cout << "Wybor: ";
            int s;
            cin >> s;
            count = 0;
            if (s == 1) return TypCuckoo;
            if (s == 2) return TypOtwarta;
            return TypAVL;
        }

        case 3:
            count = -2;
            return TypCuckoo;

        case 4:
            exit(0);

        default:
            cout << "Nieprawidlowy wybor.\n";
            return showMainMenu(count);
    }
}

int showOperationsMenu() {
    cout << "\n=== OPERACJE NA TABLICY MIESZAJACEJ ===\n";
    cout << "1. insert(klucz, wartosc)\n";
    cout << "2. remove(klucz)\n";
    cout << "3. zwroc rozmiar struktury\n";
    cout << "4. Powrot\n";
    cout << "Wybor: ";

    int op;
    cin >> op;
    return op;
}