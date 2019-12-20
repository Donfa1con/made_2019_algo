#include "position.hpp"
#include <iostream>
#include <cassert>


bool Position::is_finish() const {
  return operator==(FinishPosition);
}

std::vector<Position> Position::siblings() const {
    std::vector<Position> result;
    if (zero_place < 12) {
        Position sibling = *this;
        std::swap(sibling.chips[zero_place], sibling.chips[zero_place + 4]);
        sibling.zero_place += 4;
        result.emplace_back(sibling);
    }
    if (zero_place >= 4) {
        Position sibling = *this;
        std::swap(sibling.chips[zero_place], sibling.chips[zero_place - 4]);
        sibling.zero_place -= 4;
        result.emplace_back(sibling);
    }
    if (zero_place % 4 != 0) {
        Position sibling = *this;
        std::swap(sibling.chips[zero_place], sibling.chips[zero_place - 1]);
        sibling.zero_place -= 1;
        result.emplace_back(sibling);
    }
    if (zero_place % 4 != 3) {
        Position sibling = *this;
        std::swap(sibling.chips[zero_place], sibling.chips[zero_place + 1]);
        sibling.zero_place += 1;
        result.emplace_back(sibling);
    }
    for (auto& res: result) {
        res.calc_manhatten_dist();
    }
    return result;
}

bool Position::operator==(const Position& other) const {
    for (size_t i = 0; i < chips.size(); ++i ) {
        if (chips[i] != other.chips[i]) {
            return false;
        }
    }
    return true;
}

bool Position::operator!=(const Position &other) const {
    return !operator==(other);
}

bool Position::operator<(const Position &other) const {
    return dist > other.dist;
}

void Position::calc_manhatten_dist() {
    dist = 0;
    for (int i = 0; i < 16; ++i) {
        dist += std::abs(i + 1 - chips[i]) % 4 + std::abs(i / 4 - (chips[i] - 1) / 4);
    }
}

char get_move_symbol(const Position& from, const Position& to) {
    int zero_diff = to.zero_place - from.zero_place;
    switch (zero_diff) {
        case 1:
            return 'L'; // Ноль вправо -> фишка влево
        case -1:
            return 'R';
        case 4:
            return 'U';
        case -4:
            return 'D';
        default:
            assert(false);
    }
    return 0;
}
