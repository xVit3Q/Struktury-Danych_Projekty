#include "listaDwukierunkowa.hpp"
#include <iostream>
#include "losowanie.hpp"
using std::cout;
using std::endl;
ListaDwukierunkowa::ListaDwukierunkowa() : head(nullptr), tail(nullptr), rozmiar(0) {}

ListaDwukierunkowa::~ListaDwukierunkowa() {
    Node* current = head; // ustawienie aktualnego wskaźnika jako head
    while (current) { // pętla wykonująca się dopóki lista nie jest pusta
        Node* next = current->next; // zapisuje wskaźnik następnego elementu, potem go usuwa i idzie dalej
        delete current; 
        current = next; 
    }
}
ListaDwukierunkowa::ListaDwukierunkowa(const ListaDwukierunkowa& other) : head(nullptr), tail(nullptr), rozmiar(0) {
    Node* current = other.head; // ustawienie aktualnego wskaźnika jako head
    while (current != nullptr) {
        dodajNaKoniec(current->dane); // dodaje elementy z innej listy na koniec tej listy
        current = current->next;
    }
}
ListaDwukierunkowa& ListaDwukierunkowa::operator=(const ListaDwukierunkowa& other) {
    if (this == &other) {
        return *this; // obsługa przypisania do samego siebie
    }
    // Najpierw czysci obecną listę, aby uniknąć wycieków pamięci
    while(head != nullptr) usunZPoczatku(); // usuwanie elementów z obecnej listy

    head = nullptr;
    tail = nullptr;
    rozmiar = 0;

    Node* current = other.head; // ustawienie aktualnego wskaźnika jako head
    while (current != nullptr) {
        dodajNaKoniec(current->dane); // dodajemy elementy z innej listy na koniec tej listy
        current = current->next;
    }
    
    return *this; // zwracamy referencję do tego obiektu
}
void ListaDwukierunkowa::dodajNaPoczatek(int value) {
    Node* newNode = new Node(value); // tworzenie nowego węzła
    if (!head) {
        head = tail = newNode; // w przypadku gdy lista jest pusta, head i tail wskazują na ten sam nowy węzeł
    } else {
        newNode->next = head; // nowy węzeł wskazuje na stary head
        head->prev = newNode; // stary head wskazuje wstecz
        head = newNode; // przesunięcie head 
    }
    rozmiar++;
}
void ListaDwukierunkowa::dodajNaKoniec(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode; // sprawdza czy lista jest pusta, jeśli tak to ustawia head i tail na nowy element
    } else {
        tail->next = newNode; // dodanie na koniec listy
        newNode->prev = tail; // ustawienie wskaźnika prev nowego elementu na stary tail
        tail = newNode; // przesunięcie tail na nowy element
    }
    rozmiar++;
}
void ListaDwukierunkowa::dodajNaPozycje(int value, int pozycja) {
    if(pozycja < 0 || pozycja > rozmiar) {
        cout << "Nieprawidłowa pozycja!" << endl;
        return;
    }
    if (pozycja ==0) { dodajNaPoczatek(value); return; }
    if (pozycja == rozmiar) { dodajNaKoniec(value); return; }

    Node* current;
    if(pozycja <= rozmiar /2){
        current = head;
        for(int i = 0; i < pozycja - 1; i++)
        {
            current = current->next; // przechodzi do elementu przed pozycja przed wstawianiem (i - 1)
        }
    }
    else {
        current = tail;
        for(int i = rozmiar - 1; i > pozycja - 1; i--)
        {
            current = current->prev; // przechodzi do elementu przed pozycja przed wstawianiem (i - 1) od końca listy
        }
    }
    //wstawianie nowego elementu przed current
    Node* newNode = new Node(value); // tworzy nowy element
    newNode->prev = current->prev; //nowy wskazuje wstecz na poprzednika current
    newNode->next = current; //nowy wskazuje na current
    current->prev->next = newNode; //poprzednik current wskazuje na nowy element
    current->prev = newNode; //current wskazuje wstecz na nowy element
    rozmiar++;

}
void ListaDwukierunkowa::dodajNaLosoweMiejsce(int value) {
    int pozycja = losujPozycje(0, rozmiar);
    dodajNaPozycje(value, pozycja);
}
void ListaDwukierunkowa::usunZPoczatku() {
    if (!head) {
        cout << "Lista jest pusta!" << endl;
        return;
    }
    Node* temp = head; // zapisanie wskaźnika do usunięcia
    head = head->next; // przesunięcie head na następny element
    if (head) {
        head->prev = nullptr; // odcięcie wskaźnika prev od nowego head
    }
    delete temp; // usunięcie starego head
    rozmiar--;
    if (!head) {
        tail = nullptr; // jeśli lista jest teraz pusta to tail również powinien być nullptr
    }
}
void ListaDwukierunkowa::usunZKonca() {
    if (!head) {
        cout << "Lista jest pusta!" << endl;
        return;
    }
    if (head == tail) { // jeśli jest tylko jeden element w liście
        delete head;
        head = tail = nullptr;
    } else {
        Node* temp = tail; // zapisanie wskaźnika do usunięcia starego tail
        tail = tail->prev; // przesunięcie tail na poprzedni element ta poprawka z O(n) na O(1)
        tail->next = nullptr; // odcięcie wskaźnika next od nowego tail
        delete temp; // usunięcie starego tail
    }
    rozmiar--;
}

void ListaDwukierunkowa::usunZPozycji(int pozycja) {
    if (pozycja < 0 || pozycja >= rozmiar) {
        cout << "Nieprawidłowa pozycja!" << endl;
        return;
    }
    if (pozycja == 0) { usunZPoczatku(); return; }
    if (pozycja == rozmiar - 1) { usunZKonca(); return; }

    Node* current;

    if(pozycja <= rozmiar /2) {
        current = head;
        for(int i = 0; i < pozycja; i++)
        {
            current = current->next;
        }
    } else {
        current = tail;
        for(int i = rozmiar - 1; i > pozycja; i--)
        {
            current = current->prev;
        }
    }
    current->prev->next = current->next; // poprzedni element omija current
    current->next->prev = current->prev; // następny element omija current

    current->next = nullptr; // odcięcie wskaźników current
    current->prev = nullptr;
    delete current; // usunięcie current
    rozmiar--;

}
void ListaDwukierunkowa::usunZLosowegoMiejsca() {
    if (rozmiar == 0) {
        cout << "Lista jest pusta!" << endl;
        return;
    }
    int pozycja = losujPozycje(0, rozmiar - 1);
    usunZPozycji(pozycja);
}
int ListaDwukierunkowa::szukaj(int value) const {
    Node* left = head;
    Node* right = tail;
    int leftIndex = 0;
    int rightIndex = rozmiar - 1;

    while (left != nullptr && right != nullptr && leftIndex <= rightIndex) {
        if (left->dane == value) {
            return leftIndex; // znaleziono wartość po lewej stronie
        }
        if (right->dane == value) {
            return rightIndex; // znaleziono wartość po prawej stronie
        }
        left = left->next; // przesunięcie w prawo
        right = right->prev; // przesunięcie w lewo
        leftIndex++;
        rightIndex--;
    }
    return -1; // zwraca -1 jeśli nie znaleziono elementu
}
void ListaDwukierunkowa::wyswietl() const {
    Node* current = head;
    cout << "Lista: ";
    while (current) {
        cout << current->dane << " ";
        current = current->next;
    }
    cout << endl;
}
