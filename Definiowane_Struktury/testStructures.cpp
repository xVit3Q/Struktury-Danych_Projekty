#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "tablicaDynamiczna.hpp"
#include "listaJednokierunkowa.hpp"
#include "listaDwukierunkowa.hpp"
#include "testStructures.hpp"
#include "pomocnicze.hpp"

using namespace std;

void testStructures() {
    vector<int> rozmiary = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000};
    
    cout << "\n===== ROZPOCZYNANIE TESTOW WYDAJNOSCI =====\n\n";
    
    // Clear wyniki.txt at start
    ofstream clear_log("wyniki.txt");
    clear_log.close();
    
    for (int rozmiar : rozmiary) {
        cout << "Testowanie na " << rozmiar << " elementach...\n";
        
        vector<int> dane = generujDane(rozmiar);
        int testValue = dane[rozmiar / 2];
        
        // ===== TABLICA DYNAMICZNA =====
        {
            TablicaDynamiczna tablica;
            for (int x : dane) tablica.dodajNaKoniec(x);
            
            auto start = std::chrono::high_resolution_clock::now();
            tablica.dodajNaPoczatek(999);
            auto end = std::chrono::high_resolution_clock::now();
            auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("TablicaDynamiczna [" + to_string(rozmiar) + "] - Dodaj na poczatek", ns);
            cout << "  TablicaDynamiczna Dodaj na poczatek: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            tablica.dodajNaKoniec(888);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("TablicaDynamiczna [" + to_string(rozmiar) + "] - Dodaj na koniec", ns);
            cout << "  TablicaDynamiczna Dodaj na koniec: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            tablica.dodajNaPozycji(777, rozmiar / 2);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("TablicaDynamiczna [" + to_string(rozmiar) + "] - Dodaj na pozycje", ns);
            cout << "  TablicaDynamiczna Dodaj na pozycje: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            tablica.usunZPoczatku();
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("TablicaDynamiczna [" + to_string(rozmiar) + "] - Usun z poczatku", ns);
            cout << "  TablicaDynamiczna Usun z poczatku: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            tablica.usunZKonca();
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("TablicaDynamiczna [" + to_string(rozmiar) + "] - Usun z konca", ns);
            cout << "  TablicaDynamiczna Usun z konca: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            tablica.usunZPozycji(rozmiar / 2);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("TablicaDynamiczna [" + to_string(rozmiar) + "] - Usun z pozycji", ns);
            cout << "  TablicaDynamiczna Usun z pozycji: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            tablica.szukaj(testValue);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("TablicaDynamiczna [" + to_string(rozmiar) + "] - Szukaj", ns);
            cout << "  TablicaDynamiczna Szukaj: " << ns << " ns\n";
        }
        
        // ===== LISTA JEDNOKIERUNKOWA =====
        {
            ListaJednokierunkowa lista;
            for (int x : dane) lista.dodajNaKoniec(x);
            
            auto start = std::chrono::high_resolution_clock::now();
            lista.dodajNaPoczatek(999);
            auto end = std::chrono::high_resolution_clock::now();
            auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaJednokierunkowa [" + to_string(rozmiar) + "] - Dodaj na poczatek", ns);
            cout << "  ListaJednokierunkowa Dodaj na poczatek: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.dodajNaKoniec(888);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaJednokierunkowa [" + to_string(rozmiar) + "] - Dodaj na koniec", ns);
            cout << "  ListaJednokierunkowa Dodaj na koniec: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.dodajNaPozycje(777, rozmiar / 2);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaJednokierunkowa [" + to_string(rozmiar) + "] - Dodaj na pozycje", ns);
            cout << "  ListaJednokierunkowa Dodaj na pozycje: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.usunZPoczatku();
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaJednokierunkowa [" + to_string(rozmiar) + "] - Usun z poczatku", ns);
            cout << "  ListaJednokierunkowa Usun z poczatku: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.usunZKonca();
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaJednokierunkowa [" + to_string(rozmiar) + "] - Usun z konca", ns);
            cout << "  ListaJednokierunkowa Usun z konca: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.usunZPozycji(rozmiar / 2);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaJednokierunkowa [" + to_string(rozmiar) + "] - Usun z pozycji", ns);
            cout << "  ListaJednokierunkowa Usun z pozycji: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.szukaj(testValue);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaJednokierunkowa [" + to_string(rozmiar) + "] - Szukaj", ns);
            cout << "  ListaJednokierunkowa Szukaj: " << ns << " ns\n";
        }
        
        // ===== LISTA DWUKIERUNKOWA =====
        {
            ListaDwukierunkowa lista;
            for (int x : dane) lista.dodajNaKoniec(x);
            
            auto start = std::chrono::high_resolution_clock::now();
            lista.dodajNaPoczatek(999);
            auto end = std::chrono::high_resolution_clock::now();
            auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaDwukierunkowa [" + to_string(rozmiar) + "] - Dodaj na poczatek", ns);
            cout << "  ListaDwukierunkowa Dodaj na poczatek: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.dodajNaKoniec(888);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaDwukierunkowa [" + to_string(rozmiar) + "] - Dodaj na koniec", ns);
            cout << "  ListaDwukierunkowa Dodaj na koniec: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.dodajNaPozycje(777, rozmiar / 2);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaDwukierunkowa [" + to_string(rozmiar) + "] - Dodaj na pozycje", ns);
            cout << "  ListaDwukierunkowa Dodaj na pozycje: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.usunZPoczatku();
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaDwukierunkowa [" + to_string(rozmiar) + "] - Usun z poczatku", ns);
            cout << "  ListaDwukierunkowa Usun z poczatku: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.usunZKonca();
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaDwukierunkowa [" + to_string(rozmiar) + "] - Usun z konca", ns);
            cout << "  ListaDwukierunkowa Usun z konca: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.usunZPozycji(rozmiar / 2);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaDwukierunkowa [" + to_string(rozmiar) + "] - Usun z pozycji", ns);
            cout << "  ListaDwukierunkowa Usun z pozycji: " << ns << " ns\n";
            
            start = std::chrono::high_resolution_clock::now();
            lista.szukaj(testValue);
            end = std::chrono::high_resolution_clock::now();
            ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            logujWynik("ListaDwukierunkowa [" + to_string(rozmiar) + "] - Szukaj", ns);
            cout << "  ListaDwukierunkowa Szukaj: " << ns << " ns\n";
        }
        
        cout << "\n";
    }
    
    cout << "===== TESTY ZAKONCZONE =====\n";
    cout << "Wyniki zapisane do wyniki.txt\n\n";
}
