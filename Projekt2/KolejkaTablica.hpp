#ifndef KOLEJKA_TABLICA_HPP
#define KOLEJKA_TABLICA_HPP

struct Element{
    int wartosc;
    int priorytet;
    long long kolejnosc;
    Element():wartosc(0),priorytet(0),kolejnosc(0){}
    Element(int e, int p, long long k):wartosc(e),priorytet(p),kolejnosc(k){}
};

class KolejkaTablica{
private:
    Element* dane;
    int licznik;
    int rozmiar;
    long long licznikKolejki;

    void zwiekszRozmiar();
    void zmniejszRozmiar(); 
    int znajdzIndeksMax() const;
public:
    KolejkaTablica();
    ~KolejkaTablica();
    KolejkaTablica(const KolejkaTablica& other);
    KolejkaTablica& operator=(const KolejkaTablica& other);
    void insert(int e, int p);
    int extract_max();
    int find_max() const;
    void modify_key(int e, int p);
    void increase_key(int e, int p);
    void decrease_key(int e, int p);
    int return_size() const;
};
#endif