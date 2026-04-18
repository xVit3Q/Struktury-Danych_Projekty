#include "pomocnicze.hpp"
#include <fstream>
#include <random>
#include <limits>
#include <chrono>

using namespace std;

void logujWynik(const string& opis, long long ns) {
    ofstream log("wyniki.txt", ios::app);
    if (log.is_open()) {
        double ms = ns / 1'000'000.0;
        log << opis << " | " << ns << " ns (" << ms << " ms)" << endl;
    }
}

int losujInt32() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    return distribution(generator);
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
vector<int> generujDane(int count) {
    vector<int> dane;
    dane.reserve(count);
    for (int i = 0; i < count; i++) {
        dane.push_back(losujInt32());
    }
    return dane;
}