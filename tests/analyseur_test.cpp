#include <iostream>
#include <string>
#include <vector>
#include "protocole/analyseur.hpp"

// traiter : compare la validite et la commande normalisee
static int verifier(Analyseur& a, const std::string& nom,
                    const std::vector<std::string>& trame,
                    bool valide_attendu, const std::string& commande_attendue)
{
    Requete r = a.traiter(trame);
    bool ok = (r.valide == valide_attendu) && (r.commande == commande_attendue);
    std::cout << (ok ? "[OK]    " : "[ECHEC] ") << nom
              << " (valide=" << r.valide << ", commande=\"" << r.commande << "\")\n"
              << std::endl;
    return ok ? 0 : 1;
}

// decouper : compare le contenu du tableau
static int verifier_decoupage(Analyseur& a, const std::string& nom,
                              const std::string& ligne,
                              const std::vector<std::string>& attendu)
{
    std::vector<std::string> obtenu = a.decouper(ligne);
    bool ok = (obtenu == attendu);
    std::cout << (ok ? "[OK]    " : "[ECHEC] ") << "decouper : " << nom
              << " (" << obtenu.size() << " mot(s))\n" << std::endl;
    return ok ? 0 : 1;
}

int main()
{
    Analyseur a;
    int echecs = 0;

    // traiter : cas valides (la commande doit ressortir en majuscules)
    echecs += verifier(a, "SET a 1 (minuscules)", {"set", "a", "1"}, true, "SET");
    echecs += verifier(a, "Get a (casse mixte)",  {"Get", "a"},      true, "GET");
    echecs += verifier(a, "DEL a",                {"DEL", "a"},      true, "DEL");

    // traiter : cas invalides (commande vide)
    echecs += verifier(a, "SET a (valeur manquante)",  {"SET", "a"},           false, "");
    echecs += verifier(a, "GET a b c (trop long)",     {"GET", "a", "b", "c"}, false, "");
    echecs += verifier(a, "DEL a b (trop long)",       {"DEL", "a", "b"},      false, "");
    echecs += verifier(a, "HELLO (commande inconnue)", {"HELLO"},              false, "");
    echecs += verifier(a, "trame vide",                {},                     false, "");

    // decouper
    echecs += verifier_decoupage(a, "mots simples",      "set a 1",     {"set", "a", "1"});
    echecs += verifier_decoupage(a, "espaces multiples", "set   a   1", {"set", "a", "1"});
    echecs += verifier_decoupage(a, "espaces autour",    "  get a  ",   {"get", "a"});
    echecs += verifier_decoupage(a, "ligne vide",        "",            {});
    echecs += verifier_decoupage(a, "que des espaces",   "   ",         {});
    echecs += verifier_decoupage(a, "fin de ligne nc", "get a\r\n", {"get", "a"});
    
    // extraire_lignes
    std::string t1 = "set a 1\nget a\n";
    auto l1 = a.extraire_lignes(t1);
    echecs += (l1 == std::vector<std::string>{"set a 1", "get a"} && t1.empty()) ? 0 : 1;

    std::string t2 = "set a 1\nge";
    auto l2 = a.extraire_lignes(t2);
    echecs += (l2 == std::vector<std::string>{"set a 1"} && t2 == "ge") ? 0 : 1;

    std::string t3 = "ge";
    auto l3 = a.extraire_lignes(t3);
    echecs += (l3.empty() && t3 == "ge") ? 0 : 1;
    
    if (echecs == 0)
        std::cout << "Tous les tests passent." << std::endl;
    else
        std::cout << echecs << " test(s) en echec." << std::endl;

    return echecs;
}