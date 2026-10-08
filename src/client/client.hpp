#include <string>
#include <vector>


class Client {
   private:
        int id;
        int port;
    public:
        bool estesntligne;
        Client();
        ~Client();

        void connecter();
        void deconnecter();
        void envoyer(std::string message);
        bool recevoir();
};