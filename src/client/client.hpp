#pragma once
#include <string>

class Client {
private:
    int id;
    int port;
public:
    bool estenligne;

    Client();
    Client(int id);
    ~Client();

    int getId() const { return id; }

    void connecter(int p);
    void deconnecter();
    void envoyer(std::string message);
    bool recevoir();
};