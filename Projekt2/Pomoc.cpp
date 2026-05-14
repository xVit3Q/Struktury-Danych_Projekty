#include "Pomoc.hpp"
#include "FillTabRand.hpp"
#include <fstream>

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