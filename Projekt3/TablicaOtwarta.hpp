#ifndef TABLICAOTWARTA_HPP
#define TABLICAOTWARTA_HPP
//Status komórki w tablicy mieszającej z adresowaniem otwartym
enum StatusKomorki{WOLNA,ZAJETA};

//Struktura reprezentująca pojedynczy element (parę klucz-wartość) w tablicy
struct ElementOtwarta {
    int klucz;
    int wartosc;
    StatusKomorki status = WOLNA;//Domyślnie każda nowa komórka jest wolna
};

class TablicaOtwarta{
private:
    ElementOtwarta* dane;//Dynamiczna tablica struktur ElementOtwarta
    int licznik;//Aktualna liczba przechowywanych elementów
    int rozmiar;//Całkowity rozmiar (pojemność) tablicy

    void zwiekszRozmiar();//Automatyczne podwajanie rozmiaru tablicy
    void zmniejszRozmiar();//Zmniejszanie tablicy przy niskim zapełnieniu
    int funkcjaMieszajaca(int klucz) const;//Wyznaczenie indeksu bazowego dla klucza
public:
    TablicaOtwarta();//Konstruktor domyślny
    ~TablicaOtwarta();//Destruktor
    TablicaOtwarta(const TablicaOtwarta& other);//Konstruktor kopiujący
    TablicaOtwarta& operator=(const TablicaOtwarta& other);//Operator przypisania
    void insert(int klucz, int wartosc);//Wstawienie nowej pary lub aktualizacja
    void remove(int klucz);//Usunięcie elementu oraz reorganizacja luki
    int returnSize() const;//Zwraca aktualną liczbę elementów
};
#endif