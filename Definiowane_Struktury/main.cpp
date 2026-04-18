#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <limits>

#include "menu.hpp"
#include "listaDwukierunkowa.hpp"

using namespace std;

int losujInt32() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    return distribution(generator);
}
void zapiszDoPliku(const vector<int>& dane) {
    ofstream file("dane.txt");
    for (int x : dane) file << x << "\n";
    file.close();
}

vector<int> wczytajZPliku() {
    vector<int> dane;
    ifstream file("dane.txt");
    int x;
    while (file >> x) dane.push_back(x);
    return dane;
}

int main() {
    while (true) {

        int count = 0;
        StructureType selected = showMainMenu(count);

        vector<int> dane;

        if (count > 0) {
            dane.reserve(count);

            for (int i = 0; i < count; i++) {
                dane.push_back(losujInt32());
            }

            zapiszDoPliku(dane);
            cout << "Wygenerowano i zapisano dane do dane.txt\n\n";
            continue; // wracamy do menu głównego
        }

        dane = wczytajZPliku();
        cout << "Wczytano " << dane.size() << " elementow z pliku.\n";

        ListaDwukierunkowa lista;

        if (selected == Dwukierunkowa) {
            for (int x : dane) lista.dodajNaKoniec(x);
        }

        while (true) {
            int op = showOperationsMenu();
            if (op == 9) break; // powrót

            int value, pos;

            switch (op) {
                case 1:
                    cout << "Podaj wartosc: ";
                    cin >> value;
                    lista.dodajNaPoczatek(value);
                    break;

                case 2:
                    cout << "Podaj wartosc: ";
                    cin >> value;
                    lista.dodajNaKoniec(value);
                    break;

                case 3:
                    cout << "Podaj wartosc: ";
                    cin >> value;
                    cout << "Podaj pozycje: ";
                    cin >> pos;
                    lista.dodajNaPozycje(value, pos);
                    break;

                case 4:
                    lista.usunZPoczatku();
                    break;

                case 5:
                    lista.usunZKonca();
                    break;

                case 6:
                    cout << "Podaj pozycje: ";
                    cin >> pos;
                    lista.usunZPozycji(pos);
                    break;

                case 7:
                    cout << "Podaj wartosc do wyszukania: ";
                    cin >> value;
                    lista.szukaj(value);
                    break;

                case 8:
                    lista.wyswietl();
                    break;

                default:
                    cout << "Niepoprawna opcja!\n";
            }
        }
    }

    return 0;
}
