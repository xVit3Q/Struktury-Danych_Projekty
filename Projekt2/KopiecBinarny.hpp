
#ifndef KOLEJKA_KOPIEC_HPP
#define KOLEJKA_KOPIEC_HPP

struct ElementKopiec {
    int wartosc;
    int priorytet;
    long long kolejnosc;
    ElementKopiec() : wartosc(0), priorytet(0), kolejnosc(0) {}
    ElementKopiec(int e, int p, long long k) : wartosc(e), priorytet(p), kolejnosc(k) {}
};

class KopiecBinarny {
private:
    ElementKopiec* dane;
    int licznik;
    int rozmiar;
    long long licznikKolejki;

    void zwiekszRozmiar();
    void zmniejszRozmiar();

    // Indeksy węzłów w kopcu (tablica indeksowana od 1)
    int rodzic(int i) const;
    int leweDziecko(int i) const;
    int praweDziecko(int i) const;

    //Jesli dwa elemnety o tyym samym kluczu to ten co byl pierwszy dodany ma priorytet fifo
    bool maNadrzednyPriorytet(int i, int j) const;

    void heapifyUp(int i);    // przywraca własność kopca od i w górę
    void heapifyDown(int i);     // przywraca własność kopca od i w dół

public:
    KopiecBinarny();
    ~KopiecBinarny();
    KopiecBinarny(const KopiecBinarny& other);
    KopiecBinarny& operator=(const KopiecBinarny& other);

    void insert(int e, int p);
    void reserve(int n);
    int extract_max();
    int find_max() const;
    void modify_key(int e, int p);
    void increase_key(int e, int p);
    void decrease_key(int e, int p);
    int return_size() const;
};

#endif