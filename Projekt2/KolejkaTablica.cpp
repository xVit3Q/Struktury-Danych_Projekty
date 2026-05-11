#include "kolejkaTablica.hpp"
#include <iostream>

KolejkaTablica::KolejkaTablica(){
    licznik=0;
    rozmiar=1;
    licznikKolejki=0;
    dane = new Element[rozmiar];
}

KolejkaTablica::~KolejkaTablica(){
    delete[] dane;
}

KolejkaTablica::KolejkaTablica(const KolejkaTablica& other) {
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    dane = new Element[rozmiar]; // alokacja nowej tablicy
    for (int i = 0; i < licznik; i++) {
        dane[i] = other.dane[i]; // kopiowanie danych
    }
}
KolejkaTablica& KolejkaTablica::operator=(const KolejkaTablica& other) {
    if (this == &other)  // sprawdzenie samoprzydzielenia
        return *this; // zwrócenie obiektu bez zmian

    delete[] dane; // zwolnienie starej tablicy

    licznik = other.licznik;
    rozmiar = other.rozmiar;
    dane = new Element[rozmiar]; // alokacja nowej tablicy
    for (int i = 0; i < licznik; i++) {
        dane[i] = other.dane[i]; // kopiowanie danych
    }
    return *this;
}

void KolejkaTablica::zwiekszRozmiar(){
    if(licznik >= rozmiar) {
        rozmiar *= 2;//zwiekszenie rozmiaru o połowę
        Element* noweDane = new Element[rozmiar];//nowa tablica
        for(int i=0; i<licznik; i++){
            noweDane[i] = dane[i];//przerzucenie danych do nowej tablicy
        }
        delete[] dane;//usuniecie starej tablicy
        dane = noweDane;//podpiecie nowego wskaznika
    } 
}
void KolejkaTablica::zmniejszRozmiar(){
    int staryRozmiar = rozmiar;
    while(licznik > 0 && licznik <= rozmiar / 4 && rozmiar > 1){
        rozmiar /= 2;//zmniejszenie rozmiaru o połowę
        }
        //realok
        if(rozmiar != staryRozmiar){ //realok tylko jesli rozmiar sie zmienil
        Element* noweDane = new Element[rozmiar];//nowa tablica
        for(int i=0; i<licznik; i++){
            noweDane[i] = dane[i];//przerzucenie danych do nowej tablicy
        }
        delete[] dane;//usuniecie starej tablicy
        dane = noweDane;//podpiecie nowego wskaznika
    }
}

int KolejkaTablica::znajdzIndeksMax() const{
    if(licznik==0){
        return -1;
        //nie ma nic w tablicy
    }
    int maxIndeks=0;
    for(int i=1;i<licznik;i++){
        if(dane[i].priorytet > dane[maxIndeks].priorytet){
            maxIndeks=i;
        }else if(dane[i].priorytet==dane[maxIndeks].priorytet){
            if(dane[i].kolejnosc < dane[maxIndeks].kolejnosc){
                maxIndeks=i;
            }
        }
    }
    return maxIndeks;
}

void KolejkaTablica::insert(int e, int p){
    dane[licznik]=Element(e, p, licznikKolejki);
    licznikKolejki++;
    licznik++;
}

int KolejkaTablica::extract_max(){
    int maxIndeks = znajdzIndeksMax();
    int maxWartosc = dane[maxIndeks].wartosc;

    for(int i=maxIndeks;i<licznik;i++){
        dane[i]=dane[i+1];
    }
    licznik--;
    zmniejszRozmiar();
    return maxWartosc;
}

int KolejkaTablica::find_max() const{
    return dane[znajdzIndeksMax()].wartosc;
}

void KolejkaTablica::modify_key(int e, int p){
    for(int i=0;i<licznik;i++){
        if(dane[i].wartosc==e){
            dane[i].priorytet=p;
            return;
        }
    }
}
// Zwiększa priorytet elementu o wartości e na p
// Działa tylko jeśli nowy priorytet jest większy od obecnego
void KolejkaTablica::increase_key(int e, int p){
    for(int i=0;i<licznik;i++){
        if(dane[i].wartosc==e){
            if(p > dane[i].priorytet)   // zwiększamy tylko jeśli większy
                dane[i].priorytet=p;
            return;
        }
    }
}

// Zmniejsza priorytet elementu o wartości e na p
// Działa tylko jeśli nowy priorytet jest mniejszy od obecnego
void KolejkaTablica::decrease_key(int e, int p){
    for(int i=0;i<licznik;i++){
        if(dane[i].wartosc==e){
            if(p < dane[i].priorytet)   // zmniejszamy tylko jeśli mniejszy
                dane[i].priorytet=p;
            return;
        }
    }
}


int KolejkaTablica::return_size() const{
    return licznik;
}