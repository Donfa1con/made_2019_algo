#include "utils.hpp"


bool bfs(Position& start, std::unordered_map<Position, Position>& parents) {
    std::priority_queue<Position> positions_queue;
    positions_queue.push(start);
    while (!positions_queue.empty()) {
        Position current = positions_queue.top();
        positions_queue.pop();
        for (auto sibling: current.siblings()) {
            if (parents.count(sibling)) {
                continue;
            }
            parents[sibling] = current;
            if (sibling.is_finish()) {
                return true;
            }
            positions_queue.push(sibling);
        }
    }
    return false;
}

std::vector<char> get_path(const Position& start,
                           const std::unordered_map<Position, Position>& parents) {
    std::vector<char> result;

    Position current = FinishPosition;
    while (current != start) {
        const Position parent = parents.at(current);
        result.push_back(get_move_symbol(parent, current));
        current = parent;
    }
    // Развернем result, так как собирали его с конца.
    std::reverse(result.begin(), result.end());
    return result;
}

std::pair<bool, std::vector<char>> solve_puzzle15(Position& start) {
    // Запустим BFS, запоминая предков всех пройденных позиций.
    std::unordered_map<Position, Position> parents;

    if (!bfs(start, parents)) {
        return std::make_pair(false, std::vector<char>());
    }
    return std::make_pair(true, get_path(start, parents));
}

