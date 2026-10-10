#pragma once
#include <vector>
#include "client/client.hpp"

class Serveur {
    public:
        int port;
        bool allume;
        Serveur();
        Serveur(int p);
        ~Serveur();

        void allumer();
        void eteindre();
        void ajoutercli(Client c);
        void supprimercli(Client c);
    private:
        std::vector<Client> clients;
};