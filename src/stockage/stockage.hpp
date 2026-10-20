#pragma once
#include <vector>
#include <string>
#include <mutex>


class Stockage
{ 
    private:
        std::vector<std::pair<std::string, std::string>> BD;
        mutable std::mutex mtx;
    public:
        Stockage();
        ~Stockage();

        void mettre(std::string key, std::string v);
        std::string recuperer(std::string clee);
        void supprimer(std::string clee);
};