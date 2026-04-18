#include <iostream>
#include "menu.hpp"

using namespace std;

StructureType showMainMenu(int &count) {
    cout << "=== MENU GLOWNE ===\n";
    cout << "1. Wygeneruj dane i zapisz do pliku\n";
    cout << "2. Wczytaj dane z pliku i wybierz strukture\n";
    cout << "3. Wyjscie\n";

    int choice;
    cin >> choice;

    if (choice == 3) exit(0);

    if (choice == 1) {
        cout << "Ile danych wygenerowac: ";
        cin >> count;
        return Dynamiczna; // placeholder, strukture wybierzesz później
    }

    if (choice == 2) {
        cout << "Wybierz strukture:\n";
        cout << "1. Tablica dynamiczna\n";
        cout << "2. Lista jednokierunkowa\n";
        cout << "3. Lista dwukierunkowa\n";

        int s;
        cin >> s;

        switch(s) {
            case 1: return Dynamiczna;
            case 2: return Jednokierunkowa;
            case 3: return Dwukierunkowa;
        }
    }

    return Dynamiczna;
}

int showOperationsMenu() {
    cout << "\n=== OPERACJE ===\n";
    cout << "1. Dodaj na poczatek\n";
    cout << "2. Dodaj na koniec\n";
    cout << "3. Dodaj na pozycje\n";
    cout << "4. Usun z poczatku\n";
    cout << "5. Usun z konca\n";
    cout << "6. Usun z pozycji\n";
    cout << "7. Wyszukaj liczbe\n";
    cout << "8. Wyswietl\n";
    cout << "9. Powrot\n";

    int op;
    cin >> op;
    return op;
}
