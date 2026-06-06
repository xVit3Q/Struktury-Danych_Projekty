#ifndef DRZEWOAVL_HPP
#define DRZEWOAVL_HPP

struct ElementAVL {
    int klucz;
    int wartosc;
    ElementAVL* lewy;
    ElementAVL* prawy;
    int wysokosc;
};

class DrzewoAVL {
    private:
        ElementAVL* korzen;
        int licznik;

        int wysokosc(ElementAVL* e) const;
        int wspolczynnikRownowagi(ElementAVL* e) const;
        void aktualizujWysokosc(ElementAVL* e);

        ElementAVL* rotacjaLewo(ElementAVL* x);
        ElementAVL* rotacjaPrawo(ElementAVL* y);
        ElementAVL* zrownowaz(ElementAVL* e);
        ElementAVL* removeMinimum(ElementAVL* e, ElementAVL*& minNode);

        ElementAVL* insert(ElementAVL* e, int klucz, int wartosc, bool& wstawiono);
        ElementAVL* remove(ElementAVL* e, int klucz, bool& usunieto);
        ElementAVL* find(ElementAVL* e, int klucz) const;
        void wyczysc(ElementAVL* e);
        ElementAVL * kopiuj(ElementAVL* e);

    public:
        DrzewoAVL();
        ~DrzewoAVL();
        DrzewoAVL(const DrzewoAVL& other);
        DrzewoAVL& operator=(const DrzewoAVL& other);

        void insert(int klucz, int wartosc);
        void remove(int klucz);

        int returnSize() const;
        bool pusty() const;


};

#endif