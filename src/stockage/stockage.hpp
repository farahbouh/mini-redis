#include  <vector>
#include <string>

#pragma once
class Stockage
{ 
    private:
        std::vector<std::pair<std::string, std::string>> BD;

    public:
        Stockage();
        ~Stockage();

        void mettre(std::string key, std::string v);
        std::string recuperer(std::string clee);
        void supprimer(std::string clee);
};