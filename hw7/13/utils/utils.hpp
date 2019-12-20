#pragma once
#include "../position/position.hpp"

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>


std::pair<bool, std::vector<char>> solve_puzzle15(Position& start);

bool bfs(const Position& start, std::unordered_map<Position, Position>& parents);

std::vector<char> get_path(const Position& start,
                           const std::unordered_map<Position, Position>& parents);

std::pair<bool, std::vector<char>> solve_puzzle15(const Position& start);
