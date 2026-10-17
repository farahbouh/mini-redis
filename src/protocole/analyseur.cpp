#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "protocole/analyseur.hpp"

Analyseur::Analyseur() {
    // Constructeur par défaut
}

Analyseur::~Analyseur() {
    // Destructeur par défaut
}

Requete Analyseur::traiter(const std::vector<std::string>& trame) {
    if (trame.empty()) {
        std::cout << "trame vide" << std::endl;
        return Requete{false, "", {}};
    }

    std::string mot = trame[0];
    for (size_t i = 0; i < mot.size(); i++) {
        mot[i] = std::toupper(static_cast<unsigned char>(mot[i]));
    }

    if (mot == "SET") {
        if (trame.size() != 3) {
            std::cout << "SET attend 3 elements" << std::endl;
            return Requete{false, "", {}};
        }
        std::cout << "set" << std::endl;
    }
    else if (mot == "GET") {
        if (trame.size() != 2) {
            std::cout << "GET attend 2 elements" << std::endl;
            return Requete{false, "", {}};
        }
        std::cout << "get" << std::endl;
    }
    else if (mot == "DEL") {
        if (trame.size() != 2) {
            std::cout << "DEL attend 2 elements" << std::endl;
            return Requete{false, "", {}};
        }
        std::cout << "del" << std::endl;
    }
    else {
        std::cout << "commande non reconnue" << std::endl;
        return Requete{false, "", {}};
    }

    return Requete{true, mot, trame};
}

std::vector<std::string> Analyseur::decouper(const std::string& ligne) {
    std::vector<std::string> trame;
    std::string mot;

    for (char c : ligne) {
        if (c == ' ') {
            // espace = mot est fini
            if (!mot.empty()) {
                trame.push_back(mot);
                mot.clear();
            }
        } else {
            mot += c;   // ajout de la lettre 
        }
    }

    if (!mot.empty()) {          // le dernier mot n'est pas suivi d'un espace
        trame.push_back(mot);
    }
    return trame;
}
    