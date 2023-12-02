#include <fstream>
#include <string>
#include <vector>
#include <sstream>
std::ifstream get_input(const std::string &day) {
    std::ifstream input("/Users/sidparikh/CLionProjects/AdventCPP/solutions23/input/" + day);

    if (!input) {
        throw std::runtime_error{"Could not find input file named " + day};
    }

    return input;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::istringstream iss {s};
    std::string token;
    std::vector<std::string> out {};
    while (std::getline(iss, token, delim))
    {
        out.push_back(token);
    }
    return out;
}
