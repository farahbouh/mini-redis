#include "serveur/serveur.hpp"

Serveur::Serveur() {
    this->port = 8080; // Port par défaut
    this->allume = false;
}

Serveur::Serveur(int p) {
    this->port = p;
    this->allume = false;
}

Serveur::~Serveur() {}

void Serveur::allumer() {
    this->allume = true;
}

void Serveur::eteindre() {
    this->allume = false;
}

void Serveur::ajoutercli(Client c) {
    if (this->allume) {
        this->clients.push_back(c);
    }
}

void Serveur::supprimercli(Client c) {
    if (this->allume) {
        for (size_t i = 0; i < clients.size(); i++) {
            if (clients[i].getId() == c.getId()) {
                clients.erase(clients.begin() + i);
                return;
            }
        }
    }
}