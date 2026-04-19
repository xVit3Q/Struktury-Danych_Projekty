#include "listaDwukierunkowa.hpp"
#include <iostream>
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
    // na początku sprawdzamy czy pozycja jest poprawna lub czy pozycja jest równa 0 lub równa rozmiarowi listy, jeśli tak to wywołujemy odpowiednie funkcje
    if (pozycja < 0 || pozycja > rozmiar) {
        cout << "Nieprawidłowa pozycja!" << endl;
        return;
    }
    if (pozycja == 0) { 
        dodajNaPoczatek(value);
        return;
    }
    if (pozycja == rozmiar) {
        dodajNaKoniec(value);
        return;
    }
    Node* newNode = new Node(value); // nowy element
    Node* current = head;
    for (int i = 0; i < pozycja - 1; i++) {
        current = current->next; // przesuwanie się do elementu przed pozycją docelową (i - 1)
    }
    newNode->next = current->next; // ustawienie wskaźnika next 
    newNode->prev = current; // i prev nowego elementu
    if (current->next) {
        current->next->prev = newNode; 
    }
    current->next = newNode; //
    rozmiar++;
}
void ListaDwukierunkowa::dodajNaLosoweMiejsce(int value) {
    int pozycja = rand() % (rozmiar + 1); // losowa pozycja od 0 do rozmiar
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
    if (head == tail) { //jeśli jest tylko jeden element w liście
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next; //przesuwanie się do przedostatniego elementu
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    rozmiar--;
}
void ListaDwukierunkowa::usunZPozycji(int pozycja) {
    if (pozycja < 0 || pozycja >= rozmiar) {
        cout << "Nieprawidłowa pozycja!" << endl;
        return;
    }

    if (pozycja == 0) {
        usunZPoczatku();
        return;
    }

    if (pozycja == rozmiar - 1) {
        usunZKonca();
        return;
    }

    Node* current = head;

    for (int i = 0; i < pozycja - 1; i++) {
        current = current->next;
    }

    Node* temp = current->next; // zapisanie wskaźnika do usunięcia

    current->next = temp->next; // przesunięcie wskaźnika next poprzedniego elementu na element po usuwanym
    temp->next->prev = current;

    delete temp;
    rozmiar--;
}
void ListaDwukierunkowa::usunZLosowegoMiejsca() {
    if (rozmiar == 0) {
        cout << "Lista jest pusta!" << endl;
        return;
    }
    int pozycja = rand() % rozmiar; // losowa pozycja od 0 do rozmiar - 1
    usunZPozycji(pozycja);
}
void ListaDwukierunkowa::szukaj(int value) const {
    Node* current = head;
    int index = 0;
    while (current) {
        if (current->dane == value) {
            cout << "Znaleziono wartość " << value << " na pozycji " << index << "." << endl;
            return;
        }
        current = current->next;
        index++;
    }
    cout << "Nie znaleziono wartości " << value << " w liście." << endl;
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
