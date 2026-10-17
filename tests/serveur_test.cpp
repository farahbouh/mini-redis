#include <iostream>
#include <string>
#include "serveur/serveur.hpp"

// Envoie une ligne au serveur et compare la reponse a celle attendue
static int verifier(Serveur& s, const std::string& ligne, const std::string& attendu)
{
    std::string obtenu = s.executer(ligne);
    bool ok = (obtenu == attendu);
    std::cout << (ok ? "[OK]    " : "[ECHEC] ") << "\"" << ligne << "\""
              << " -> \"" << obtenu << "\""
              << " (attendu \"" << attendu << "\")\n" << std::endl;
    return ok ? 0 : 1;
}

int main()
{
    Serveur s;
    int echecs = 0;

    // Scenario normal
    echecs += verifier(s, "set a 1", "OK");
    echecs += verifier(s, "get a",   "1");

    // Remplacement d'une valeur
    echecs += verifier(s, "set a 2", "OK");
    echecs += verifier(s, "get a",   "2");

    // Casse et espaces multiples
    echecs += verifier(s, "SET   b   hello", "OK");
    echecs += verifier(s, "Get b",           "hello");

    // Suppression : a disparait, b reste
    echecs += verifier(s, "del a", "OK");
    echecs += verifier(s, "get a", "ERREUR cle inconnue");
    echecs += verifier(s, "get b", "hello");

    // Erreurs
    echecs += verifier(s, "hello",   "ERREUR");   // commande inconnue
    echecs += verifier(s, "set a",   "ERREUR");   // valeur manquante
    echecs += verifier(s, "get a b", "ERREUR");   // trop d'arguments
    echecs += verifier(s, "",        "ERREUR");   // ligne vide

    if (echecs == 0)
        std::cout << "Tous les tests passent." << std::endl;
    else
        std::cout << echecs << " test(s) en echec." << std::endl;

    return echecs;
}
