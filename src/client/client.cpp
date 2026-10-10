#include "client/client.hpp"

Client::Client() : id(0), port(8080), estenligne(false) {}

Client::Client(int id) : id(id), port(8080), estenligne(false) {}

Client::~Client() {}

void Client::connecter(int p)
{
    this->port = p;
    this->estenligne = true;
}

void Client::deconnecter()
{
    this->estenligne = false;
}

void Client::envoyer(std::string /*message*/)
{
}

bool Client::recevoir()
{
    return true;
}