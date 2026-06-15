#include "TablicaOtwarta.hpp"

//inicjalizacja tablicy o rozmiarze początkowym 1
TablicaOtwarta::TablicaOtwarta(){
    licznik = 0;
    rozmiar = 1;
    dane = new ElementOtwarta[rozmiar];
}
//zwalnianie dynamicznie zaalokowanej pamięci tablicy
TablicaOtwarta::~TablicaOtwarta(){
    delete[] dane;
}
//kopiowanie danych z innego obiektu
TablicaOtwarta::TablicaOtwarta(const TablicaOtwarta& other){
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    dane = new ElementOtwarta[rozmiar];
    for(int i=0; i<rozmiar;i++){
        dane[i]=other.dane[i];
    }
}
//ochrona przed samoprzypisaniem i bezpieczna alokacja nowej pamięci
TablicaOtwarta& TablicaOtwarta::operator=(const TablicaOtwarta& other){
    if(this == &other)return *this;
    ElementOtwarta* noweDane = new ElementOtwarta[other.rozmiar];
    for(int i=0;i<other.rozmiar;i++){
        noweDane[i] = other.dane[i];
    }
    delete[] dane;//Zwolnienie starych zasobów
    dane = noweDane;
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    return *this;
}
//dwukrotnie powiększanie tablicy, gdy zapełnienie przekroczy 70%
void TablicaOtwarta::zwiekszRozmiar(){
    if(licznik >= rozmiar * 0.7){ 
        int nowyRozmiar = rozmiar * 2;
        ElementOtwarta* noweDane = new ElementOtwarta[nowyRozmiar];
        int staryRozmiar = rozmiar;
        rozmiar = nowyRozmiar;
        //rehashing,czyli ponowne przepisanie elementów do nowej, większej tablicy
        for(int i = 0; i < staryRozmiar; i++){
            if(dane[i].status == ZAJETA){
                int indeks = funkcjaMieszajaca(dane[i].klucz);
                //Próbkowanie liniowe w poszukiwaniu wolnego miejsca
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
//Zmniejszanie tablicy, gdy stopień zapełnienia spadnie poniżej 25%
void TablicaOtwarta::zmniejszRozmiar(){
    int staryRozmiar = rozmiar;
    while(licznik <= rozmiar / 4 && rozmiar > 1){
        rozmiar /= 2;
    }
    if(rozmiar != staryRozmiar){
        ElementOtwarta* noweDane = new ElementOtwarta[rozmiar];
        //Ponowne haszowanie elementów do mniejszej przestrzeni
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
//funkcja mieszająca wyznaczająca indeks bazowy
int TablicaOtwarta::funkcjaMieszajaca(int klucz) const {
    unsigned int u_klucz = static_cast<unsigned int>(klucz);
    return static_cast<int>(u_klucz % rozmiar);
}
//Wstawianie nowej pary klucz-wartość lub aktualizacja istniejącej
void TablicaOtwarta::insert(int klucz, int wartosc){
    zwiekszRozmiar();//Sprawdzenie warunku powiększenia tablicy
    int indeks = funkcjaMieszajaca(klucz);
    int startowyIndeks = indeks;
    //Szukanie klucza lub pierwszego wolnego miejsca (próbkowanie liniowe)
    while(dane[indeks].status == ZAJETA){
        if(dane[indeks].klucz == klucz){
            dane[indeks].wartosc = wartosc;//jeśli klucz istnieje to aktualizacja wartości
            return;
        }
        indeks = (indeks + 1) % rozmiar;
        if(indeks == startowyIndeks){
            return;//Zabezpieczenie przed pętlą nieskończoną (gdyby tablica była pełna)
        }
    }
    //Zapis nowego elementu w znalezionym wolnym miejscu
    dane[indeks].klucz = klucz;
    dane[indeks].wartosc = wartosc;
    dane[indeks].status = ZAJETA;
    licznik++;
}
//Usuwanie elementu i restrukturyzacja sąsiadujących komórek w celu uniknięcia luk
void TablicaOtwarta::remove(int klucz){
    if(licznik == 0){
        return;
    }
    //Przesuwanie kolejnych elementów, by zapełnić powstałą "dziurę"
    int indeks = funkcjaMieszajaca(klucz);
    int startowyIndeks = indeks;
 
    while(dane[indeks].status == ZAJETA){
        if(dane[indeks].klucz == klucz){
            dane[indeks].status = WOLNA;
            licznik--;
            int pustaKomorka = indeks;
            int kolejny = (indeks + 1) % rozmiar;
            while(dane[kolejny].status == ZAJETA){
                int bazowy = funkcjaMieszajaca(dane[kolejny].klucz);
                bool miedzy = false;
                if (pustaKomorka < kolejny) {
                    miedzy = (bazowy > pustaKomorka && bazowy <= kolejny);
                } else {
                    miedzy = (bazowy > pustaKomorka || bazowy <= kolejny);
                }
                //Jeśli element powinien znajdować się wcześniej, przesuwamy go
                if (!miedzy) {
                    dane[pustaKomorka] = dane[kolejny];
                    dane[kolejny].status = WOLNA;
                    pustaKomorka = kolejny;
                }
                
                kolejny = (kolejny + 1) % rozmiar;
            }
            zmniejszRozmiar();//Ewentualne zmniejszenie rozmiaru po zwolnieniu miejsca
            return;
        }
        indeks = (indeks + 1) % rozmiar;
        if(indeks == startowyIndeks){
            break;
        }
    }
}
//Zwraca aktualną liczbę przechowywanych elementów
int TablicaOtwarta::returnSize() const{
    return licznik;
}