#include  <vector>
#include <string>


class Store
{ 
    private:
        std::vector<std::pair<std::string, std::string>> BD;

    public:
        Store();
        ~Store();

        void mettre(std::string key, std::string v);
        std::string recuperer(std::string clee);
        void supprimer(std::string clee);
};