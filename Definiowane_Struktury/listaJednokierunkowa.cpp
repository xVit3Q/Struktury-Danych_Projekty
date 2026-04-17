#include "listaJednokierunkowa.hpp"
#include <iostream>

ListaJednokierunkowa::ListaJednokierunkowa() : head(nullptr), tail(nullptr), rozmiar(0) {}

ListaJednokierunkowa::~ListaJednokierunkowa() {
    Node* current = head; //ustwanienie aktuilnego wskaźnika jako head
    while (current) { //pętla wykonujaca sie dopóki lista nie jest pusta
        Node* next = current->next; 
        delete current; 
        current = next; 
    }
}
void ListaJednokierunkowa::dodajNaPoczatek(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    rozmiar++;
}
void ListaJednokierunkowa::dodajNaPozycje(int value, int pozycja) {
    if (pozycja < 0 || pozycja > rozmiar) {
        std::cout << "Nieprawidłowa pozycja!" << std::endl;
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
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    rozmiar++;
}
void ListaJednokierunkowa::dodajNaKoniec(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    rozmiar++;
}
void ListaJednokierunkowa::usunZPoczatku() {
    if (!head) {
        std::cout << "Lista jest pusta!" << std::endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    rozmiar--;
    if (!head) {
        tail = nullptr;
    }
}
void ListaJednokierunkowa::usunZPozycji(int pozycja) {
    if (pozycja < 0 || pozycja >= rozmiar) {
        std::cout << "Nieprawidłowa pozycja!" << std::endl;
        return;
    }
    if (pozycja == 0) {
        usunZPoczatku();
        return;
    }
    Node* current = head;
    for (int i = 0; i < pozycja - 1; i++) {
        current = current->next;
    }
    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    rozmiar--;
    if (current->next == nullptr) {
        tail = current;
    }
}
void ListaJednokierunkowa::usunZKonca() {
    if (!head) {
        std::cout << "Lista jest pusta!" << std::endl;
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    rozmiar--;
}
void ListaJednokierunkowa::szukaj(int value) const {
    Node* current = head;
    int index = 0;
    while (current) {
        if (current->dane == value) {
            std::cout << "Znaleziono wartość " << value << " na pozycji " << index << "." << std::endl;
            return;
        }
        current = current->next;
        index++;
    }
    std::cout << "Nie znaleziono wartości " << value << " w liście." << std::endl;
}
void ListaJednokierunkowa::wyswietl() const {
    Node* current = head;
    std::cout << "Lista: ";
    while (current) {
        std::cout << current->dane << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
