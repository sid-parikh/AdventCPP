#include "days.hpp"
#include <ranges>
#include <string>
#include "input_utils.hpp"
#include <iostream>

namespace day01 {
    std::string part_one() {
        std::ifstream input = get_input("day01");

        std::string line;
        int sum = 0;
        while (std::getline(input, line)) {
            // First digit
            int num = 0;
            for (const char& c: line) {
                if (c >= '0' && c <= '9') {
                    num += 10 * (c - '0');
                    break;
                }
            }

            // Last digit
            for (const char& c: std::ranges::reverse_view(line)) {
                if (c >= '0' && c <= '9') {
                    num += (c - '0');
                    break;
                }
            }
            sum += num;
        }

        return std::to_string(sum);
    }

    int get_num (std::string_view line, size_t i) {
        constexpr static std::array<std::string_view, 9> nums = {
                "one",
                "two",
                "three",
                "four",
                "five",
                "six",
                "seven",
                "eight",
                "nine"
        };

        for (int n = 0; n < 9; ++n) {
            if (i + nums[n].size() <= line.size() && line.substr(i, nums[n].size()) == nums[n]) {
                return n + 1;
            }
        }

        return -1;
    }
    std::string part_two() {

        std::ifstream input = get_input("day01");
        std::string line;
        int sum = 0;
        while (std::getline(input, line)) {
            int num = 0;
            for (size_t i = 0; i < line.size(); ++i) {
                if (isdigit(line[i])) {
                    num += 10 * (line[i] - '0');
                    break;
                }
                else {
                    int n = get_num(line, i);
                    if (n >= 0) {
                        num += 10 * n;
                        break;
                    }
                }
            }
            for (int i = line.size() - 1; i >= 0; --i) {
                if (isdigit(line[i])) {
                    num += (line[i] - '0');
                    break;
                }
                else {
                    int n = get_num(line, i);
                    if (n >= 0) {
                        num += n;
                        break;
                    }
                }
            }
            sum += num;
            std::cout << num << std::endl;
        }
        return std::to_string(sum);
    }
}
