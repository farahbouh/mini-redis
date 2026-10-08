#include <string>
#include <vector>
#include "client/client.hpp"

class serveur {
    public:
        int port;
        serveur();
        serveur(int p);
        ~serveur();

        void allumer();
        void eteindre();
        void ajoutercli(Client c);
        void supprimercli(Client c);
    private:
        std::vector<std::Client> clients;

};