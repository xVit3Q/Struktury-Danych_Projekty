#ifndef lista_Jednokierunkowa_hpp
#define lista_Jednokierunkowa_hpp

class ListaJednokierunkowa {
private:
    struct Node {
        int dane;
        Node* next;
        Node(int value) : dane(value), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int rozmiar;
public:
    ListaJednokierunkowa();
    ~ListaJednokierunkowa();
    void dodajNaPoczatek(int value);
    void dodajNaPozycje(int value, int pozycja);
    void dodajNaKoniec(int value);  
    void usunZPoczatku();
    void usunZPozycji(int pozycja);
    void usunZKonca();
    void szukaj(int value) const;
    void wyswietl() const;
};

#endif /* lista_Jednokierunkowa_hpp */ 