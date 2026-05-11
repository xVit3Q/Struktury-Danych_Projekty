#pragma once
#include <vector>
#include <string>

// ============================================================
// Element przechowywany w kopcu binarnym
// ============================================================
struct BinaryHeapElement {
    std::string value;    // wartość elementu
    int priority;         // priorytet elementu

    BinaryHeapElement(const std::string& v, int p) : value(v), priority(p) {}
};

// ============================================================
// Kolejka priorytetowa MAX oparta na kopcu binarnym
// Kopiec binarny przechowuje elementy w tablicy (wektorze)
// Rodzic węzła i: leweDziecko = 2*i+1, praweDziecko = 2*i+2
// ============================================================
class BinaryHeap {
private:
    std::vector<BinaryHeapElement> heap; // wewnętrzna tablica kopca

    // Pomocnicze metody do utrzymania własności kopca
    void heapifyUp(int index);           // "bąbelkowanie" w górę po wstawieniu
    void heapifyDown(int index);         // "bąbelkowanie" w dół po usunięciu
    void swap(int i, int j);             // zamiana dwóch elementów

    int parent(int i) const;             // indeks rodzica
    int leftChild(int i) const;          // indeks lewego dziecka
    int rightChild(int i) const;         // indeks prawego dziecka

    int findIndex(const std::string& value) const; // szuka indeksu elementu po wartości

public:
    BinaryHeap() = default;
    ~BinaryHeap() = default;

    void insert(const std::string& value, int priority); // dodaj element
    BinaryHeapElement extractMax();                       // usuń i zwróć max
    const BinaryHeapElement& peek() const;               // podejrzyj max bez usuwania

    void increaseKey(const std::string& value, int newPriority); // zwiększ priorytet
    void decreaseKey(const std::string& value, int newPriority); // zmniejsz priorytet
    void modifyKey(const std::string& value, int newPriority);   // zmień priorytet

    int returnSize() const;   // zwróć rozmiar
    bool isEmpty() const;     // czy pusta
    void print() const;       // wypisz zawartość
};