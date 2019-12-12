#include <iostream>

#include "huf/huf.hpp"


void Encode(IInputStream& original, IOutputStream& compressed) {
    Huffman huffman;
    huffman.encode(original, compressed);
}

void Decode(IInputStream& compressed, IOutputStream& original) {
    Huffman huffman;
    huffman.decode(compressed, original);
}


int main() {
    // Получаем данные, которые нужно закодировать
    vector<vector<byte>> input;

    fillInputs(input);

    // Сжимаем данные
    vector<vector<byte>> compressed;
    compressed.resize(input.size());
    for (unsigned int i = 0; i < input.size(); i++) {
        CInputStream iStream(input[i]);
        COutputStream oStream(compressed[i]);
        Encode(iStream, oStream);
    }

    // Распаковываем сжатые данные и проверяем, что они совпадают с оригиналом
    for (unsigned int i = 0; i < input.size(); i++) {
        vector<byte> output;
        CInputStream iStream(compressed[i]);
        COutputStream oStream(output);
        Decode(iStream, oStream);
        if (!isEqual(input[i], output)) {
            cout << -1;
            return 0;
        }
    }

    // Вычисляем степень сжатия
    cout << (float(calculateSize(compressed)) / calculateSize(input));
    return 0;
}
