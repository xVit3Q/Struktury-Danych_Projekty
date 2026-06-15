#ifndef TABLICACUKCOO_HPP
#define TABLICACUKCOO_HPP
//Struktura reprezentująca pojedynczą komórkę w tablicy kukułczej
struct ElementCuckoo {
    int klucz;
    int wartosc;
    bool zajeta = false;//Flaga określająca, czy komórka przechowuje aktualny element
};

class TablicaCuckoo {
private:
    ElementCuckoo* tablica1;//Pierwsza tablica mieszająca
    ElementCuckoo* tablica2;//Druga tablica mieszająca
    int licznik;//Łączna liczba elementów w obu tablicach
    int rozmiar;//Rozmiar pojedynczej tablicy

    int funkcjaMieszajaca1(int klucz) const;//Pierwsza funkcja mieszająca
    int funkcjaMieszajaca2(int klucz) const;//Druga funkcja mieszająca
    
    void rehash(int nowyRozmiar);//Przebudowa struktur i ponowne rozlokowanie elementów
    void zwiekszRozmiar();//Sprawdzenie warunku i ewentualne powiększenie tablic
    void zmniejszRozmiar();//Sprawdzenie warunku i ewentualne pomniejszenie tablic

public:
    TablicaCuckoo();//Konstruktor domyślny
    ~TablicaCuckoo();//Destruktor

    TablicaCuckoo(const TablicaCuckoo& other);//Konstruktor kopiujący
    TablicaCuckoo& operator=(const TablicaCuckoo& other);//Operator przypisania

    void insert(int klucz, int wartosc);//Wstawienie elementu z obsługą wysiedlania
    void remove(int klucz);//Usunięcie elementu
    int returnSize() const;//Zwraca aktualną liczbę przechowywanych elementów
};

#endif