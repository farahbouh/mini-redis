#include <string>
#include <vector>
#pragma once

class Analyseur {
    public:

        Analyseur();
        ~Analyseur();

        std::vector<std::string> traiter(std::string m);
};