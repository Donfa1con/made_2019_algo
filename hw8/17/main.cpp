/*
17. Шаблон с ?
Шаблон поиска задан строкой длины m,
в которой кроме обычных символов могут встречаться символы “?”.\
Найти позиции всех вхождений шаблона в тексте длины n.
Каждое вхождение шаблона предполагает,
что все обычные символы совпадают с соответствующими из текста,
а вместо символа “?” в тексте встречается произвольный символ.
Гарантируется, что сам “?” в тексте не встречается.

Время работы - O(n + m + Z),
где Z - общее число вхождений подстрок шаблона “между вопросиками” в исходном тексте.
m ≤ 5000, n ≤ 2000000.

Пример 1
Ввод                        Вывод
ab??aba                     2
ababacaba

Пример 2
Ввод                        Вывод
aa??bab?cbaa?               0 13
aabbbabbcbaabaabbbabbcbaab
*/
#include <iostream>

#include "trie/trie.hpp"

int main() {
    Trie trie;
    std::string pattern = "";
    std::string str = "";
    std::cin >> pattern >> str;
    
    if (std::all_of(pattern.begin(), pattern.end(), [](char ch) {return ch == '?';})) {
        for (size_t i = 0; i < str.size() - pattern.size() + 1; ++i) {
            std::cout << i << " ";
        }
    } else {
        trie.create_trie_from_pattern(pattern);
        for (auto res: trie.find(str)) {
            std::cout << res << " ";
        }
    }
    return 0;
}
