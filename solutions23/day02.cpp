#include "days.hpp"
#include <string>
#include "input_utils.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>

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
    std::string to_string(const Game& g) {
        std::ostringstream stream{};

        stream << g.id << ": ";

        for (const Round& s: g.rounds) {
            stream << '\n' << s.red << ' ' << s.green << ' ' << s.blue;
        }

        return stream.str();
    }

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
                            round.blue = stoi(color.substr(1, color.size() - 6));
                            break;
                        case 'n':
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

    bool is_possible(const Game& game, int r, int g, int b) {
        return std::ranges::all_of(game.rounds.cbegin(), game.rounds.cend(), [&](const Round& round) {
            return (round.red <= r && round.blue <= b && round.green <= g);
        });
    }

    int power(const Game& game) {

        int r = std::ranges::max(game.rounds, {}, [](const Round& r) {
            return r.red;
        }).red;

        int b = std::ranges::max(game.rounds, {}, [](const Round& r) {
            return r.blue;
        }).blue;

        int g = std::ranges::max(game.rounds, {}, [](const Round& r) {
            return r.green;
        }).green;

        return r * b * g;
    }

    std::string part_one() {
        auto games = build_games();
        int sum = 0;
        for (const Game& g: games) {
            if (is_possible(g, 12, 13, 14)) {
                sum += g.id;
            }
        }
        return std::to_string(sum);
    }

    std::string part_two() {
        auto games = build_games();

        int total = std::accumulate(games.begin(), games.end(), 0, [](int sum, const Game& g){
            return sum + power(g);
        });

        return std::to_string(total);
    }
}
