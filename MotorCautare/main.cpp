// main.cpp
#include "UI.h"
#include "Index.h"
#include "Culori.h"
#include <iostream>
#include <string>

int main() {
    afiseazaBanner();

    Index motorCautare;
    std::string caleDirector;

    std::cout << Culori::CYAN << "  Director documente: " << Culori::RESET;
    std::getline(std::cin, caleDirector);

    motorCautare.incarcaDocumenteDinDirector(caleDirector);

    std::string cuvantCautat;
    while (true) {
        std::cout << Culori::CYAN << "\n  Cauta" << Culori::GRI
            << " (sau 'iesire')" << Culori::CYAN << ": " << Culori::RESET;
        std::cin >> cuvantCautat;

        if (cuvantCautat == "iesire") {
            std::cout << "\n";
            afiseazaInfo("La revedere!\n");
            break;
        }

        motorCautare.cautaCuvant(cuvantCautat);
    }

    return 0;
}