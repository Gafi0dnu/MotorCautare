#pragma once
#include <string>

class Document {
public:
    std::string caleFisier;
    std::string continut;

    Document(std::string cale, std::string cont)
        : caleFisier(cale), continut(cont) {
    }
};