#ifndef TABLICAOTWARTA_HPP
#define TABLICAOTWARTA_HPP

enum StatusKomorki{WOLNA,ZAJETA};

struct ElementOtwarta {
    int klucz;
    int wartosc;
    StatusKomorki status = WOLNA;
};

class TablicaOtwarta{
private:
    ElementOtwarta* dane;
    int licznik;
    int rozmiar;

    void zwiekszRozmiar();
    void zmniejszRozmiar();
    int funkcjaMieszajaca(int klucz) const;
public:
    TablicaOtwarta();
    ~TablicaOtwarta();
    TablicaOtwarta(const TablicaOtwarta& other);
    TablicaOtwarta& operator=(const TablicaOtwarta& other);
    void insert(int klucz, int wartosc);
    void remove(int klucz);
    int returnSize() const;
};
#endif