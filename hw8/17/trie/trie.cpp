#include "trie.hpp"

Trie::Trie(): root(std::make_shared<TrieNode>()), sub_pattern_count(0) {}

void Trie::create_trie_from_pattern(const std::string& pattern) {
    std::string sub_pattern = "";
    for (size_t i = 0; i < pattern.size(); ++i) {
        if (pattern[i] != '?') {
            sub_pattern += pattern[i];
        } else if (sub_pattern != "") {
            add(sub_pattern, i);
            sub_pattern = "";
        }
    }
    if (sub_pattern != "") {
        add(sub_pattern, pattern.size());
    }
    pattern_size = pattern.size();
}

void Trie::add(const std::string& key, size_t sub_pattern_position) {
    std::shared_ptr<TrieNode> current = root;
    for (char symbol: key) {
        auto next = current->go.find(symbol);
        if (next == current->go.end()) {
            auto parent = current;
            current = current->go[symbol] = std::make_shared<TrieNode>();
            current->symbol = symbol;
            current->parent = parent;
        } else {
            current = next->second;
        }
    }
    current->is_terminal = true;
    current->positions.push_back(sub_pattern_position);
    ++sub_pattern_count;
}

std::shared_ptr<TrieNode> Trie::goto_next_state(std::shared_ptr<TrieNode>& node, char symbol) {
    auto next = node->go.find(symbol);
    if (next != node->go.end()) {
        return node->go[symbol];
    }
    if (node == root) {
        return root;
    }
    auto suffix_link = get_suffix_link(node);
    return node->go[symbol] = goto_next_state(suffix_link, symbol);
}

std::shared_ptr<TrieNode> Trie::get_suffix_link(std::shared_ptr<TrieNode>& node) {
    if (node->suffix_link) {
        return node->suffix_link;
    }
    if (node == root || node->parent == root) {
        return root;
    }
    auto suffix_link = get_suffix_link(node->parent);
    return node->suffix_link = goto_next_state(suffix_link, node->symbol);
}

std::shared_ptr<TrieNode> Trie::get_terminal_link(std::shared_ptr<TrieNode>& node) {
    if (node->terminal_link) {
        return node->terminal_link;
    }
    auto suffix_link = get_suffix_link(node);
    if (suffix_link == root || suffix_link->is_terminal) {
        return suffix_link;
    }
    return node->terminal_link = get_terminal_link(suffix_link);
}

std::vector<size_t> Trie::find(const std::string& str) {
    std::vector<size_t> position_counters(str.size());
    std::vector<size_t> result;
    auto next_node = root;
    for (size_t i = 0; i < str.size(); ++i) {
        next_node = goto_next_state(next_node, str[i]);
        auto current = next_node;
        for (; current != root; current = get_terminal_link(current)) {
            if (!current->is_terminal) {
                continue;
            }
            for (auto position: current->positions) {
                size_t index = i - position + 1;
                if (i + 1 >= position && index + pattern_size <= str.size()) {
                    ++position_counters[index];
                    if (position_counters[index] == sub_pattern_count) {
                        result.push_back(index);
                    }
                }
            }
        }
    }
    return result;
}
