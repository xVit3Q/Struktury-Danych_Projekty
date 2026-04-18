#include "tablicaDynamiczna.hpp"
#include <iostream>

TablicaDynamiczna::TablicaDynamiczna(){
    licznik = 0;
    rozmiar = 1;
    dane = new int[rozmiar];//nowa tablica o rozmiarze 1
}

TablicaDynamiczna::~TablicaDynamiczna(){
    delete[] dane;//zwolnienie pamieci
}

void TablicaDynamiczna::zwiekszRozmiar(){
    if(licznik==rozmiar){
        rozmiar*=2;//zwiekszenie rozmiaru dwukrotnie
        int* noweDane = new int[rozmiar];//tworzenie nowej tablicy

        for(int i=0;i<licznik;i++)
        {
            noweDane[i]=dane[i];//przerzucenie danych do nowej tablicy
        }
        delete[] dane;//usuniecie starej tablicy
        dane=noweDane;//podpiecie nowego wskaznika
    }
}

void TablicaDynamiczna::zmniejszRozmiar(){
    
    if(licznik > 0 && licznik <= rozmiar / 4){//jesli zapełnienie spadnie do 1/4 rozmiaru
        rozmiar /= 2; //zmniejszenie rozmiaru o połowę
        int* noweDane = new int[rozmiar]; //nowa tablica

        for(int i=0; i<licznik; i++){
            noweDane[i] = dane[i]; //przerzucenie danych do nowej tablicy
        }
        delete[] dane; //usuniecie starej tablicy
        dane = noweDane; //podpiecie nowego wskaznika
    }
}

//------DODAWANIE ELEMENTU-------
void TablicaDynamiczna::dodajNaPoczatek(int wartosc){
    zwiekszRozmiar();//sprawdzenie czy wymaga zwiększenia rozmiaru
    for(int i=licznik;i>0;i--){
        dane[i]=dane[i-1];//przerzucenie danych o jedno pole w prawo w tablicy
    }
    dane[0]=wartosc;//dodanie wartosci na pierwsze miejsce
    licznik++;
}

void TablicaDynamiczna::dodajNaKoniec(int wartosc){
    zwiekszRozmiar();//sprawdzenie czy wymaga zwiększenia rozmiaru
    dane[licznik]=wartosc;
    licznik++;
}

void TablicaDynamiczna::dodajNaPozycji(int indeks, int wartosc){
    if(indeks<0 || indeks>licznik){
        return;
    }
    zwiekszRozmiar();//sprawdzenie czy wymaga zwiększenia rozmiaru
    for(int i=licznik;i>indeks;i--){
        dane[i]=dane[i-1];//przerzucenie danych o jedno pole w prawo od podanego ideksu
    }
    dane[indeks]=wartosc;//wstawienie wartosci na dany indeks
    licznik++;
}
void TablicaDynamiczna::dodajNaLosoweMiejsce(int wartosc){
    int indeks = rand() % (licznik + 1);//losowy indeks od 0 do licznik
    dodajNaPozycji(indeks, wartosc);
}
//USUWANIE ELEMENTU
void TablicaDynamiczna::usunZPoczatku(){
    if (licznik == 0)
    {
        return;
    }
    for(int i=0;i<licznik-1;i++)
    {
        dane[i]=dane[i+1];//przesuwanie danych o jedno pole w lewo
    }
    licznik--;
    zmniejszRozmiar();//sprawdzenie czy mozna zwolnic nieuzywane miejsce
}

void TablicaDynamiczna::usunZKonca(){
    if(licznik>0){
        licznik--;
        zmniejszRozmiar();//sprawdzenie czy mozna zwolnic nieuzywane miejsce
    }
}

void TablicaDynamiczna::usunZPozycji(int indeks){
    if(indeks<0 || indeks>= licznik){
        return;
    }
    for(int i=indeks;i<licznik-1;i++)
    {
        dane[i]=dane[i+1];//przesuwanie danych w lewo od podanego indeksu
    }
    licznik--;
    zmniejszRozmiar();//sprawdzenie czy mozna zwolnic nieuzywane miejsce
}
void TablicaDynamiczna::usunZLosowegoMiejsca(){
    if(licznik==0){
        return;
    }
    int indeks = rand() % licznik;//losowy indeks od 0 do licznik - 1
    usunZPozycji(indeks);
}
int TablicaDynamiczna::szukaj(int wartosc){
    for(int i=0;i<licznik;i++){
        if(dane[i] == wartosc){
            return i;//zwrocenie indeksu jesli znaleziono
        }
    }
    return -1;//liczba nie istnieje w tablicy
}

void TablicaDynamiczna::wyswietl(){
    if(licznik==0){
        std::cout<< "tablica jest pusta"<<std::endl;
        return;
    }
    std::cout << "licznik: " << licznik << ", pojemnosc: " << rozmiar<<std::endl;
    for(int i=0;i<licznik;i++){
        std::cout<< dane[i] << " ";//wypisanie elementu
    }
    std::cout<<std::endl;
}