#pragma once
#include <string>
#include <vector>

struct Requete {
    bool valide;
    std::string commande;   // "SET", "GET", "DEL"
    std::vector<std::string> trame;
};

class Analyseur {
    public:

        Analyseur();
        ~Analyseur();
        Requete traiter(const std::vector<std::string>& trame);
        std::vector<std::string> decouper(const std::string& ligne);
};