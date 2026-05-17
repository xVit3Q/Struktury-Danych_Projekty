#include "KopiecBinarny.hpp"
#include <stdexcept>

KopiecBinarny::KopiecBinarny() {
    licznik = 0;
    rozmiar = 1;
    licznikKolejki = 0;
    dane = new ElementKopiec[rozmiar + 1]; // indeksujemy od 1
}

KopiecBinarny::~KopiecBinarny() {
    delete[] dane;
}

KopiecBinarny::KopiecBinarny(const KopiecBinarny& other) {
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    licznikKolejki = other.licznikKolejki;
    dane = new ElementKopiec[rozmiar + 1];
    for (int i = 1; i <= licznik; i++) {
        dane[i] = other.dane[i];
    }
}

KopiecBinarny& KopiecBinarny::operator=(const KopiecBinarny& other) {
    if (this == &other) return *this;

    ElementKopiec* noweDane = new ElementKopiec[other.rozmiar + 1];
    for (int i = 1; i <= other.licznik; i++) {
        noweDane[i] = other.dane[i];
    }

    delete[] dane;

    dane = noweDane;
    licznik = other.licznik;
    rozmiar = other.rozmiar;
    licznikKolejki = other.licznikKolejki;
    return *this;
}

void KopiecBinarny::zwiekszRozmiar() {
    if (licznik >= rozmiar) {
        rozmiar *= 2;
        ElementKopiec* noweDane = new ElementKopiec[rozmiar + 1];
        for (int i = 1; i <= licznik; i++) {
            noweDane[i] = dane[i];
        }
        delete[] dane;
        dane = noweDane;
    }
}

void KopiecBinarny::zmniejszRozmiar() {
    int staryRozmiar = rozmiar;
    while (licznik > 0 && licznik <= rozmiar / 4 && rozmiar > 1) {
        rozmiar /= 2;
    }
    if (rozmiar != staryRozmiar) {
        ElementKopiec* noweDane = new ElementKopiec[rozmiar + 1];
        for (int i = 1; i <= licznik; i++) {
            noweDane[i] = dane[i];
        }
        delete[] dane;
        dane = noweDane;
    }
}

int KopiecBinarny::rodzic(int i) const {
    return i / 2;
}
int KopiecBinarny::praweDziecko(int i) const {
    return 2 * i + 1;
}
int KopiecBinarny::leweDziecko(int i) const {
    return 2 * i;
}

bool KopiecBinarny::maNadrzednyPriorytet(int i, int j) const {
    if (dane[i].priorytet != dane[j].priorytet) {
        return dane[i].priorytet > dane[j].priorytet;
    }
    return dane[i].kolejnosc < dane[j].kolejnosc;
}

void KopiecBinarny::heapifyUp(int i) {
    while (i > 1 && maNadrzednyPriorytet(i, rodzic(i))) {
        ElementKopiec tmp = dane[i];
        dane[i] = dane[rodzic(i)];
        dane[rodzic(i)] = tmp;

        i = rodzic(i);
    }
}

// NAPRAWIONE: Bezpieczna i szybka wersja iteracyjna (pętla zamiast rekurencji)
void KopiecBinarny::heapifyDown(int i) {
    while (true) {
        int najwiekszy = i;
        int l = leweDziecko(i);
        int p = praweDziecko(i);

        if (l <= licznik && maNadrzednyPriorytet(l, najwiekszy)) {
            najwiekszy = l;
        }
        if (p <= licznik && maNadrzednyPriorytet(p, najwiekszy)) {
            najwiekszy = p;
        }

        if (najwiekszy != i) {
            ElementKopiec tmp = dane[i];
            dane[i] = dane[najwiekszy];
            dane[najwiekszy] = tmp;

            i = najwiekszy; // Przechodzimy niżej bez wywoływania funkcji na stosie
        } else {
            break; // Struktura kopca została przywrócona
        }
    }
}

void KopiecBinarny::insert(int e, int p) {
    zwiekszRozmiar();
    licznik++;
    dane[licznik] = ElementKopiec(e, p, licznikKolejki);
    licznikKolejki++;
    heapifyUp(licznik);
}

// NAPRAWIONE: Pętla zaczyna od 1, bo od 1 indeksujemy struktury danych
void KopiecBinarny::reserve(int n) {
    if (n <= rozmiar) return;
    ElementKopiec* noweDane = new ElementKopiec[n + 1];
    for (int i = 1; i <= licznik; i++) {
        noweDane[i] = dane[i];
    }
    delete[] dane;
    dane = noweDane;
    rozmiar = n;
}

int KopiecBinarny::extract_max() {
    if (licznik == 0) throw std::runtime_error("Kolejka jest pusta");

    int maxWartosc = dane[1].wartosc;

    dane[1] = dane[licznik];
    licznik--;

    if (licznik > 0) {
        heapifyDown(1);
    }
    zmniejszRozmiar(); 
    return maxWartosc;
}

int KopiecBinarny::find_max() const {
    if (licznik == 0) throw std::runtime_error("Kolejka jest pusta");
    return dane[1].wartosc;
}

void KopiecBinarny::increase_key(int e, int p) {
    for (int i = 1; i <= licznik; i++) {
        if (dane[i].wartosc == e) {
            // Znaleźliśmy pierwszy (najwcześniejszy w strukturze kopca) element o tej wartości
            if (p > dane[i].priorytet) {
                dane[i].priorytet = p;
                heapifyUp(i);
            }
            return; // ZAWSZE przerywamy po znalezieniu pasującej wartości 'e', nie idziemy dalej!
        }
    }
}

void KopiecBinarny::decrease_key(int e, int p) {
    for (int i = 1; i <= licznik; i++) {
        if (dane[i].wartosc == e) {
            // Znaleźliśmy pierwszy element o tej wartości
            if (p < dane[i].priorytet) {
                dane[i].priorytet = p;
                heapifyDown(i);
            }
            return; // ZAWSZE przerywamy po znalezieniu pasującej wartości 'e'
        }
    }
}

void KopiecBinarny::modify_key(int e, int p) {
    for (int i = 1; i <= licznik; i++) {
        if (dane[i].wartosc == e) {
            int starePrio = dane[i].priorytet;
            dane[i].priorytet = p;
            if (p > starePrio)
                heapifyUp(i);
            else if (p < starePrio)
                heapifyDown(i);
            return;
        }
    }
}

int KopiecBinarny::return_size() const {
    return licznik;
}