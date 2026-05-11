#pragma once
#include <string>

// Typy struktur dostępnych w menu
enum StructureType {
    KolejkaTablicowa = 1,
    KopiecBinarnyTyp = 2
};

StructureType showMainMenu(int& count);
int showOperationsMenu();