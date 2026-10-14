#include  <vector>
#include <string>
#include <stdexcept>
#include "stockage.hpp"


Stockage::Stockage()
{
    BD.clear();
}
Stockage::~Stockage()
{
    BD.clear();
}

/***************** 
    Parametres: 
    c : clee
    v : valeur
********************/
void Stockage::mettre(std::string c, std::string v)
{
    for (auto &pair : BD) {
        if (pair.first == c) {
            pair.second = v; // Met à jour la valeur si la clé existe déjà
            return;
        }
    }
    BD.push_back(std::make_pair(c, v));
}
std::string Stockage::recuperer(std::string clee)
{
    for (const auto &pair : BD) {
        if (pair.first == clee) {
            return pair.second;
        }
    }
    throw std::runtime_error("clee n'existe pas");
}
void Stockage::supprimer(std::string clee){
    for (auto it = BD.begin(); it != BD.end(); ++it) {
        if (it->first == clee) {
            BD.erase(it);
            return;
        }
    }
}
