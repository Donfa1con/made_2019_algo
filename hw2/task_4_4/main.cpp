/*
 4. Порядковая статистика
 Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
 Требуется найти k-ю порядковую статистику. т.е. напечатать число,
 которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
 Напишите нерекурсивный алгоритм.
 Требования к дополнительной памяти: O(n).
 Требуемое среднее время работы: O(n).
 Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении
 от конца массива к началу.
 Пример
 Ввод                   Вывод
 10 4                   5
 1 2 3 4 5 6 7 8 9 10
*/
#include <iostream>
#include <cstdlib>
#include <ctime>


int partition(long int* data, int size) {
    std::srand(unsigned(std::time(0)));
    int pivot_idx = std::rand() % size;
    
    std::swap(data[0], data[pivot_idx]);
    int i = size - 1, j = size - 1;
    while (j > 0) {
        if (data[j] >= data[0]) {
            std::swap(data[i], data[j]);
            i--;
        }
        j--;
    }
    std::swap(data[0], data[i]);
    return i;
}


long int get_k_stat(long int* data, int size, int k) {
    int pivot_idx = partition(data, size);
    int lidx = 0, ridx = size;
    int k_stat_idx = pivot_idx;
    while (k != k_stat_idx) {
        if (k > k_stat_idx) {
            lidx = k_stat_idx + 1;
        } else {
            ridx = k_stat_idx;
        }
        pivot_idx = partition(data + lidx, ridx - lidx);
        k_stat_idx = lidx + pivot_idx;
    }
    return data[k_stat_idx];
}


int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    long int* data = new long int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    
    std::cout << get_k_stat(data, n, k) << std::endl;
    
    delete[] data;
    return 0;
}
