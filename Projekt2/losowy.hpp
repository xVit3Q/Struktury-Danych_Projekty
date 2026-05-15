#ifndef LOSOWY_HPP
#define LOSOWY_HPP
//Bierze rozmiar przed wykonywaniem testów aby mozna bylo losowac priorytet
void ustawRozmiar(int r);


// Losuje jedna z liczb w strukturze
int losujPozycje();

// Losuje priorytet dla struktury -> Priorytwtów jest 2*size
int losujPriorytet();
//Losuje priorytet dla decrease key aby nie wsyzedł ponizej 0
int losujNizszyPriorytet(int a);
#endif