#pragma once
#include <vector>
#include "client/client.hpp"
#include "stockage/stockage.hpp"
#include "protocole/analyseur.hpp"

class Serveur {
    public:
        int port;
        bool allume;

        Stockage stockeur;
        Analyseur analyseur;

        Serveur();
        Serveur(int p);
        ~Serveur();

        void allumer();
        void eteindre();
        void ajoutercli(Client c);
        void supprimercli(Client c);

        std::string executer(const std::string& commande_cli);
        void lancer();

    private:
        std::vector<Client> clients;
};