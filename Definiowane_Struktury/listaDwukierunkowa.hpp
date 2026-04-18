#ifndef lista_Dwukierunkowa_hpp
#define lista_Dwukierunkowa_hpp

class ListaDwukierunkowa {
private:
    struct Node {
        int dane;
        Node* next;                         
        Node* prev;
        Node(int value) : dane(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int rozmiar;
public:
    ListaDwukierunkowa();
    ~ListaDwukierunkowa();
    void dodajNaPoczatek(int value);
    void dodajNaPozycje(int value, int pozycja);
    void dodajNaKoniec(int value);
    void dodajNaLosoweMiejsce(int value);  
    void usunZPoczatku();
    void usunZPozycji(int pozycja);
    void usunZKonca();
    void usunZLosowegoMiejsca();
    void szukaj(int value) const;
    void wyswietl() const;
};

#endif /* lista_Dwukierunkowa_hpp */ 