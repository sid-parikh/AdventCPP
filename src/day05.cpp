#include "day05.hpp"

#include "input_utils.hpp"

#include <string>
#include <stack>
#include <array>
#include <fstream>

namespace day05 {

    /**
     * It is way too much work to parse input programmatically for these stacks
     * @return The input stacks (manually hard-coded)
     */
    std::array<std::stack<char>, 9> make_stacks() {
        std::array<std::stack<char>, 9> out {};
        /*
        [M]             [Z]     [V]
        [Z]     [P]     [L]     [Z] [J]
    [S] [D]     [W]     [W]     [H] [Q]
    [P] [V] [N] [D]     [P]     [C] [V]
    [H] [B] [J] [V] [B] [M]     [N] [P]
    [V] [F] [L] [Z] [C] [S] [P] [S] [G]
    [F] [J] [M] [G] [R] [R] [H] [R] [L]
    [G] [G] [G] [N] [V] [V] [T] [Q] [F]         *
         */

        out[0] = std::stack<char>({'G', 'F', 'V', 'H', 'P', 'S'});
        out[1] = std::stack<char>({'G', 'J', 'F', 'B', 'V', 'D', 'Z', 'M'});
        out[2] = std::stack<char>({'G', 'M', 'L', 'J', 'N'});
        out[3] = std::stack<char>({'N', 'G', 'Z', 'V', 'D', 'W', 'P'});
        out[4] = std::stack<char>({'V', 'R', 'C', 'B'});
        out[5] = std::stack<char>({'V', 'R', 'S', 'M', 'P', 'W', 'L', 'Z'});
        out[6] = std::stack<char>({'T', 'H', 'P'});
        out[7] = std::stack<char>({'Q', 'R', 'S', 'N', 'C', 'H', 'Z', 'V'});
        out[8] = std::stack<char>({'F', 'L', 'G', 'P', 'V', 'Q', 'J'});
        return out;
    }

    std::string part_one() {
        std::array<std::stack<char>, 9> stacks = make_stacks();
        std::ifstream input = get_input("day05");

        while (input.good()) {
            int amount;
            int from;
            int to;
            std::string ignore;
            input >> ignore; // "move"
            input >> amount;
            input >> ignore; // "from"
            input >> from;
            input >> ignore; // "to"
            input >> to;

            // 0-indexing
            to -= 1;
            from -= 1;
            for (; amount > 0; --amount) {
                stacks[to].push(stacks[from].top());
                stacks[from].pop();
            }
        }

        // Answer is top of each stack
        std::string out{};
        for (const auto& stack : stacks) {
            out.push_back(stack.top());
        }
        return out;
    }

    std::string part_two() {
        std::array<std::stack<char>, 9> stacks = make_stacks();
        std::ifstream input = get_input("day05");

        while (input.good()) {
            int amount;
            int from;
            int to;
            std::string ignore;
            input >> ignore; // "move"
            input >> amount;
            input >> ignore; // "from"
            input >> from;
            input >> ignore; // "to"
            input >> to;

            // 0-indexing
            to -= 1;
            from -= 1;
            std::stack<char> temp {};
            for (; amount > 0; --amount) {
                // Need to maintain order instead of reversing; use temp stack to re-reverse
                temp.push(stacks[from].top());
                stacks[from].pop();
            }
            while (!temp.empty()) {
                stacks[to].push(temp.top());
                temp.pop();
            }
        }

        // Answer is top of each stack
        std::string out{};
        for (const auto& stack : stacks) {
            out.push_back(stack.top());
        }
        return out;
    }

}
