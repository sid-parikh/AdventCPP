#include "day15.hpp"

#include "input_utils.hpp"
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_set>

namespace day15 {

    struct item {
        std::pair<int, int> sensor;
        std::pair<int, int> beacon;
    };

    std::vector<item> get_items() {
        std::ifstream in = get_input("day15");
        std::vector<item> out{};

        while (in.good()) {
            item line;
            in.ignore(30, '=');
            in >> line.sensor.first;
            in.ignore(30, '=');
            in >> line.sensor.second;
            in.ignore(30, '=');
            in >> line.beacon.first;
            in.ignore(30, '=');
            in >> line.beacon.second;
            out.push_back(std::move(line));
        }

        return out;
    }

    std::string part_one() {
        std::vector<item> in = get_items();

        int tgt_y = 2'000'000;
        std::vector<std::pair<int, int>> ranges{};
        std::unordered_set<int> beacon_xs {};
        for (const auto& it: in) {
            /* Some math:
             * dist is fixed. |x1-x2| + |y1 - y2|
             * given dist, x1, y1 (sensor), and tgt_y (y2), solve for x2
             * for dists <= dist
             * |y1-y2| is a constant d_y
             * |x-x_0| + d_y <= dist
             * |x-x_0| <= dist - d_y
             * d_y - dist <= x-x_0 <= dist - d_y
             * d_y - dist + x_0 <= x <= dist - d_y + x_0
             */
            const int d_y{std::abs(it.sensor.second - tgt_y)};
            const int dist{
                    std::abs(it.sensor.first - it.beacon.first) +
                    std::abs(it.sensor.second - it.beacon.second)
            };
            const int left{
                    it.sensor.first - (dist - d_y)
            };
            const int right{
                    it.sensor.first + (dist - d_y)
            };

            const int lower_bound {std::min(left, right)};
            const int upper_bound {std::max(left, right)};

            ranges.emplace_back(lower_bound, upper_bound);
        }

        // merge overlapping intervals and count total size
        std::sort(ranges.begin(), ranges.end());
        std::vector<std::pair<int, int>> merged {};
        merged.push_back(ranges.front());
        //https://leetcode.com/problems/merge-intervals/solutions/21242/c-10-line-solution-easing-understanding/ (LOL)
        for (std::size_t i = 1; i < ranges.size(); ++i) {
            if (merged.back().second < ranges[i].first) {
                // No overlap, push this range
                merged.push_back(ranges[i]);
            } else {
                // If there is some overlap, just update with the max value
                merged.back().second = std::max(merged.back().second, ranges[i].second);
            }
        }

        // Now count total size of the non-overlapping intervals
        unsigned long size = 0;
        for (const auto& r : merged) {
            size += r.second - r.first + 1;
        }

        size -= (beacon_xs.size());

        return std::to_string(size);
    }

    std::string part_two() {
        return {};
    }
}
