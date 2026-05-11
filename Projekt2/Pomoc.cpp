#include "Pomoc.hpp"
#include "FillTabRand.hpp"
#include <fstream>
#include <random>

using namespace std;

// ---------- narzędzia ogólne ----------
void zapiszCsv(ofstream& plik, const string& algorytm, int rozmiar,
               const string& typDanych, long long ns) 
{
    double ms = ns / 1'000'000.0;
    plik << algorytm << "," 
         << rozmiar << "," 
         << typDanych << "," 
         << ns << "," 
         << ms << "\n";
}

void zapiszDoPliku(const vector<int>& dane) {
    ofstream file("dane.txt");
    for (int x : dane) file << x << "\n";
}

vector<int> wczytajZPliku() {
    vector<int> dane;
    ifstream file("dane.txt");
    int x;
    while (file >> x) dane.push_back(x);
    return dane;
}
void flushCache() {
    static const size_t SIZE = 64 * 1024 * 1024; // 64 MB — powyżej większości L3
    static volatile char buffer[SIZE];            // volatile na buforze, nie na sumie

    for (size_t i = 0; i < SIZE; i += 64) {      // co linię cache
        buffer[i] = static_cast<char>(i);         // zapis wymuszony przez volatile
    }
}