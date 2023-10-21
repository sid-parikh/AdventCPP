#include "day04.hpp"
#include "input_utils.hpp"

#include <string>
#include <fstream>
#include <iostream>

namespace day04 {

    /**
     * Each elf is assigned a range [start, last]
     */
    struct elf_pair {
        std::pair<int, int> elf1;
        std::pair<int, int> elf2;
    };

    std::vector<elf_pair> get_elves() {
        std::ifstream in = get_input("day04");

        std::vector<elf_pair> out{};

        while (in.good()) {
            elf_pair curr_elf{};
            char c;
            in >> curr_elf.elf1.first;
            in >> c; // Skip hyphen
            in >> curr_elf.elf1.second;
            in >> c; // Skip comma
            in >> curr_elf.elf2.first;
            in >> c; // Skip hyphen
            in >> curr_elf.elf2.second;
            out.push_back(curr_elf);
        }

        return out;
    }

    std::string part_one() {
        std::vector<elf_pair> elves = get_elves();

        int count = 0;
        for (auto &pair: elves) {
            // If either the first contains the second or the second contains the first
            if ((pair.elf1.first <= pair.elf2.first && pair.elf1.second >= pair.elf2.second)
                || (pair.elf2.first <= pair.elf1.first && pair.elf2.second >= pair.elf1.second)) {
                ++count;
            }
        }
        return std::to_string(count);
    }

    std::string part_two() {
        std::vector<elf_pair> elves = get_elves();

        int count = 0;
        for (auto &pair: elves) {
            // If they overlap at all
            if ((pair.elf1.first <= pair.elf2.first && pair.elf1.second >= pair.elf2.first)
            ||(pair.elf2.first <= pair.elf1.first && pair.elf2.second >= pair.elf1.first)) {
                ++count;
            }

        }
        return std::to_string(count);
    }
} // namespace day04