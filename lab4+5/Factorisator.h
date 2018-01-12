#pragma once

#include <vector>
#include <iostream>

class Factorisator {
public:
    std::string factorisationFunction(uint64_t number) {
        getFactoristion(number);
        std::string result = std::to_string(number) + " = ";
        return result + getString();
    };
private:
    void getFactoristion(uint64_t number) {
        factorisation.clear();
        uint64_t probe = 2;
        while (number != 1) {
            if (number % probe != 0) {
                probe++;
            } else {
                number /= probe;
                factorisation.push_back(probe);
            }
        }
        std::cout << std::endl;
    };

    const std::string getString() const {
        std::string output;
        for (auto i : factorisation) {
            output += std::to_string(i) + " * ";
        }
        output = output.substr(0, output.length() - 2);
        return output;
    };


    std::vector<uint64_t> factorisation;
};