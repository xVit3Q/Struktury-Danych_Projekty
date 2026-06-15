#include "TablicaCuckoo.hpp"
#include <cmath>
//alokacja pamięci dla dwóch niezależnych tablic składowych
TablicaCuckoo::TablicaCuckoo(){
    licznik = 0;
    rozmiar = 1;
    tablica1 = new ElementCuckoo[rozmiar];
    tablica2 = new ElementCuckoo[rozmiar];
}
//poprawne zwalnianie pamięci obu tablic
TablicaCuckoo::~TablicaCuckoo(){
    delete[] tablica1;
    delete[] tablica2;
}
//kopiowanie obu struktur danych
TablicaCuckoo::TablicaCuckoo(const TablicaCuckoo& other){
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    tablica1 = new ElementCuckoo[rozmiar];
    tablica2 = new ElementCuckoo[rozmiar];
    for(int i = 0; i < rozmiar; i++){
        tablica1[i] = other.tablica1[i];
        tablica2[i] = other.tablica2[i];
    }
}
//Operator przypisania z zabezpieczeniem przed samoprzypisaniem
TablicaCuckoo& TablicaCuckoo::operator=(const TablicaCuckoo& other){
    if(this == &other){
        return *this;
    }
    //Bezpieczna alokacja nowych zasobów przed usunięciem starych
    ElementCuckoo* nowaTablica1 = new ElementCuckoo[other.rozmiar];
    ElementCuckoo* nowaTablica2 = new ElementCuckoo[other.rozmiar];
    for(int i = 0; i < other.rozmiar; i++){
        nowaTablica1[i] = other.tablica1[i];
        nowaTablica2[i] = other.tablica2[i];
    }

    delete[] tablica1;
    delete[] tablica2;

    tablica1 = nowaTablica1;
    tablica2 = nowaTablica2;
    licznik = other.licznik;
    rozmiar = other.rozmiar;

    return *this;
}
//Pierwsza funkcja mieszająca
int TablicaCuckoo::funkcjaMieszajaca1(int klucz) const {
    unsigned int u_klucz = static_cast<unsigned int>(klucz);
    return static_cast<int>(u_klucz % rozmiar);
}
//Druga funkcja mieszająca (haszowanie Fibonacciego)
int TablicaCuckoo::funkcjaMieszajaca2(int klucz) const {
    double A = 1.618033; //złota proporcja (haszowanie Fibonacciego)
    unsigned int u_klucz = static_cast<unsigned int>(klucz);
    double iloczyn = u_klucz * A;
    double czesc_ulamkowa = iloczyn - static_cast<long long>(iloczyn);
    return static_cast<int>(czesc_ulamkowa * rozmiar);
}
//Rehash-relokacja wszystkich istniejących elementów do tablic o nowym rozmiarze
void TablicaCuckoo::rehash(int nowyRozmiar) {
    int staryRozmiar = rozmiar;
    ElementCuckoo* staraTablica1 = tablica1;
    ElementCuckoo* staraTablica2 = tablica2;

    rozmiar = nowyRozmiar;
    tablica1 = new ElementCuckoo[rozmiar];
    tablica2 = new ElementCuckoo[rozmiar];
    licznik = 0;//Licznik zostanie zaktualizowany podczas ponownego wstawiania (insert)

    for (int i = 0; i < staryRozmiar; i++) {
        if (staraTablica1[i].zajeta) {
            insert(staraTablica1[i].klucz, staraTablica1[i].wartosc);
        }
        if (staraTablica2[i].zajeta) {
            insert(staraTablica2[i].klucz, staraTablica2[i].wartosc);
        }
    }
    delete[] staraTablica1;
    delete[] staraTablica2;
}
//Powiększenie tablicy, gdy współczynnik zapełnienia osiągnie 50%
void TablicaCuckoo::zwiekszRozmiar() {
    if (licznik >= rozmiar * 0.5) {
        int nowyRozmiar;
        if (rozmiar == 0) {
            nowyRozmiar = 1;
        } else {
            nowyRozmiar = rozmiar * 2;
        }
        rehash(nowyRozmiar);
    }
}
//Pomniejszenie struktury, jeśli zajęte jest mniej niż 25% miejsc
void TablicaCuckoo::zmniejszRozmiar() {
    int staryRozmiar = rozmiar;
    while (licznik <= rozmiar / 4 && rozmiar > 1) {
        rozmiar /= 2;
    }

    if (rozmiar != staryRozmiar) {
        rehash(rozmiar);
    }
}
//Wstawianie elementu z obsługą algorytmu wysiedlania
void TablicaCuckoo::insert(int klucz, int wartosc) {
    //Sprawdzenie, czy klucz już istnieje w tablicy 1 i aktualizacja wartości
    int idx1 = funkcjaMieszajaca1(klucz);
    if (tablica1[idx1].zajeta && tablica1[idx1].klucz == klucz) {
        tablica1[idx1].wartosc = wartosc;
        return;
    }
    //Sprawdzenie, czy klucz już istnieje w tablicy 2 i aktualizacja wartości
    int idx2 = funkcjaMieszajaca2(klucz);
    if (tablica2[idx2].zajeta && tablica2[idx2].klucz == klucz) {
        tablica2[idx2].wartosc = wartosc;
        return;
    }

    zwiekszRozmiar();

    int obecnyKlucz = klucz;
    int obecnaWartosc = wartosc;
    //Maksymalna liczba prób wstawienia zapobiegająca pętli nieskończonej przy cyklach
    int max_prob = rozmiar * 2 + 10; 

    for (int i = 0; i < max_prob; i++) {
        idx1 = funkcjaMieszajaca1(obecnyKlucz);
        //Próba wstawienia do pierwszej tablicy (jeśli pusta)
        if (!tablica1[idx1].zajeta) {
            tablica1[idx1].klucz = obecnyKlucz;
            tablica1[idx1].wartosc = obecnaWartosc;
            tablica1[idx1].zajeta = true;
            licznik++;
            return;
        }
        //Wysiedlenie dotychczasowego elementu z tablicy 1
        int tempKlucz = tablica1[idx1].klucz;
        int tempWartosc = tablica1[idx1].wartosc;

        tablica1[idx1].klucz = obecnyKlucz;
        tablica1[idx1].wartosc = obecnaWartosc;
        //Przełączenie wysiedlonego elementu na pozycję w tablicy 2
        obecnyKlucz = tempKlucz;
        obecnaWartosc = tempWartosc;
        idx2 = funkcjaMieszajaca2(obecnyKlucz);
        
        //Próba wstawienia wysiedlonego elementu do drugiej tablicy (jeśli pusta)
        if (!tablica2[idx2].zajeta) {
            tablica2[idx2].klucz = obecnyKlucz;
            tablica2[idx2].wartosc = obecnaWartosc;
            tablica2[idx2].zajeta = true;
            licznik++;
            return;
        }
        //Wysiedlenie dotychczasowego elementu z tablicy 2
        tempKlucz = tablica2[idx2].klucz;
        tempWartosc = tablica2[idx2].wartosc;

        tablica2[idx2].klucz = obecnyKlucz;
        tablica2[idx2].wartosc = obecnaWartosc;
        //W kolejnej iteracji spróbujemy wstawić ten element z powrotem do tablicy 1
        obecnyKlucz = tempKlucz;
        obecnaWartosc = tempWartosc;
    }
    //Wykryto cykl (przekroczono limit prób) - wymuszenie powiększenia tablicy i rehash
    int wymuszonyRozmiar;
    if (rozmiar == 0) {
        wymuszonyRozmiar = 1;
    } else {
        wymuszonyRozmiar = rozmiar * 2;
    }
    rehash(wymuszonyRozmiar);
    insert(obecnyKlucz, obecnaWartosc);//Ponowna próba wstawienia po przebudowie
}
//Usuwanie elementu
void TablicaCuckoo::remove(int klucz) {
    if (licznik == 0) return;

    int idx1 = funkcjaMieszajaca1(klucz);
    if (tablica1[idx1].zajeta && tablica1[idx1].klucz == klucz) {
        tablica1[idx1].zajeta = false;
        licznik--;
        zmniejszRozmiar();
        return;
    }

    int idx2 = funkcjaMieszajaca2(klucz);
    if (tablica2[idx2].zajeta && tablica2[idx2].klucz == klucz) {
        tablica2[idx2].zajeta = false;
        licznik--;
        zmniejszRozmiar();
        return;
    }
}
//Zwraca łączną liczbę elementów przechowywanych w strukturze
int TablicaCuckoo::returnSize() const {
    return licznik;
}