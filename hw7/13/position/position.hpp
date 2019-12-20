#pragma once

#include <vector>


const size_t HashParameter = 37;

struct Position {
    std::vector<char> chips;
    char zero_place;
    char dist;

    bool is_finish() const;
    void calc_manhatten_dist();
    std::vector<Position> siblings() const;
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    bool operator<(const Position& other) const;
};

namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(const Position& key) const {
            size_t value = 0;
            for (auto chip : key.chips) {
                value = HashParameter * value + static_cast<size_t>(chip);
            }
            return value;
        }
    };
}

const Position FinishPosition{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}, 15};

char get_move_symbol(const Position& from, const Position& to);
