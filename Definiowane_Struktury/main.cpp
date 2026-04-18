#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <limits>
#include <chrono>
#include <string>

#include "menu.hpp"
#include "tablicaDynamiczna.hpp"
#include "listaJednokierunkowa.hpp"
#include "listaDwukierunkowa.hpp"

using namespace std;

void logujWynik(const string& opis, long long ns) {
    ofstream log("wyniki.txt", ios::app);
    if (log.is_open()) {
        double ms = ns / 1'000'000.0;
        log << opis << " | " << ns << " ns (" << ms << " ms)" << endl;
    }
}

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
}

vector<int> wczytajZPliku() {
    vector<int> dane;
    ifstream file("dane.txt");
    int x;
    while (file >> x) dane.push_back(x);
    return dane;
}

int main() {
cout.flush();
    while (true) {

        int count = 0;
        StructureType selected = showMainMenu(count);

        // ============================
        // GENEROWANIE DANYCH
        // ============================
        if (count > 0) {
            vector<int> dane;
            dane.reserve(count);

            for (int i = 0; i < count; i++)
                dane.push_back(losujInt32());

            zapiszDoPliku(dane);
            cout << "Wygenerowano i zapisano dane do dane.txt\n\n";

            continue; // wracamy do menu głównego
        }

        // ============================
        // WCZYTYWANIE DANYCH
        // ============================
        vector<int> dane = wczytajZPliku();
        cout << "Wczytano " << dane.size() << " elementow z pliku.\n";

        // ============================
        // TWORZENIE STRUKTURY
        // ============================

        TablicaDynamiczna tablica;
        ListaJednokierunkowa jednokierunkowa;
        ListaDwukierunkowa dwukierunkowa;

        // wypełnianie odpowiedniej struktury
        if (selected == Dynamiczna) {
            for (int x : dane) tablica.dodajNaKoniec(x);
        }
        else if (selected == Jednokierunkowa) {
            for (int x : dane) jednokierunkowa.dodajNaKoniec(x);
        }
        else if (selected == Dwukierunkowa) {
            for (int x : dane) dwukierunkowa.dodajNaKoniec(x);
        }

        while (true) {

            int op = showOperationsMenu();
            if (op == 9) break;

            int value, pos;

            auto start = std::chrono::high_resolution_clock::now();
            auto end = start;

            string opis = "Operacja na strukturze " + to_string(selected) + " (" + to_string(dane.size()) + " elementow): ";

            switch (op) {

                case 1: // dodaj na początek
                    cout << "Podaj wartosc: ";
                    cin >> value;
                    opis += "Dodano na poczatek";

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.dodajNaPoczatek(value);
                    else if (selected == Jednokierunkowa) jednokierunkowa.dodajNaPoczatek(value);
                    else dwukierunkowa.dodajNaPoczatek(value);
                    end = std::chrono::high_resolution_clock::now();
                    break;

                case 2: // dodaj na koniec
                    cout << "Podaj wartosc: ";
                    cin >> value;
                    opis += "Dodano na koniec";

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.dodajNaKoniec(value);
                    else if (selected == Jednokierunkowa) jednokierunkowa.dodajNaKoniec(value);
                    else dwukierunkowa.dodajNaKoniec(value);
                    end = std::chrono::high_resolution_clock::now();
                    break;

                case 3: // dodaj na pozycję
                    cout << "Podaj wartosc: ";
                    cin >> value;
                    cout << "Podaj pozycje: ";
                    cin >> pos;
                    opis += "Dodano na pozycje " + to_string(pos);

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.dodajNaPozycji(value, pos);
                    else if (selected == Jednokierunkowa) jednokierunkowa.dodajNaPozycje(value, pos);
                    else dwukierunkowa.dodajNaPozycje(value, pos);
                    end = std::chrono::high_resolution_clock::now();
                    break;

                case 4: // usuń z początku
                    opis += "Usunieto z poczatku";

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.usunZPoczatku();
                    else if (selected == Jednokierunkowa) jednokierunkowa.usunZPoczatku();
                    else dwukierunkowa.usunZPoczatku();
                    end = std::chrono::high_resolution_clock::now();
                    break;

                case 5: // usuń z końca
                    opis += "Usunieto z konca";

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.usunZKonca();
                    else if (selected == Jednokierunkowa) jednokierunkowa.usunZKonca();
                    else dwukierunkowa.usunZKonca();
                    end = std::chrono::high_resolution_clock::now();
                    break;

                case 6: // usuń z pozycji
                    cout << "Podaj pozycje: ";
                    cin >> pos;
                    opis += "Usunieto z pozycji " + to_string(pos);

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.usunZPozycji(pos);
                    else if (selected == Jednokierunkowa) jednokierunkowa.usunZPozycji(pos);
                    else dwukierunkowa.usunZPozycji(pos);
                    end = std::chrono::high_resolution_clock::now();
                    break;

                case 7: // wyszukaj
                    cout << "Podaj wartosc: ";
                    cin >> value;
                    opis += "Wyszukano wartosc";

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.szukaj(value);
                    else if (selected == Jednokierunkowa) jednokierunkowa.szukaj(value);
                    else dwukierunkowa.szukaj(value);
                    end = std::chrono::high_resolution_clock::now();
                    break;

                case 8: // wyświetl
                    opis += "Wyswietlono listę";

                    start = std::chrono::high_resolution_clock::now();
                    if (selected == Dynamiczna) tablica.wyswietl();
                    else if (selected == Jednokierunkowa) jednokierunkowa.wyswietl();
                    else dwukierunkowa.wyswietl();
                    end = std::chrono::high_resolution_clock::now();
                    break;

                default:
                    cout << "Nieprawidlowa opcja\n";
                    continue;
            }

            auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            double ms = ns / 1'000'000.0;

            cout << "\n=== RESULT ===\n";
            cout << opis << "\n";
            cout << "Execution time: " << ns << " ns (" << ms << " ms)\n";
            cout << "==================\n"<<endl;
            cout.flush();

            logujWynik(opis, ns);
        }
    }

    return 0;
}
