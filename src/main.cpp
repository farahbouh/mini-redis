#include <iostream>
#include "stockage/stockage.hpp"
#include "serveur/serveur.hpp"

int main()
{
    Serveur s;
    s.allumer();
    s.lancer();
    return 0;
}