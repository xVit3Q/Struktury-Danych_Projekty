#include "pomocnicze.hpp"
#include <fstream>
#include "losowanie.hpp"
#include <chrono>

using namespace std;

void logujWynik(const string& opis, long long ns) {
    ofstream log("wyniki.txt", ios::app);
    if (log.is_open()) {
        double ms = ns / 1'000'000.0;
        log << opis << " | " << ns << " ns (" << ms << " ms)" << endl;
    }
}

void zapiszDoPliku(const vector<int>& dane) {
    ofstream file("dane.txt");
    for (int x : dane) file << x << "\n";
}
void zapiszCsv(ofstream& plik, const string& struktura, int rozmiar, const string& operacja, long long ns) {
    double ms = ns / 1'000'000.0;
    plik << struktura << "," << rozmiar << "," << operacja << "," << ns << "," << ms << "\n";
}

vector<int> wczytajZPliku() {
    vector<int> dane;
    ifstream file("dane.txt");
    int x;
    while (file >> x) dane.push_back(x);
    return dane;
}
vector<int> generujDane(int count) {
    vector<int> dane;
    dane.reserve(count);
    for (int i = 0; i < count; i++) {
        dane.push_back(losujInt32());
    }
    return dane;
}