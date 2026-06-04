#ifndef TABLICACUKCOO_HPP
#define TABLICACUKCOO_HPP

struct Element {
    int klucz;
    int wartosc;
    bool zajeta = false;
};

class TablicaCuckoo {
private:
    Element* tablica1;
    Element* tablica2;
    int licznik;
    int rozmiar;

    int funkcjaMieszajaca1(int klucz) const;
    int funkcjaMieszajaca2(int klucz) const;
    
    void rehash(int nowyRozmiar);
    void zwiekszRozmiar();
    void zmniejszRozmiar();

public:
    TablicaCuckoo();
    ~TablicaCuckoo();

    TablicaCuckoo(const TablicaCuckoo& other);
    TablicaCuckoo& operator=(const TablicaCuckoo& other);

    void insert(int klucz, int wartosc); 
    void remove(int klucz);
};

#endif