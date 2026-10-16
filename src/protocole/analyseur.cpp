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

bool Analyseur::traiter(const std::vector<std::string>& trame) {
    if (trame.empty()) {
        std::cout << "trame vide" << std::endl;
        return false;
    }

    std::string mot = trame[0];
    for (size_t i = 0; i < mot.size(); i++) {
        mot[i] = std::toupper(static_cast<unsigned char>(mot[i]));
    }

    if (mot == "SET") {
        if (trame.size() != 3) {
            std::cout << "SET attend 3 elements" << std::endl;
            return false;
        }
        std::cout << "set" << std::endl;
    }
    else if (mot == "GET") {
        if (trame.size() != 2) {
            std::cout << "GET attend 2 elements" << std::endl;
            return false;
        }
        std::cout << "get" << std::endl;
    }
    else if (mot == "DEL") {
        if (trame.size() != 2) {
            std::cout << "DEL attend 2 elements" << std::endl;
            return false;
        }
        std::cout << "del" << std::endl;
    }
    else {
        std::cout << "commande non reconnue" << std::endl;
        return false;
    }

    return true;
}