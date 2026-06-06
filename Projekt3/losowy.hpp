#ifndef LOSOWY_HPP
#define LOSOWY_HPP
//Bierze rozmiar przed wykonywaniem testów aby mozna bylo losowac priorytet
void ustawRozmiar(int r);

// Losuje jedna z liczb w strukturze
int losujPozycje();

// Losuje wartosc dla insertu, w zakresie int32, aby zapewnić pełną różnorodność wartości
int losujWartosc();
// Losuje klucze dla struktury od 0 do max uint32_t, aby zapewnić pełną różnorodność kluczy
int losujKlucz();
#endif