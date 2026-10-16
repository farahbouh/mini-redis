#include <iostream>
#include <string>
#include <vector>
#include "protocole/analyseur.hpp"

// Lance traiter sur une trame et compare avec le resultat attendu
static int verifier(Analyseur& a, const std::string& nom,
                    const std::vector<std::string>& trame, bool attendu)
{
    bool obtenu = a.traiter(trame);
    bool ok = (obtenu == attendu);
    std::cout << (ok ? "[OK]   " : "[ECHEC] ") << nom
              << " (attendu=" << attendu << ", obtenu=" << obtenu << ")\n"
              << std::endl;
    return ok ? 0 : 1;
}

int main()
{
    Analyseur a;
    int echecs = 0;

    // Cas valides
    echecs += verifier(a, "SET a 1 (minuscules)",   {"set", "a", "1"}, true);
    echecs += verifier(a, "Get a (casse mixte)",    {"Get", "a"},      true);
    echecs += verifier(a, "DEL a",                  {"DEL", "a"},      true);

    // Cas invalides
    echecs += verifier(a, "SET a (valeur manquante)", {"SET", "a"},               false);
    echecs += verifier(a, "GET a b c (trop long)",    {"GET", "a", "b", "c"},     false);
    echecs += verifier(a, "DEL a b (trop long)",      {"DEL", "a", "b"},          false);
    echecs += verifier(a, "HELLO (commande inconnue)", {"HELLO"},                 false);
    echecs += verifier(a, "trame vide",               {},                         false);

    if (echecs == 0)
        std::cout << "Tous les tests passent." << std::endl;
    else
        std::cout << echecs << " test(s) en echec." << std::endl;

    return echecs;
}
