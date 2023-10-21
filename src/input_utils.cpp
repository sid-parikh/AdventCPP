#include "input_utils.hpp"

#include <fstream>

std::ifstream get_input(const std::string &day) {
    std::ifstream input("/Users/sidparikh/CLionProjects/AdventCPP/input/" + day);

    if (!input) {
        throw std::runtime_error{"Could not find input file named " + day};
    }

    return input;
}
