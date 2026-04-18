#ifndef TABLICA_DYNAMICZNA_HPP
#define TABLICA_DYNAMICZNA_HPP

class TablicaDynamiczna{
private:
    int* dane;
    int licznik;
    int rozmiar;
    
    void zwiekszRozmiar();
    void zmniejszRozmiar();
public:
    TablicaDynamiczna();
    ~TablicaDynamiczna();
    void dodajNaPoczatek(int wartosc);
    void dodajNaKoniec(int wartosc);
    void dodajNaPozycji(int indeks, int wartosc);
    void dodajNaLosoweMiejsce(int wartosc);
    void usunZPoczatku();
    void usunZKonca();
    void usunZPozycji(int indeks);
    void usunZLosowegoMiejsca();
    int szukaj(int wartosc);
    void wyswietl();
};
#endif