#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include "tablicaDynamiczna.hpp"
#include "listaJednokierunkowa.hpp"
#include "listaDwukierunkowa.hpp"
#include "testStructuresSr.hpp"
#include "pomocnicze.hpp"

using namespace std;

void testStructuresSr(int powtórzenia) {
    vector<int> rozmiary = {50000, 80000, 100000, 160000, 200000, 400000, 600000, 1000000};
    WynikiStruktur wyniki;
    
    cout << "\n===== ROZPOCZYNANIE TESTOW WYDAJNOSCI =====\n\n";

    // Clear wyniki.txt at start
    ofstream clear_log("wyniki.txt");
    clear_log.close();

    ofstream outDyn("wyniki_TablicaDynamicznaSR.csv");
    ofstream outJedn("wyniki_ListaJednokierunkowaSR.csv");
    ofstream outDwuk("wyniki_ListaDwukierunkowaSR.csv");

    if (!outDyn.is_open() || !outJedn.is_open() || !outDwuk.is_open()) {
        cerr << "Nie mozna otworzyc plikow CSV do zapisu\n";
        return;
    }

    outDyn << "Struktura,Rozmiar,Operacja,Czas_ns,Czas_ms\n";
    outJedn << "Struktura,Rozmiar,Operacja,Czas_ns,Czas_ms\n";
    outDwuk << "Struktura,Rozmiar,Operacja,Czas_ns,Czas_ms\n";
    
for (int rozmiar : rozmiary) {
    wyniki.reset();
    for (int rep = 1; rep <= powtórzenia; rep++) {

        cout << "Powtorzenie " << rep << "/" << powtórzenia
             << " dla rozmiaru " << rozmiar << endl;

        // 🔥 GENERUJEMY DANE TYLKO RAZ NA POWTÓRZENIE
        vector<int> dane = generujDane(rozmiar);

        // ============================================
        // ============ TABLICA DYNAMICZNA ============
        // ============================================

        {
            TablicaDynamiczna t;
            for (int x : dane) t.dodajNaKoniec(x);

            auto test = [&](auto func) {
                auto s = chrono::high_resolution_clock::now();
                func();
                auto e = chrono::high_resolution_clock::now();
                return chrono::duration_cast<chrono::nanoseconds>(e - s).count();
            };

            wyniki.tablica.dodP += test([&]() { t.dodajNaPoczatek(999); });
            wyniki.tablica.dodK += test([&]() { t.dodajNaKoniec(888); });
            wyniki.tablica.dodPos += test([&]() { t.dodajNaPozycji(777, rozmiar/2); });
            wyniki.tablica.dodLos += test([&]() { t.dodajNaLosoweMiejsce(666); });

            wyniki.tablica.usP += test([&]() { t.usunZPoczatku(); });
            wyniki.tablica.usK += test([&]() { t.usunZKonca(); });
            wyniki.tablica.usPos += test([&]() { t.usunZPozycji(rozmiar/2); });
            wyniki.tablica.usLos += test([&]() { t.usunZLosowegoMiejsca(); });

            wyniki.tablica.szuk0 += test([&]() { t.szukaj(dane[0]); });
            wyniki.tablica.szuk25 += test([&]() { t.szukaj(dane[rozmiar/4]); });
            wyniki.tablica.szuk50 += test([&]() { t.szukaj(dane[rozmiar/2]); });
            wyniki.tablica.szuk75 += test([&]() { t.szukaj(dane[3*rozmiar/4]); });
            wyniki.tablica.szuk100 += test([&]() { t.szukaj(dane[rozmiar-1]); });
        }

        // ============================================
        // ========== LISTA JEDNOKIERUNKOWA ============
        // ============================================

        {
            ListaJednokierunkowa l;
            for (int x : dane) l.dodajNaKoniec(x);

            auto test = [&](auto func) {
                auto s = chrono::high_resolution_clock::now();
                func();
                auto e = chrono::high_resolution_clock::now();
                return chrono::duration_cast<chrono::nanoseconds>(e - s).count();
            };

            wyniki.jednokierunkowa.dodP += test([&]() { l.dodajNaPoczatek(999); });
            wyniki.jednokierunkowa.dodK += test([&]() { l.dodajNaKoniec(888); });
            wyniki.jednokierunkowa.dodPos += test([&]() { l.dodajNaPozycje(777, rozmiar/2); });
            wyniki.jednokierunkowa.dodLos += test([&]() { l.dodajNaLosoweMiejsce(666); });

            wyniki.jednokierunkowa.usP += test([&]() { l.usunZPoczatku(); });
            wyniki.jednokierunkowa.usK += test([&]() { l.usunZKonca(); });
            wyniki.jednokierunkowa.usPos += test([&]() { l.usunZPozycji(rozmiar/2); });
            wyniki.jednokierunkowa.usLos += test([&]() { l.usunZLosowegoMiejsca(); });

            wyniki.jednokierunkowa.szuk0 += test([&]() { l.szukaj(dane[0]); });
            wyniki.jednokierunkowa.szuk25 += test([&]() { l.szukaj(dane[rozmiar/4]); });
            wyniki.jednokierunkowa.szuk50 += test([&]() { l.szukaj(dane[rozmiar/2]); });
            wyniki.jednokierunkowa.szuk75 += test([&]() { l.szukaj(dane[3*rozmiar/4]); });
            wyniki.jednokierunkowa.szuk100 += test([&]() { l.szukaj(dane[rozmiar-1]); });
        }

        // ============================================
        // ========== LISTA DWUKIERUNKOWA ==============
        // ============================================

        {
            ListaDwukierunkowa l;
            for (int x : dane) l.dodajNaKoniec(x);

            auto test = [&](auto func) {
                auto s = chrono::high_resolution_clock::now();
                func();
                auto e = chrono::high_resolution_clock::now();
                return chrono::duration_cast<chrono::nanoseconds>(e - s).count();
            };

            wyniki.dwukierunkowa.dodP += test([&]() { l.dodajNaPoczatek(999); });
            wyniki.dwukierunkowa.dodK += test([&]() { l.dodajNaKoniec(888); });
            wyniki.dwukierunkowa.dodPos += test([&]() { l.dodajNaPozycje(777, rozmiar/2); });
            wyniki.dwukierunkowa.dodLos += test([&]() { l.dodajNaLosoweMiejsce(666); });

            wyniki.dwukierunkowa.usP += test([&]() { l.usunZPoczatku(); });
            wyniki.dwukierunkowa.usK += test([&]() { l.usunZKonca(); });
            wyniki.dwukierunkowa.usPos += test([&]() { l.usunZPozycji(rozmiar/2); });
            wyniki.dwukierunkowa.usLos += test([&]() { l.usunZLosowegoMiejsca(); });

            wyniki.dwukierunkowa.szuk0 += test([&]() { l.szukaj(dane[0]); });
            wyniki.dwukierunkowa.szuk25 += test([&]() { l.szukaj(dane[rozmiar/4]); });
            wyniki.dwukierunkowa.szuk50 += test([&]() { l.szukaj(dane[rozmiar/2]); });
            wyniki.dwukierunkowa.szuk75 += test([&]() { l.szukaj(dane[3*rozmiar/4]); });
            wyniki.dwukierunkowa.szuk100 += test([&]() { l.szukaj(dane[rozmiar-1]); });
        }
    }

    // ============================================================
    // ===================== LICZENIE ŚREDNICH =====================
    // ============================================================

    auto AVG = [&](long long suma) { return suma / powtórzenia; };

    // TABLICA
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "DodajPoczatek", AVG(wyniki.tablica.dodP));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "DodajKoniec", AVG(wyniki.tablica.dodK));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "DodajPozycja", AVG(wyniki.tablica.dodPos));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "DodajLosowe", AVG(wyniki.tablica.dodLos));

    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "UsunPoczatek", AVG(wyniki.tablica.usP));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "UsunKoniec", AVG(wyniki.tablica.usK));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "UsunPozycja", AVG(wyniki.tablica.usPos));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "UsunLosowe", AVG(wyniki.tablica.usLos));

    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "Szukaj0", AVG(wyniki.tablica.szuk0));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "Szukaj25", AVG(wyniki.tablica.szuk25));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "Szukaj50", AVG(wyniki.tablica.szuk50));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "Szukaj75", AVG(wyniki.tablica.szuk75));
    zapiszCsv(outDyn, "TablicaDynamiczna", rozmiar, "Szukaj100", AVG(wyniki.tablica.szuk100));

    // LISTA JEDNOKIERUNKOWA
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "DodajPoczatek", AVG(wyniki.jednokierunkowa.dodP));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "DodajKoniec", AVG(wyniki.jednokierunkowa.dodK));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "DodajPozycja", AVG(wyniki.jednokierunkowa.dodPos));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "DodajLosowe", AVG(wyniki.jednokierunkowa.dodLos));

    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "UsunPoczatek", AVG(wyniki.jednokierunkowa.usP));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "UsunKoniec", AVG(wyniki.jednokierunkowa.usK));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "UsunPozycja", AVG(wyniki.jednokierunkowa.usPos));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "UsunLosowe", AVG(wyniki.jednokierunkowa.usLos));

    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "Szukaj0", AVG(wyniki.jednokierunkowa.szuk0));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "Szukaj25", AVG(wyniki.jednokierunkowa.szuk25));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "Szukaj50", AVG(wyniki.jednokierunkowa.szuk50));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "Szukaj75", AVG(wyniki.jednokierunkowa.szuk75));
    zapiszCsv(outJedn, "ListaJednokierunkowa", rozmiar, "Szukaj100", AVG(wyniki.jednokierunkowa.szuk100));

    // LISTA DWUKIERUNKOWA
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "DodajPoczatek", AVG(wyniki.dwukierunkowa.dodP));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "DodajKoniec", AVG(wyniki.dwukierunkowa.dodK));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "DodajPozycja", AVG(wyniki.dwukierunkowa.dodPos));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "DodajLosowe", AVG(wyniki.dwukierunkowa.dodLos));

    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "UsunPoczatek", AVG(wyniki.dwukierunkowa.usP));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "UsunKoniec", AVG(wyniki.dwukierunkowa.usK));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "UsunPozycja", AVG(wyniki.dwukierunkowa.usPos));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "UsunLosowe", AVG(wyniki.dwukierunkowa.usLos));

    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "Szukaj0", AVG(wyniki.dwukierunkowa.szuk0));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "Szukaj25", AVG(wyniki.dwukierunkowa.szuk25));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "Szukaj50", AVG(wyniki.dwukierunkowa.szuk50));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "Szukaj75", AVG(wyniki.dwukierunkowa.szuk75));
    zapiszCsv(outDwuk, "ListaDwukierunkowa", rozmiar, "Szukaj100", AVG(wyniki.dwukierunkowa.szuk100));
}
}