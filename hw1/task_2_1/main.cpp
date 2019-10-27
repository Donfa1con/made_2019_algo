/* 2_1. Жадина
Вовочка ест фрукты из бабушкиной корзины.
В корзине лежат фрукты разной массы.
Вовочка может поднять не более K грамм.
Каждый фрукт весит не более K грамм.
За раз он выбирает несколько самых тяжелых фруктов,
которые может поднять одновременно, откусывает от каждого
половину и кладет огрызки обратно в корзину.
Если фрукт весит нечетное число грамм, он откусывает большую половину.
Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.

Формат ввода
Вначале вводится n - количество фруктов и n строк с массами фруктов. n ≤ 50000.
Затем K - "грузоподъемность". K ≤ 1000.
Формат вывода
Неотрицательное число - количество подходов к корзине.

Пример 1
Ввод            Вывод
3               4
1 2 2
2
Пример 2
Ввод            Вывод
3               5
4 3 5
6
Пример 3
Ввод            Вывод
7               3
1 1 1 1 1 1 1
3
*/

#include <iostream>
#include <vector>

#include "heap/heap.hpp"

int get_count(int k, Heap& heap) {
    int counter = 0;
    std::vector<int> tmp_buf;
    
    while (!heap.is_empty()) {
        int taken_weight = 0;
        while (!heap.is_empty() && taken_weight + heap.get_max() <= k) {
            int min = heap.extract_max();
            taken_weight += min;
            if (min > 1) {
                tmp_buf.push_back(min / 2);
            }
        }
        while(tmp_buf.size()) {
            heap.insert(tmp_buf.back());
            tmp_buf.pop_back();
        }
        ++counter;
    }
    return counter;
}

int main() {
    Heap heap;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int fruit = 0;
        std::cin >> fruit;
        heap.insert(fruit);
    }
    int k = 0;
    std::cin >> k;
    std::cout << get_count(k, heap) << std::endl;
    return 0;
}
