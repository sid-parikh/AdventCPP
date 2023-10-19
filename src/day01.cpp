#include "day01.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "input_utils.hpp"

namespace day01 {
    std::vector<int> get_elves() {

        std::ifstream input = get_input("day01");

        int curr{0};
        std::string line;
        std::vector<int> out{};
        while (std::getline(input, line)) {
            if (line.empty()) {
                out.push_back(curr);
                curr = 0;
            } else {
                curr += std::stoi(line);
            }
        }

        return out;
    }

    std::string part_two() {
        std::vector<int> elves = get_elves();

        // Print out largest elf
        return std::to_string(*std::max_element(elves.begin(), elves.end()));
    }

    std::string part_one() {
        std::vector<int> elves = get_elves();

        // Get top 3 elements
        std::partial_sort(elves.begin(), elves.begin() + 3, elves.end(), std::greater<>{});

        // Print out sum of top 3 elves
        return std::to_string(elves[0] + elves[1] + elves[2]);
    }
}
