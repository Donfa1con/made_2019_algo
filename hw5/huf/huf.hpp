#pragma once

#include "../buf/buf.hpp"
#include "../Huffman/Huffman.hpp"

#include <queue>
#include <vector>
#include <unordered_map>


struct HuffmanNode {
    HuffmanNode(HuffmanNode* left, HuffmanNode* right, size_t size, byte value): left(left), right(right), value(value), size(size) {};
    HuffmanNode(size_t size, byte value): left(nullptr), right(nullptr), value(value), size(size) {};
    HuffmanNode(HuffmanNode&) = delete;
    HuffmanNode(HuffmanNode&&) = delete;
    HuffmanNode& operator=(HuffmanNode&) = delete;
    HuffmanNode& operator=(HuffmanNode&&) = delete;
    ~HuffmanNode() {}
    
    HuffmanNode* left;
    HuffmanNode* right;
    byte value;
    size_t size;
};


class Huffman {
  public:
    Huffman();
    Huffman(Huffman&) = delete;
    Huffman(Huffman&&) = delete;
    Huffman& operator=(Huffman&) = delete;
    Huffman& operator=(Huffman&&) = delete;
    ~Huffman();
    
    void encode(IInputStream& input, IOutputStream& output);
    void decode(IInputStream& input, IOutputStream& output);

  private:
    std::unordered_map<byte, size_t> create_freq_table(IInputStream& input);
    void build_tree(const std::unordered_map<byte, size_t>& freq_table);
    void delete_tree(HuffmanNode* node);
    
    void encode_nodes(HuffmanNode* node, std::vector<bool> huffman_code,
                      std::unordered_map<byte, vector<bool>>& code_table);
    std::unordered_map<byte, std::vector<bool>> encode_tree();
    std::vector<byte> encode_data(const std::unordered_map<byte, vector<bool>>& code_table);
    
    void read_compressed(IInputStream& input);
    HuffmanNode* decode_tree();
    std::vector<byte> decode_data();
    
    byte size_;
    vector<byte> data_;
    HuffmanNode* top_node_;
    BitsWriter writer;
    BitsReader reader;
};


