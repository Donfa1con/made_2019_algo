#include <cassert>
#include <iostream>

#include "heap.hpp"

Heap::~Heap() {
    delete[] buf;
}

void Heap::reallocate(size_t new_capacity) {
    assert(new_capacity >= size);
    int* new_buf = new int[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_buf[i] = buf[i];
    }
    delete[] buf;
    buf = new_buf;
    capacity = new_capacity;
}

void Heap::sift_down(int index) {
    while (2 * index + 1 < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int tmp_index = left;
        if (right < size and buf[right] > buf[left]) {
            tmp_index = right;
        }
        if (buf[index] >= buf[tmp_index]) {
            break;
        }
        std::swap(buf[index], buf[tmp_index]);
        index = tmp_index;
    }
}

void Heap::sift_up(int index) {
    while (buf[index] > buf[(index - 1) / 2]) {
        std::swap(buf[index], buf[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void Heap::insert(int key) {
    if (size == capacity) {
        reallocate(capacity * 2);
    }
    buf[size] = key;
    sift_up(size);
    ++size;
}

int Heap::extract_max() {
    assert(size);
    if (size < capacity / 4) {
        reallocate(capacity / 2);
    }
    int max = buf[0];
    --size;
    buf[0] = buf[size];
    sift_down(0);
    return max;
}

int Heap::get_max() const {
    assert(size);
    return buf[0];
}

bool Heap::is_empty() const {
    return size == 0;
}
