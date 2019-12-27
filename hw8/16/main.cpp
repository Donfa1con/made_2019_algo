/*
16. Поиск подстроки
Найдите все вхождения шаблона в строку.
Длина шаблона – p, длина строки – n.
Время O(n + p), доп. память – O(p).
p <= 30000, n <= 300000.
Использовать один из методов:
- С помощью z-функции.

Формат ввода
Шаблон, символ перевода строки, строка.

Формат вывода
Позиции вхождения шаблона в строке.

Пример
Ввод    Вывод
a       0 1 2
aaa
*/
#include <iostream>
#include <string>
#include <vector>


std::vector<size_t> find_positions(const std::string& pattern, const std::string& str) {
    size_t pattern_size = pattern.size();
    size_t str_size = str.size();
    std::vector<size_t> z_func(pattern_size);
    std::vector<size_t> positions;
    
    for (size_t i = 1, left = 0, right = 0; i < pattern_size + str_size; ++i) {
        bool is_pattern = i < pattern_size;
        size_t z_value = 0;
        if (i <= right) {
            z_value = std::min(right - i + 1, z_func[i - left]);
        }
        
        while (is_pattern && i + z_value < pattern_size && pattern[z_value] == pattern[i + z_value]) {
            ++z_value;
        }
        while (!is_pattern &&i + z_value < pattern_size + str_size && pattern[z_value] == str[i + z_value - pattern_size]) {
            ++z_value;
        }
        
        if (i + z_value - 1 > right) {
            left = i;
            right = i + z_value - 1;
        }
        if (is_pattern) {
            z_func[i] = z_value;
        } else if (z_value == pattern_size) {
            positions.push_back(i - pattern_size);
        }
    }
    return positions;
}


int main() {
    std::string pattern = "";
    std::string str = "";
    std::cin >> pattern >> str;
    for (auto v: find_positions(pattern, str))
        std::cout << v << " ";
    return 0;
}
