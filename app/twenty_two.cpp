#include <iostream>

#include "day01.hpp"
#include "day02.hpp"

void print_results(const std::string &day, const std::string &part_one, const std::string &part_two) {
    std::cout << "Day " << day << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Part One: " << part_one << std::endl;
    std::cout << "Part Two: " << part_two << std::endl << std::endl;
}

int main() {
    print_results("One", day01::part_one(), day01::part_two());
    print_results("Two", day02::part_one(), day02::part_two());
}