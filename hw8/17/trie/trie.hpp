#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <queue>


struct TrieNode {
    std::map<char, std::shared_ptr<TrieNode>> go;
    char symbol;
    bool is_terminal = false;
    std::vector<size_t> positions;
    std::shared_ptr<TrieNode> parent = nullptr;
    std::shared_ptr<TrieNode> suffix_link = nullptr;
    std::shared_ptr<TrieNode> terminal_link = nullptr;
};


class Trie {
  public:
    Trie();
    Trie(const Trie&) = delete;
    Trie(Trie&&) = delete;
    Trie& operator=(const Trie&) = delete;
    Trie& operator=(Trie&&) = delete;
    ~Trie() = default;

    void create_trie_from_pattern(const std::string& pattern);
    void add(const std::string& key, size_t sub_pattern_position);
    std::vector<size_t> find(const std::string& key);
    
  private:
    std::shared_ptr<TrieNode> goto_next_state(std::shared_ptr<TrieNode>& node, char symbol);
    std::shared_ptr<TrieNode> get_suffix_link(std::shared_ptr<TrieNode>& node);
    std::shared_ptr<TrieNode> get_terminal_link(std::shared_ptr<TrieNode>& node);
    std::shared_ptr<TrieNode> root;
    size_t sub_pattern_count;
    size_t pattern_size;
};
