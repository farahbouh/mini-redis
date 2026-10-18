#include "serveur/serveur.hpp"
#include <iostream>       
#include <stdexcept>       
#include <sys/socket.h>    
#include <netinet/in.h>   
#include <unistd.h>    

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

std::string Serveur::executer(const std::string& commande_cli)
{
    std::vector<std::string> trame=analyseur.decouper(commande_cli);
    Requete requete = analyseur.traiter(trame);
    if (!requete.valide) {
        return "ERREUR";
    }
    if (requete.commande == "SET") {
        stockeur.mettre(requete.trame[1], requete.trame[2]);
        return "OK";
    }
    else if (requete.commande == "GET") {
        try {
            return stockeur.recuperer(requete.trame[1]);
        } catch (const std::exception&) {
            return "ERREUR cle inconnue";
        }
    }
    else { 
        stockeur.supprimer(requete.trame[1]);
        return "OK";
    }
}
void Serveur::lancer()
{
    int fd_ecoute = socket(AF_INET, SOCK_STREAM, 0); // création du socket

    int oui = 1;
    setsockopt(fd_ecoute, SOL_SOCKET, SO_REUSEADDR, &oui, sizeof(oui)); 

    sockaddr_in adresse{}; // préparer l'adresse du serveur
    adresse.sin_family = AF_INET; // famille d'adresses (IPv4)
    adresse.sin_addr.s_addr = INADDR_ANY; // accepter les connexions de n'importe quelle adresse
    adresse.sin_port = htons(port);     // convertir le port en format réseau     

    bind(fd_ecoute, (sockaddr*)&adresse, sizeof(adresse)); // lier le socket à l'adresse et au port
    listen(fd_ecoute, 5);                               // mettre le socket en mode écoute (5 connexions en file d'attente)
    std::cout << "En attente sur le port " << port << std::endl;

    int fd_client = accept(fd_ecoute, nullptr, nullptr);  // accepter une connexion entrante 
    char tampon[1024];
    while (true) {
        ssize_t n = recv(fd_client, tampon, sizeof(tampon), 0); // recevoir des données du client
        
        if (n > 0) {
            std::string ligne(tampon, n);
            std::cout << "Recu : " << ligne;

            std::string reponse = executer(ligne);   // le serveur appelle sa propre méthode
            reponse += "\n";

            if (send(fd_client, reponse.c_str(), reponse.size(), 0) < 0) {
                perror("send");
            }
        }
    }
        close(fd_client); // fermer la connexion avec le client
    close(fd_ecoute); // fermer le socket d'écoute
}