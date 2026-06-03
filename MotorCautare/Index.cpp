#include "Index.h"
#include "Culori.h"
#include "UI.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

Index::Index() {
    stopWords = {
        "si", "sau", "un", "o", "la", "de", "cu",
        "in", "pe", "din", "spre", "prin", "care",
        "ce", "ca", "sa", "se", "nu", "ma", "te",
        "el", "ea", "ei", "ale", "al", "ai", "a",
        "i", "ii", "le", "li", "ne", "va", "vi"
    };
}

std::string Index::eliminaDiacritice(const std::string& input) {
    std::string rezultat;
    rezultat.reserve(input.size());

    for (size_t i = 0; i < input.size(); ) {
        unsigned char c1 = static_cast<unsigned char>(input[i]);

        if (c1 >= 0xC0 && c1 <= 0xDF && i + 1 < input.size()) {
            unsigned char c2 = static_cast<unsigned char>(input[i + 1]);
            uint16_t codepoint = ((c1 & 0x1F) << 6) | (c2 & 0x3F);

            switch (codepoint) {
            case 0x0103: case 0x0102:
            case 0x00E2: case 0x00C2:
                rezultat += 'a'; i += 2; continue;
            case 0x00EE: case 0x00CE:
                rezultat += 'i'; i += 2; continue;
            case 0x0219: case 0x0218:
            case 0x015F: case 0x015E:
                rezultat += 's'; i += 2; continue;
            case 0x021B: case 0x021A:
            case 0x0163: case 0x0162:
                rezultat += 't'; i += 2; continue;
            default:
                i += 2; continue;
            }
        }

        rezultat += input[i];
        i++;
    }
    return rezultat;
}

std::string Index::curataCuvant(const std::string& cuvant) {
    std::string faraDiacritice = eliminaDiacritice(cuvant);
    std::string rezultat;
    for (char c : faraDiacritice) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (std::isalnum(uc))
            rezultat += std::tolower(uc);
    }
    return rezultat;
}

void Index::incarcaDocumenteDinDirector(const std::string& caleDirector) {
    if (!fs::exists(caleDirector) || !fs::is_directory(caleDirector)) {
        afiseazaEroare("Directorul nu exista sau nu este accesibil!");
        return;
    }

    std::cout << "\n";
    afiseazaInfo("Scanez directorul: " + Culori::ALB_BOLD + caleDirector + Culori::RESET);
    afiseazaSeparator();

    int nrFisiere = 0;
    for (const auto& entry : fs::directory_iterator(caleDirector)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream fisier(entry.path());
            if (fisier.is_open()) {
                std::string continut((std::istreambuf_iterator<char>(fisier)),
                    std::istreambuf_iterator<char>());

                std::cout << Culori::GRI << "  -> " << Culori::RESET
                    << entry.path().filename().string()
                    << Culori::GRI << "  (" << continut.size() << " bytes)\n"
                    << Culori::RESET;

                Document doc(entry.path().string(), continut);
                indexeazaDocument(doc);
                nrFisiere++;
                fisier.close();
            }
        }
    }

    afiseazaSeparator();

    if (nrFisiere == 0) {
        afiseazaEroare("Nu s-au gasit fisiere .txt in director.");
        return;
    }

    std::cout << "\n";
    afiseazaSucces("Indexare finalizata!");
    std::cout << Culori::GRI << " Documente indexate : "
        << Culori::ALB_BOLD << nrFisiere << "\n" << Culori::RESET;
    std::cout << Culori::GRI << " Cuvinte unice      : "
        << Culori::ALB_BOLD << indexMecanism.size() << "\n" << Culori::RESET;
    std::cout << "\n";
}

void Index::indexeazaDocument(const Document& doc) {
    std::stringstream ss(doc.continut);
    std::string cuvant;
    nrDocumente++;
    while (ss >> cuvant) {
        std::string cuvantCurat = curataCuvant(cuvant);
        if (cuvantCurat.empty()) continue;
        if (stopWords.count(cuvantCurat)) continue;
        indexMecanism[cuvantCurat].insert(doc.caleFisier);
    }
}

void Index::cautaCuvant(std::string cuvant) {
    cuvant = curataCuvant(cuvant);

    std::cout << "\n";
    afiseazaSeparator();
    std::cout << Culori::CYAN_BOLD << "  Cautare: " << Culori::ALB_BOLD
        << "\"" << cuvant << "\"" << Culori::RESET << "\n";
    afiseazaSeparator();

    std::map<std::string, std::set<std::string>> potriviri;

    for (const auto& [cheie, fisiere] : indexMecanism) {
        if (cheie.find(cuvant) != std::string::npos) {
            for (const auto& cale : fisiere) {
                potriviri[cale].insert(cheie);
            }
        }
    }

    if (potriviri.empty()) {
        afiseazaEroare("Niciun rezultat gasit pentru \"" + cuvant + "\".");
    }
    else {
        std::cout << Culori::VERDE << "  " << potriviri.size()
            << " document(e) gasite:\n\n" << Culori::RESET;

        int idx = 1;
        for (const auto& [cale, cuvinteGasite] : potriviri) {
            std::string numeFisier = fs::path(cale).filename().string();

            std::cout << Culori::GALBEN_BOLD << "  [" << idx++ << "] "
                << Culori::ALB_BOLD << numeFisier << Culori::RESET << "\n";
            std::cout << Culori::GRI << "      " << cale << "\n" << Culori::RESET;

            std::cout << "      ";
            bool primul = true;
            for (const auto& cv : cuvinteGasite) {
                if (!primul) std::cout << Culori::GRI << " · " << Culori::RESET;
                std::cout << Culori::VERDE << cv << Culori::RESET;
                primul = false;
            }
            std::cout << "\n\n";
        }
    }

    afiseazaSeparator();
}