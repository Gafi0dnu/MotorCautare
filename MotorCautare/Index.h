#pragma once
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include "Document.h"

class Index {
private:
    std::map<std::string, std::set<std::string>> indexMecanism;
    int nrDocumente = 0;

    std::unordered_set<std::string> stopWords;

    std::string eliminaDiacritice(const std::string& input);
    std::string curataCuvant(const std::string& cuvant);

public:
    Index(); // constructor pentru a inițializa stopWords

    void incarcaDocumenteDinDirector(const std::string& caleDirector);
    void indexeazaDocument(const Document& doc);
    void cautaCuvant(std::string cuvant);
};