#include "DrzewoAVL.hpp"
//Konstruktory/ destruktory
DrzewoAVL::DrzewoAVL() {
    korzen = nullptr;
    licznik = 0;
}

DrzewoAVL::~DrzewoAVL() {
    wyczysc(korzen);
}

DrzewoAVL::DrzewoAVL(const DrzewoAVL& other) {
    korzen = kopiuj(other.korzen);
    licznik = other.licznik;
}

DrzewoAVL& DrzewoAVL::operator=(const DrzewoAVL& other) {
    if (this == &other) return *this; // samoprzydzielenie
    wyczysc(korzen); // zwolnij stare zasoby
    licznik = other.licznik;
    korzen = kopiuj(other.korzen); // skopiuj nowe
    return *this;
}

// Publiczne metody

int DrzewoAVL::wysokosc(ElementAVL* e) const {
    if(e == nullptr) return 0;
    return e->wysokosc;
}

int DrzewoAVL::wspolczynnikRownowagi(ElementAVL* e) const {
    if(e == nullptr) return 0;
    return wysokosc(e->lewy) - wysokosc(e->prawy);
}

void DrzewoAVL::aktualizujWysokosc(ElementAVL* e) {
    int wysokoscLewy = wysokosc(e->lewy);
    int wysokoscPrawy = wysokosc(e->prawy);
    if (wysokoscLewy > wysokoscPrawy) {
        e->wysokosc = wysokoscLewy + 1;
    } 
    else {
        e-> wysokosc = wysokoscPrawy + 1;
    }
}
//Rotacje
ElementAVL* DrzewoAVL::rotacjaLewo(ElementAVL* x){
    ElementAVL* y = x->prawy;
    ElementAVL* T2 = y->lewy;
    y->lewy = x;
    x->prawy = T2;
    aktualizujWysokosc(x);
    aktualizujWysokosc(y);
    return y;
}

ElementAVL* DrzewoAVL::rotacjaPrawo(ElementAVL* y){
    ElementAVL* x = y->lewy;
    ElementAVL* T2 = x->prawy;
    x->prawy = y;
    y->lewy = T2;
    aktualizujWysokosc(y);
    aktualizujWysokosc(x);
    return x;
}

ElementAVL* DrzewoAVL::zrownowaz(ElementAVL* e) {
    aktualizujWysokosc(e);
    int balance = wspolczynnikRownowagi(e);

    //Lewo-lewo
    if (balance > 1 && wspolczynnikRownowagi(e->lewy) >= 0)
        return rotacjaPrawo(e);

    //Lewo-prawo
    if(balance > 1 && wspolczynnikRownowagi(e->lewy) < 0) {
        e->lewy = rotacjaLewo(e->lewy);
        return rotacjaPrawo(e);
    }
    //Prawo-prawo
    if(balance < -1 && wspolczynnikRownowagi(e->prawy) <= 0)
        return rotacjaLewo(e);
    //Prawo-lewo
    if(balance < -1 && wspolczynnikRownowagi(e->prawy) > 0) {
        e->prawy = rotacjaPrawo(e->prawy);
        return rotacjaLewo(e);
    }
    return e; // Nie wymaga zrównoważenia
}

//Minimum w poddrzewie (pomoc w usuwaniu)

ElementAVL* DrzewoAVL::minimum(ElementAVL* e) const {
    while(e->lewy != nullptr) {
        e = e->lewy;
    }
    return e;
}

//Rekurecyjne metody insert, remove, find
ElementAVL* DrzewoAVL::insert(ElementAVL* e, int klucz, int wartosc, bool& wstawiono) {
    if(e == nullptr) {
        ElementAVL* nowy = new ElementAVL;
        nowy->klucz = klucz;
        nowy->wartosc = wartosc;
        nowy->lewy = nullptr;
        nowy->prawy = nullptr;
        nowy->wysokosc = 1;
        wstawiono = true;
        return nowy;
    }
    if(klucz < e->klucz) {
        e->lewy = insert(e->lewy, klucz, wartosc, wstawiono);
    }
    else if(klucz > e->klucz) {
        e->prawy = insert(e->prawy, klucz, wartosc, wstawiono);
    }
    else {
        e->wartosc = wartosc; // Aktualizacja wartości dla istniejącego klucza
        wstawiono = false; // Nie wstawiono nowego ElementAVLu
        return e;
    }
    return zrownowaz(e);
}

ElementAVL* DrzewoAVL::remove(ElementAVL* e, int klucz, bool& usunieto) {
    if(e == nullptr) {
        usunieto = false;
        return nullptr;
    }
    if(klucz < e->klucz) {
        e->lewy = remove(e->lewy, klucz, usunieto);
    }
    else if(klucz > e->klucz) {
        e->prawy = remove(e->prawy, klucz, usunieto);
    }
    else {
        usunieto = true;
        
        if(e->lewy == nullptr) {
            ElementAVL* dziecko = e->prawy;
            delete e;
            return dziecko;
        }
        if (e->prawy == nullptr) {
            ElementAVL* dziecko = e->lewy;
            delete e;
            return dziecko;
        }

        ElementAVL* nastepny = minimum(e->prawy);
        e->klucz = nastepny->klucz;
        e->wartosc = nastepny->wartosc;

        bool pomocniczy = false;
        e->prawy = remove(e->prawy, nastepny->klucz, pomocniczy);
    }
    return zrownowaz(e);
}

ElementAVL* DrzewoAVL::find(ElementAVL* e, int klucz) const {
    while (e != nullptr) {
        if(klucz < e->klucz) {
            e = e->lewy;
        } else if (klucz > e->klucz) {
            e = e->prawy;
        } else {
            return e; // znaleziono
        }
    }
    return nullptr;
}

//Zarzadzanie pamięcią

void DrzewoAVL::wyczysc(ElementAVL* e) {
    if(e == nullptr) return;
    wyczysc(e->lewy);
    wyczysc(e->prawy);
    delete e;
}

ElementAVL* DrzewoAVL::kopiuj(ElementAVL* e) {
    if(e == nullptr) return nullptr;
    ElementAVL* nowy = new ElementAVL;
    nowy->klucz = e->klucz;
    nowy->wartosc = e->wartosc;
    nowy->wysokosc = e->wysokosc;
    nowy->lewy = kopiuj(e->lewy);
    nowy->prawy = kopiuj(e->prawy);
    return nowy;
}

//Api publiczne

void DrzewoAVL::insert(int klucz, int wartosc) {
    bool wstawiono = false;
    korzen = insert(korzen, klucz, wartosc, wstawiono);
    if(wstawiono) licznik++;
}

void DrzewoAVL::remove(int klucz) {
    if(licznik == 0) return; // puste drzewo
    bool usunieto = false;
    korzen = remove(korzen, klucz, usunieto);
    if(usunieto) licznik--;
}

int DrzewoAVL::rozmiar() const {
    return licznik;
}

bool DrzewoAVL::pusty() const {
    return korzen == nullptr;
}