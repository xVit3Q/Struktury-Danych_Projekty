#include "KopiecBinarny.hpp"
#include <iostream>
#include <stdexcept>

using std::string;
using std::cout;
using std::endl;

// ============================================================
// Metody pomocnicze — obliczanie indeksów
// ============================================================

int BinaryHeap::parent(int i) const {
    return (i - 1) / 2;
}

int BinaryHeap::leftChild(int i) const {
    return 2 * i + 1;
}

int BinaryHeap::rightChild(int i) const {
    return 2 * i + 2;
}

// ============================================================
// Zamiana dwóch elementów w tablicy kopca
// ============================================================
void BinaryHeap::swap(int i, int j) {
    BinaryHeapElement temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// ============================================================
// heapifyUp — przywraca własność kopca po wstawieniu elementu
// Nowy element wstawiony na koniec "wędruje" w górę
// dopóki jego priorytet jest wyższy niż rodzica
// ============================================================
void BinaryHeap::heapifyUp(int index) {
    while (index > 0 && heap[index].priority > heap[parent(index)].priority) {
        swap(index, parent(index));
        index = parent(index);
    }
}

// ============================================================
// heapifyDown — przywraca własność kopca po usunięciu korzenia
// Element z końca przeniesiony na szczyt "wędruje" w dół
// dopóki jego priorytet jest niższy niż któregoś z dzieci
// ============================================================
void BinaryHeap::heapifyDown(int index) {
    int largest = index;
    int left    = leftChild(index);
    int right   = rightChild(index);
    int n       = (int)heap.size();

    // Sprawdź czy lewe dziecko istnieje i ma wyższy priorytet
    if (left < n && heap[left].priority > heap[largest].priority)
        largest = left;

    // Sprawdź czy prawe dziecko istnieje i ma wyższy priorytet niż obecny largest
    if (right < n && heap[right].priority > heap[largest].priority)
        largest = right;

    // Jeśli largest zmienił się — zamień i kontynuuj w dół
    if (largest != index) {
        swap(index, largest);
        heapifyDown(largest);
    }
}

// ============================================================
// Wyszukiwanie elementu po wartości — O(n)
// ============================================================
int BinaryHeap::findIndex(const string& value) const {
    for (int i = 0; i < (int)heap.size(); i++) {
        if (heap[i].value == value)
            return i;
    }
    return -1; // nie znaleziono
}

// ============================================================
// insert — wstawia nowy element na koniec tablicy,
// następnie przywraca własność kopca przez heapifyUp — O(log n)
// ============================================================
void BinaryHeap::insert(const string& value, int priority) {
    heap.emplace_back(value, priority);
    heapifyUp((int)heap.size() - 1);
}

// ============================================================
// extractMax — usuwa i zwraca korzeń (element o max priorytecie)
// Zamienia korzeń z ostatnim elementem, usuwa ostatni,
// następnie przywraca własność przez heapifyDown — O(log n)
// ============================================================
BinaryHeapElement BinaryHeap::extractMax() {
    if (heap.empty())
        throw std::runtime_error("BinaryHeap: kolejka jest pusta!");

    BinaryHeapElement maxElem = heap[0]; // zapamiętaj maksimum

    heap[0] = heap.back();  // przenieś ostatni element na szczyt
    heap.pop_back();         // usuń ostatni element

    if (!heap.empty())
        heapifyDown(0);      // przywróć własność kopca

    return maxElem;
}

// ============================================================
// peek — zwraca element o największym priorytecie bez usuwania
// Korzeń kopca to zawsze maksimum — O(1)
// ============================================================
const BinaryHeapElement& BinaryHeap::peek() const {
    if (heap.empty())
        throw std::runtime_error("BinaryHeap: kolejka jest pusta!");
    return heap[0];
}

// ============================================================
// increaseKey — zwiększa priorytet elementu
// Po zwiększeniu element może być wyżej niż rodzic — heapifyUp
// ============================================================
void BinaryHeap::increaseKey(const string& value, int newPriority) {
    int idx = findIndex(value);
    if (idx == -1)
        throw std::runtime_error("BinaryHeap: element nie istnieje!");
    if (newPriority < heap[idx].priority)
        throw std::invalid_argument("BinaryHeap::increaseKey: nowy priorytet musi byc wiekszy!");

    heap[idx].priority = newPriority;
    heapifyUp(idx); // nowy priorytet może być wyższy niż rodzic
}

// ============================================================
// decreaseKey — zmniejsza priorytet elementu
// Po zmniejszeniu element może być niżej niż dzieci — heapifyDown
// ============================================================
void BinaryHeap::decreaseKey(const string& value, int newPriority) {
    int idx = findIndex(value);
    if (idx == -1)
        throw std::runtime_error("BinaryHeap: element nie istnieje!");
    if (newPriority > heap[idx].priority)
        throw std::invalid_argument("BinaryHeap::decreaseKey: nowy priorytet musi byc mniejszy!");

    heap[idx].priority = newPriority;
    heapifyDown(idx); // nowy priorytet może być niższy niż dzieci
}

// ============================================================
// modifyKey — zmienia priorytet w dowolnym kierunku
// ============================================================
void BinaryHeap::modifyKey(const string& value, int newPriority) {
    int idx = findIndex(value);
    if (idx == -1)
        throw std::runtime_error("BinaryHeap: element nie istnieje!");

    int oldPriority = heap[idx].priority;
    heap[idx].priority = newPriority;

    if (newPriority > oldPriority)
        heapifyUp(idx);
    else if (newPriority < oldPriority)
        heapifyDown(idx);
    // jeśli równy — nic nie rób
}

// ============================================================
// returnSize — zwraca liczbę elementów w kopcu — O(1)
// ============================================================
int BinaryHeap::returnSize() const {
    return (int)heap.size();
}

bool BinaryHeap::isEmpty() const {
    return heap.empty();
}

// ============================================================
// print — wypisuje zawartość kopca (kolejność tablicy)
// ============================================================
void BinaryHeap::print() const {
    if (heap.empty()) {
        cout << "  [pusty kopiec]" << endl;
        return;
    }
    cout << "  BinaryHeap (" << heap.size() << " elementow):" << endl;
    for (const auto& e : heap)
        cout << "    [" << e.value << ", priorytet=" << e.priority << "]" << endl;
}