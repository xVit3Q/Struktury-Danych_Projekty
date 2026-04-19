#include "listaJednokierunkowa.hpp"
#include <iostream>
using std::cout;
using std::endl;
ListaJednokierunkowa::ListaJednokierunkowa() : head(nullptr), tail(nullptr), rozmiar(0) {}

ListaJednokierunkowa::~ListaJednokierunkowa() {
    Node* current = head; //ustwanienie aktuilnego wskaźnika jako head
    while (current) { //dopóki lista nie jest pusta
        Node* next = current->next;  //zapamietuje nastepny element
        delete current; //usuwa aktualny element i idzie potem dalej
        current = next; //
    }
}
ListaJednokierunkowa::ListaJednokierunkowa(const ListaJednokierunkowa& other) : head(nullptr), tail(nullptr), rozmiar(0) {
    Node* current = other.head;
    while (current) {
        dodajNaKoniec(current->dane); //dodaje elementy z innej listy na koniec tej listy
        current = current->next;
    }
}
ListaJednokierunkowa& ListaJednokierunkowa::operator=(const ListaJednokierunkowa& other) {
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
void ListaJednokierunkowa::dodajNaPoczatek(int value) {
    Node* newNode = new Node(value); //tworzy nowy element
    if (!head) {
        head = tail = newNode; //sprawdza czy lista jest pusta, jesli tak to ustawia head i tail na nowy element
    } else {
        newNode->next = head; //ustawia next nowego elementu na aktualny head
        head = newNode; //aktualizuje początek listy
    }
    rozmiar++;
}
void ListaJednokierunkowa::dodajNaKoniec(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode; //sprawdza czy lista jest pusta, jesli tak to ustawia head i tail na nowy element
    } else {
        tail->next = newNode; //ustawia next ostatniego elementu na nowy element
        tail = newNode; //aktualizuje koniec listy
    }
    rozmiar++;
}
void ListaJednokierunkowa::dodajNaPozycje(int value, int pozycja) {
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
    Node* newNode = new Node(value);
    Node* current = head;
    for (int i = 0; i < pozycja - 1; i++) {
        current = current->next; //przechodzi do elementu przed pozycje przed wstawianiem (i - 1)
    }
    newNode->next = current->next; // podpiecie nowego elementu
    current->next = newNode;
    rozmiar++;
}
void ListaJednokierunkowa::dodajNaLosoweMiejsce(int value) {
    int pozycja = rand() % (rozmiar + 1); // losowa pozycja od 0 do rozmiar
    dodajNaPozycje(value, pozycja);
}
void ListaJednokierunkowa::usunZPoczatku() { 
    if (!head) {
        cout << "Lista jest pusta!" << endl;
        return;
    }
    Node* temp = head; //zapamietuje aktualny head
    head = head->next; //przesuniecie head na nastepny element
    delete temp; //usuwanie starego head
    rozmiar--;
    if (!head) {
        tail = nullptr; //jesli lista jest teraz pusta, ustawia tail na nullptr
    }
}
void ListaJednokierunkowa::usunZKonca() {
    if (!head) {
        cout << "Lista jest pusta!" << endl;
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next; //przechodzi do przedostatniego elementu
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    rozmiar--;
}
void ListaJednokierunkowa::usunZPozycji(int pozycja) {
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
        current = current->next; //przechodzi do elementu przed pozycja przed usuwaniem (i - 1)
    }
    Node* temp = current->next; //zapamietuje element do usuniecia
    current->next = temp->next; //omija element
    delete temp;
    rozmiar--;
}
void ListaJednokierunkowa::usunZLosowegoMiejsca() {
    if (rozmiar == 0) {
        cout << "Lista jest pusta!" << endl;
        return;
    }
    int pozycja = rand() % rozmiar; // losowa pozycja od 0 do rozmiar - 1
    usunZPozycji(pozycja);
}
void ListaJednokierunkowa::szukaj(int value) const {
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
void ListaJednokierunkowa::wyswietl() const {
    Node* current = head;
    cout << "Lista: ";
    while (current) {
        cout << current->dane << " ";
        current = current->next;
    }
    cout << endl;
}
