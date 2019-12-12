#include "huf.hpp"


Huffman::Huffman(): size_(0), top_node_(nullptr) {};


Huffman::~Huffman() {
    delete_tree(top_node_);
}


std::unordered_map<byte, size_t> Huffman::create_freq_table(IInputStream& input) {
    std::unordered_map<byte, size_t> freq_table;
    byte value;
    while (input.Read(value)) {
        data_.push_back(value);
        freq_table[value]++;
    }
    size_ = freq_table.size();
    return freq_table;
}


void Huffman::build_tree(const std::unordered_map<byte, size_t>& freq_table) {
    auto comparator = [](HuffmanNode* left, HuffmanNode* right){
        return left->size > right->size;
    };
    std::priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(comparator)> heap(comparator);
    for (auto& it: freq_table) {
        heap.push(new HuffmanNode(it.second, it.first));
    }
    
    if (heap.size() == 1) {
        HuffmanNode* node = heap.top();
        heap.pop();
        HuffmanNode* new_node = new HuffmanNode(node, nullptr, node->size, '\0');
        heap.push(new_node);
    } else {
        while (heap.size() != 1) {
            HuffmanNode* first_node = heap.top();
            heap.pop();
            HuffmanNode* second_node = heap.top();
            heap.pop();
            auto parent_node = new HuffmanNode(first_node, second_node, first_node->size + second_node->size, '\0');
            heap.push(parent_node);
        }
    }
    top_node_ = heap.top();
    size_ = freq_table.size();
}


void Huffman::delete_tree(HuffmanNode* node) {
    if (node) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}


void Huffman::encode_nodes(HuffmanNode* node, vector<bool> huffman_code,
                           std::unordered_map<byte, vector<bool>>& code_table) {
    if (!node->left && !node->right) {
        writer.write_bit(true);
        writer.write_byte(node->value);
        code_table[node->value] = huffman_code;
    } else {
        writer.write_bit(false);
        if (node->left) {
            huffman_code.push_back(false);
            encode_nodes(node->left, huffman_code, code_table);
            huffman_code.pop_back();
        }
        if (node->right) {
            huffman_code.push_back(true);
            encode_nodes(node->right, huffman_code, code_table);
        }
    }
}


std::unordered_map<byte, std::vector<bool>> Huffman::encode_tree() {
    writer.write_byte(size_);
    std::unordered_map<byte, std::vector<bool>> code_table;
    std::vector<bool> huffman_code;
    encode_nodes(top_node_, huffman_code, code_table);
    return code_table;
}


std::vector<byte> Huffman::encode_data(const std::unordered_map<byte, std::vector<bool>>& code_table) {
    for (auto value: data_) {
        std::vector<bool> bits = code_table.at(value);
        for (auto bit: bits) {
            writer.write_bit(bit);
        }
    }
    return writer.get_result();
}


void Huffman::encode(IInputStream& input, IOutputStream& output) {
    auto freq_table = create_freq_table(input);
    build_tree(freq_table);
    auto code_table = encode_tree();
    auto result = encode_data(code_table);

    for (auto value: result) {
        output.Write(value);
    }
}


void Huffman::read_compressed(IInputStream& input) {
    input.Read(size_);
    byte value;
    while (input.Read(value)) {
        data_.push_back(value);
    }
}


HuffmanNode* Huffman::decode_tree() {
    if (size_) {
        if (reader.read_bit(data_)) {
            --size_;
            return new HuffmanNode(0, reader.read_byte(data_));
        } else {
            HuffmanNode* leftChild = decode_tree();
            HuffmanNode* rightChild = decode_tree();
            return new HuffmanNode(leftChild, rightChild, 0, '\0');
        }
    }
    return nullptr;
}


std::vector<byte> Huffman::decode_data() {
    std::vector<byte> result;
    HuffmanNode* node = top_node_;
    while (reader.is_end_position(data_)) {
        if (reader.read_bit(data_)) {
            node = node->right;
        } else {
            node = node->left;
        }
        if (!node->left && !node->right) {
            result.push_back(node->value);
            node = top_node_;
        }
    }
    return result;
}


void Huffman::decode(IInputStream& input, IOutputStream& output) {
    read_compressed(input);
    top_node_ = decode_tree();
    auto result = decode_data();
    for (auto value: result) {
        output.Write(value);
    }
}
