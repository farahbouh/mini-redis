#pragma once
#include <string>
#include <vector>


class Analyseur {
    public:

        Analyseur();
        ~Analyseur();
        bool traiter(const std::vector<std::string>& trame);
};