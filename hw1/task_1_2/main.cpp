/*
 Дек с динамическим буфером
 Реализовать дек с динамическим зацикленным буфером.
 Обрабатывать команды push * и pop *.
 Формат ввода
 В первой строке количество команд n. n ≤ 1000000.
 Каждая команда задаётся как 2 целых числа: a b.

 a = 1 - push front
 a = 2 - pop front
 a = 3 - push back
 a = 4 - pop back
 Если дана команда pop *, то число b - ожидаемое значение. Если команда pop * вызвана для
 пустой структуры данных, то ожидается “-1”.

 Пример 1
 Ввод    Вывод
 3       YES
 1 44
 3 50
 2 44
 Пример 2
 Ввод    Вывод
 2       YES
 2 -1
 1 10
 Пример 3
 Ввод    Вывод
 2       NO
 3 44
 4 66
*/

#include <iostream>

#include "deque/deque.hpp"

bool get_result(int a, int b, Deque& deque) {
    bool result = true;
    if (a == 1) {
        deque.push_front(b);
    } else if (a == 3) {
        deque.push_back(b);
    } else {
        if (deque.empty()) {
            result = b == -1;
        } else if (a == 2) {
            result = b == deque.pop_front();
        } else if (a == 4) {
            result = b == deque.pop_back();
        }
    }
    return result;
}


int main() {
    Deque deque;
    int n = 0, a = 0, b = 0;
    std::cin >> n;
    bool result = true;
    for (int i = 0; i < n; ++i) {
        std::cin >> a >> b;
        result = get_result(a, b, deque);
        if (!result) {
            break;
        }
    }

    if (result) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
