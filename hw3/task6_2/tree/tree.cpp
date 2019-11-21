#include <stack>

#include "tree.hpp"


Tree::Tree(): root(nullptr) {}

Tree::~Tree() {
    visit_in_order([](Node* node){
        delete node;
    });
}

void Tree::insert(long int value) {
    Node** tmp = &root;
    while (*tmp) {
        if ((*tmp)->value <= value) {
            tmp = &((*tmp)->right);
        } else {
            tmp = &((*tmp)->left);
        }
    }
    *tmp = new Node(value);
}

void Tree::visit_in_order(const Callback& callback) const {
    std::stack<Node*> stack;
    Node* curr = root;
    while(curr || !stack.empty()) {
        while (curr) {
            stack.push(curr);
            curr = curr->left;
        }
        curr = stack.top();
        stack.pop();
        callback(curr);
        curr = curr->right;
    }
}
