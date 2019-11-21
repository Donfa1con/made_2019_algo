#pragma once
#include <functional>

struct Node {
    Node(long int value): left(nullptr), right(nullptr), value(value) {}
    Node* left;
    Node* right;
    long int value;
};

using Callback = std::function<void(Node*)>;

class Tree {
  public:
    Tree();
    Tree(const Tree&) = delete;
    Tree(Tree&&) = delete;
    Tree& operator= (const Tree&) = delete;
    Tree& operator= (Tree&&) = delete;
    ~Tree();
    
    void visit_in_order(const Callback& callback) const;
    void insert(long int value);
  private:
    Node* root;
};
