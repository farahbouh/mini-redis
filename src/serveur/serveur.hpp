#pragma once
#include <string>
#include <vector>
#include "client/client.hpp"
#include "stockage/stockage.hpp"
#include "protocole/analyseur.hpp"
#include <atomic> 

class Serveur {
    public:
        int port;
        std::atomic<bool> allume; 
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
        void gerer_client(int fd_client);
        std::mutex mtx_threads;
};