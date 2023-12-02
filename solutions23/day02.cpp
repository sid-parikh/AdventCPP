#include "days.hpp"
#include <string>
#include "input_utils.hpp"
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <iostream>

namespace day02 {

    struct Round {
        int red{};
        int blue{};
        int green{};
    };

    struct Game {
        int id{};
        std::vector<Round> rounds;
    };

    // Debug
//    std::string to_string(const Game& g) {
//        std::ostringstream stream{};
//
//        stream << g.id << ": ";
//
//        for (const Round& s: g.rounds) {
//            stream << '\n' << s.red << ' ' << s.green << ' ' << s.blue;
//        }
//
//        return stream.str();
//    }

    std::vector<Game> build_games() {

        std::ifstream input = get_input("day02");

        std::string line;
        std::vector<Game> games{};
        while (std::getline(input, line)) {
            Game game;
            game.id = stoi(line.substr(5, line.find(':') - 5));
            std::vector<std::string> split_rounds = split(line.substr(line.find(':') + 1), ';');

            for (const std::string& s: split_rounds) {
                Round round;
                std::vector<std::string> colors = split(s, ',');
                for (const auto& color: colors) {
                    switch (color.back()) {
                        case 'd':
                            // Red
                            round.red = stoi(color.substr(1, color.size() - 5));
                            break;
                        case 'e':
                            // Blue
                            round.blue = stoi(color.substr(1, color.size() - 6));
                            break;
                        case 'n':
                            // Green
                            round.green = stoi(color.substr(1, color.size() - 7));
                            break;
                    }
                }
                game.rounds.push_back(round);
            }
            games.push_back(game);
        }

        return games;
    }

    bool is_possible(const Game& game) {
        return std::ranges::all_of(game.rounds.cbegin(), game.rounds.cend(), [&](const Round& round) {
            return (round.red <= 12 && round.green <= 13 && round.blue <= 14);
        });
    }

    int power(const Game& game) {

        // Get largest red, blue, and green from rounds
        int r = std::ranges::max(game.rounds | std::views::transform(&Round::red));
        int b = std::ranges::max(game.rounds | std::views::transform(&Round::blue));
        int g = std::ranges::max(game.rounds | std::views::transform(&Round::green));

        return r * b * g;
    }

    std::string part_one() {
        auto games = build_games();

        int sum = 0;
        for (const Game& game : games) {
            if (is_possible(game)) {
                sum += game.id;
            }
        }

        return std::to_string(sum);
    }

    std::string part_two() {
        // Get input
        auto games = build_games();

        // Lazy-transform each game into its calculated "power"
        // views::common provides backwards-compatibility for reduce/accumulate
        auto powers = games | std::views::transform(power) | std::views::common;
        // Sum the powers
        auto total = std::reduce(powers.begin(), powers.end());

        return std::to_string(total);
    }
}
