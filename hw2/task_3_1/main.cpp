/*
 Дана очень длинная последовательность целых чисел длины n.
 Требуется вывести в отсортированном виде её наименьшие k элементов.
 Последовательность может не помещаться в память.
 Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 Пример:
 Ввод                 Вывод
 9 4                  1 2 3 4
 3 7 4 5 6 1 15 4 2
*/
#include <iostream>
#include <cstring>


void merge(int* first, int first_size, int* second, int second_size, int k) {
    int* top_k = new int[k];

    int f_idx = 0, s_idx = 0, k_idx = 0;
    while (k_idx < k) {
        if (f_idx == first_size) {
            memcpy(top_k + k_idx, second + s_idx, sizeof(int) * (k - k_idx));
            break;
        } else if (s_idx == second_size) {
            memcpy(top_k + k_idx, first + f_idx, sizeof(int) * (k - k_idx));
            break;
        }
        
        if (first[f_idx] < second[s_idx]) {
            top_k[k_idx++] = first[f_idx++];
        } else {
            top_k[k_idx++] = second[s_idx++];
        }
    }
    
    memcpy(first, top_k, sizeof(int) * k);
    delete[] top_k;
}

void merge_sort(int* data, int n) {
    if (n <= 1) {
        return;
    }
    
    int first_size = n / 2;
    int second_size = n - first_size;
    
    merge_sort(data, first_size);
    merge_sort(data + first_size, second_size);
    merge(data, first_size, data + first_size, second_size, n);
}


int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    int* data = new int[k];
    int* top_k = new int[k];

    for (int i = 0; i < n; ++i) {
        std::cin >> data[i % k];
        if ((i % k == k - 1) || (i == n - 1)) {
            merge_sort(data, i % k + 1);
            if (i == k - 1) {
                std::swap(data, top_k);
            } else {
                merge(top_k, k, data, i % k + 1, k);
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        std::cout << top_k[i] << " ";
    }

    delete[] data;
    return 0;
}
