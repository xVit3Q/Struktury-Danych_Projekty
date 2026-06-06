#include "TablicaOtwarta.hpp"

TablicaOtwarta::TablicaOtwarta(){
    licznik = 0;
    rozmiar = 1;
    dane = new ElementOtwarta[rozmiar];
}
TablicaOtwarta::~TablicaOtwarta(){
    delete[] dane;
}

TablicaOtwarta::TablicaOtwarta(const TablicaOtwarta& other){
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    dane = new ElementOtwarta[rozmiar];
    for(int i=0; i<rozmiar;i++){
        dane[i]=other.dane[i];
    }
}

TablicaOtwarta& TablicaOtwarta::operator=(const TablicaOtwarta& other){
    if(this == &other)return *this;
    ElementOtwarta* noweDane = new ElementOtwarta[other.rozmiar];
    for(int i=0;i<other.rozmiar;i++){
        noweDane[i] = other.dane[i];
    }
    delete[] dane;
    dane = noweDane;
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    return *this;
}

void TablicaOtwarta::zwiekszRozmiar(){
    if(licznik >= rozmiar * 0.7){ 
        int nowyRozmiar = rozmiar * 2;
        ElementOtwarta* noweDane = new ElementOtwarta[nowyRozmiar];
        int staryRozmiar = rozmiar;
        rozmiar = nowyRozmiar;
 
        for(int i = 0; i < staryRozmiar; i++){
            if(dane[i].status == ZAJETA){
                int indeks = funkcjaMieszajaca(dane[i].klucz);
                while(noweDane[indeks].status == ZAJETA){
                    indeks = (indeks + 1) % rozmiar;
                }
                noweDane[indeks] = dane[i];
            }
        }
        delete[] dane;
        dane = noweDane;
    }
}
 
void TablicaOtwarta::zmniejszRozmiar(){
    int staryRozmiar = rozmiar;
    while(licznik <= rozmiar / 4 && rozmiar > 1){
        rozmiar /= 2;
    }
    if(rozmiar != staryRozmiar){
        ElementOtwarta* noweDane = new ElementOtwarta[rozmiar];
 
        // POPRAWKA: rehash zamiast kopiowania bajtów
        for(int i = 0; i < staryRozmiar; i++){
            if(dane[i].status == ZAJETA){
                int indeks = funkcjaMieszajaca(dane[i].klucz);
                while(noweDane[indeks].status == ZAJETA){
                    indeks = (indeks + 1) % rozmiar;
                }
                noweDane[indeks] = dane[i];
            }
        }
        delete[] dane;
        dane = noweDane;
    }
}

int TablicaOtwarta::funkcjaMieszajaca(int klucz) const {
    unsigned int u_klucz = static_cast<unsigned int>(klucz);
    return static_cast<int>(u_klucz % rozmiar);
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
        indeks = (indeks + 1) % rozmiar;
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
            int kolejny = (indeks + 1) % rozmiar;
            while(dane[kolejny].status == ZAJETA){
                ElementOtwarta doWstawienia = dane[kolejny];
                dane[kolejny].status = WOLNA;
                licznik--;
                int nowyIndeks = funkcjaMieszajaca(doWstawienia.klucz);
                while(dane[nowyIndeks].status == ZAJETA){
                    nowyIndeks = (nowyIndeks + 1) % rozmiar;
                }
                dane[nowyIndeks] = doWstawienia;
                licznik++;
 
                kolejny = (kolejny + 1) % rozmiar;
            }
            zmniejszRozmiar();
            return;
        }
        indeks = (indeks + 1) % rozmiar;
        if(indeks == startowyIndeks){
            break;
        }
    }
}
int TablicaOtwarta::returnSize() const{
    return licznik;
}