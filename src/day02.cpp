#include "day02.hpp"

#include <string>

#include "input_utils.hpp"

namespace day02 {

    std::string part_one() {

        std::ifstream in {get_input("day02")};
        std::string line;
        int score {0};
        while (std::getline(in, line)) {

            if (line == "A X") {
                score += 1; // We chose rock
                score += 3; // Draw
            } else if (line == "A Y") {
                score += 2; // We chose paper
                score += 6; // Win
            } else if (line == "A Z") {
                score += 3; // We chose scissors
                score += 0; // Loss
            } else if (line == "B X") {
                score += 1; // We chose rock
                score += 0; // Loss
            } else if (line == "B Y") {
                score += 2; // We chose paper
                score += 3; // Draw
            } else if (line == "B Z") {
                score += 3; // We chose scissors
                score += 6; // Win
            } else if (line == "C X") {
                score += 1; // We chose rock
                score += 6; // Win
            } else if (line == "C Y") {
                score += 2; // We chose paper
                score += 0; // Loss
            } else if (line == "C Z") {
                score += 3; // We chose scissors
                score += 3; // Draw
            } else {
                throw std::runtime_error {"Invalid input line " + line};
            }

        }
        return std::to_string(score);
    }

    std::string part_two() {

        std::ifstream in {get_input("day02")};
        std::string line;
        int score {0};
        while (std::getline(in, line)) {

            if (line == "A X") {
                score += 3; // We chose scissors
                score += 0; // Loss
            } else if (line == "A Y") {
                score += 1; // We chose rock
                score += 3; // Draw
            } else if (line == "A Z") {
                score += 2; // We choose paper
                score += 6; // Win
            } else if (line == "B X") {
                score += 1; // We chose rock
                score += 0; // Loss
            } else if (line == "B Y") {
                score += 2; // We chose paper
                score += 3; // Draw
            } else if (line == "B Z") {
                score += 3; // We chose scissors
                score += 6; // Win
            } else if (line == "C X") {
                score += 2; // We chose paper
                score += 0; // Loss
            } else if (line == "C Y") {
                score += 3; // We chose scissors
                score += 3; // Draw
            } else if (line == "C Z") {
                score += 1; // We chose rock
                score += 6; // Win
            } else {
                throw std::runtime_error {"Invalid input line " + line};
            }

        }
        return std::to_string(score);
    }

}