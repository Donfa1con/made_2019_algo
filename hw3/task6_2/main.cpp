/*
Дано число N ≤ 104 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root,
если root→Key ≤ K, то узел K добавляется в правое поддерево root;
иначе в левое поддерево root.
Выведите элементы в порядке in-order (слева направо).
Рекурсия запрещена.
*/
#include <iostream>
#include "tree/tree.hpp"

int main() {
    Tree tree;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int value = 0;
        std::cin >> value;
        tree.insert(value);
    }
    tree.visit_in_order([](Node* node){
        std::cout << node->value << " ";
    });
    return 0;
}
