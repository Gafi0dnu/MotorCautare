#include "UI.h"
#include "Culori.h"
#include <iostream>

void afiseazaBanner() {
    std::cout << Culori::VERDE_BOLD;
    std::cout << "\n";
    std::cout << "  ========================================\n";
    std::cout << "  |        MOTOR DE CAUTARE v2.0         |\n";
    std::cout << "  |     Indexare documente text (.txt)   |\n";
    std::cout << "  ========================================\n";
    std::cout << Culori::RESET << "\n";
}

void afiseazaSeparator() {
    std::cout << Culori::GRI << "  -------------------------------------\n" << Culori::RESET;
}

void afiseazaEroare(const std::string& mesaj) {
    std::cout << Culori::ROSU << "  X " << Culori::RESET << mesaj << "\n";
}

void afiseazaSucces(const std::string& mesaj) {
    std::cout << Culori::VERDE << "  V " << Culori::RESET << mesaj << "\n";
}

void afiseazaInfo(const std::string& mesaj) {
    std::cout << Culori::CYAN << "  I " << Culori::RESET << mesaj << "\n";
}