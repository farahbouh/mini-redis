#include <iostream>
#include "stockage/stockage.hpp"

int main()
{
    Stockage s;

    // Test 1 : mettre puis recuperer
    s.mettre("clee1", "valeur1");
    std::cout << s.recuperer("clee1") << std::endl;

    // Test 2 : remplacement (ecraser une cle existante)
    s.mettre("clee1", "valeur2");
    std::cout << s.recuperer("clee1") << std::endl;

    // Test 3 : suppression puis recuperation
    s.supprimer("clee1");
    try {
        std::cout << s.recuperer("clee1") << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Test 4 : deux cles independantes, supprimer a ne touche pas b
    s.mettre("a", "valeurA");
    s.mettre("b", "valeurB");
    s.supprimer("a");
    std::cout << s.recuperer("b") << std::endl;

    return 0;
}