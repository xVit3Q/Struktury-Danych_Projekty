#include "TablicaOtwarta.hpp"
#include <cmath>

TablicaOtwarta::TablicaOtwarta(){
    licznik = 0;
    rozmiar = 1;
    dane = new Element[rozmiar];
}
TablicaOtwarta::~TablicaOtwarta(){
    delete[] dane;
}

TablicaOtwarta::TablicaOtwarta(const TablicaOtwarta& other){
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    dane = new Element[rozmiar];
    for(int i=0; i<rozmiar;i++){
        dane[i]=other.dane[i];
    }
}

TablicaOtwarta& TablicaOtwarta::operator=(const TablicaOtwarta& other){
    if(this == &other)return *this;
    Element* noweDane = new Element[other.rozmiar];
    for(int i=0;i<other.licznik;i++){
        noweDane[i] = other.dane[i];
    }
    delete[] dane;
    dane = noweDane;
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    return *this;
}

void TablicaOtwarta::zwiekszRozmiar(){
    if(licznik >= rozmiar){
        rozmiar *= 2;
        Element* noweDane = new Element[rozmiar];
        for(int i=0;i<licznik;i++){
            noweDane[i] = dane[i];
        }
        delete[] dane;
        dane = noweDane;
    }
}

void TablicaOtwarta::zmniejszRozmiar(){
    int staryRozmiar = rozmiar;
    while(licznik >= 0 && licznik <= rozmiar/4 && rozmiar >1){
        rozmiar /= 2;
    }
    if(rozmiar != staryRozmiar){
        Element* noweDane = new Element[rozmiar];
        for(int i=0;i<licznik;i++){
            noweDane[i] = dane[i];
        }
    delete[] dane;
    dane = noweDane;
    }
}

int TablicaOtwarta::funkcjaMieszajaca(int klucz) const{
    return (std::abs(klucz)%rozmiar);
}

void TablicaOtwarta::insert(int klucz, int wartosc){
    zwiekszRozmiar();
    int indeks = funkcjaMieszajaca(klucz);
    int startowyIndeks = indeks;
    while(dane[indeks].status == ZAJETA){
        if(dane[indeks].klucz == klucz){
            dane[indeks].wartosc = wartosc;
            return;
        }
        indeks = (indeks+1)%rozmiar;
        if(indeks == startowyIndeks){
            return;
        }
    }
    dane[indeks].klucz = klucz;
    dane[indeks].wartosc = wartosc;
    dane[indeks].status = ZAJETA;
    licznik++;
}

void TablicaOtwarta::remove(int klucz){
    if(licznik == 0){
        return;
    }
    int indeks = funkcjaMieszajaca(klucz);
    int startowyIndeks = indeks;
    while(dane[indeks].status == ZAJETA){
        if(dane[indeks].klucz == klucz){
            dane[indeks].status = WOLNA;
            licznik--;
            zmniejszRozmiar();
            return;
        }
        indeks = (indeks+1)%rozmiar;
        if(indeks == startowyIndeks){
            break;
        }
    }
    return;
}