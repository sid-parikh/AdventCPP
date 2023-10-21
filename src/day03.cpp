#include "day03.hpp"

#include "input_utils.hpp"

#include <fstream>
#include <string>

namespace day03 {

    int idx(const char& c) {
        if (c >= 'a') {
            return c - 'a';
        } else {
            return 26 + c - 'A';
        }
    }

    std::string part_one() {
        std::ifstream in = get_input("day03");
        std::string line;

        int total = 0;

        while (std::getline(in, line)) {

            // Divided into two equal sack compartments
            std::size_t sack_sz {line.size() / 2};

            // Conveniently, index is one less than priority
            // lowercase first, uppercase second
            std::array<bool, 52> seen {};

            for (std::size_t i = 0; i < sack_sz; ++i) {
                const char& c = line[i];
                seen[idx(c)] = true;
            }

            int priority = 0;
            // Sum priorities for all items seen in both
            for (std::size_t i = sack_sz; i < line.size(); ++i) {
                const int index = idx(line[i]);
                if (seen[index]) {
                    priority += index + 1;
                    // Don't count this again
                    seen[index] = false;
                }
            }

            // Add for all elves
            total += priority;
        }

        return std::to_string(total);
    }

    std::string part_two() {
        std::ifstream in = get_input("day03");

        int total = 0;
        while (in) {
            // Get first three elves
            std::string one;
            std::string two;
            std::string three;

            in >> one;
            in >> two;
            in >> three;

            // Seen table for first two strings
            std::array<bool, 52> count {};
            std::array<bool, 52> count_2 {};
            for (const char& c : one) {
                count[idx(c)] = true;
            }
            for (const char& c : two) {
                count_2[idx(c)] = true;
            }

            // If in all three, add its priority
            for (const char& c : three) {
                int i = idx(c);
                if (count[i] && count_2[i]) {
                    total += i + 1;
                    break;
                }
            }
        }

        return std::to_string(total);
    }
}
