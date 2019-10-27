#include <cassert>

#include "deque.hpp"

Deque::~Deque() {
    if (buf) {
        delete[] buf;
    }
}

bool Deque::empty() const {
    return size == 0;
}

void Deque::reallocate(size_t new_capacity) {
    assert(new_capacity >= size);
    int* new_buf = new int[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_buf[i] = buf[(head + i + 1) % capacity];
    }
    delete[] buf;
    buf = new_buf;
    tail = size - 1;
    head = new_capacity - 1;
    capacity = new_capacity;
}

void Deque::push_back(int value) {
    if (head == tail && size) {
        reallocate(capacity * 2);
    }
    tail = (tail + 1) % capacity;
    buf[tail] = value;
    ++size;
}

void Deque::push_front(int value) {
    if (head == tail && size) {
        reallocate(capacity * 2);
    }
    buf[head] = value;
    head = (head - 1 + capacity) % capacity;
    ++size;
}

int Deque::pop_back() {
    assert(size);
    if (size < capacity / 4) {
        reallocate(capacity / 2);
    }
    int value = buf[tail];
    tail = (tail - 1 + capacity) % capacity;
    --size;
    return value;
}

int Deque::pop_front() {
    assert(size);
    if (size < capacity / 4) {
        reallocate(capacity / 2);
    }
    head = (head + 1) % capacity;
    --size;
    return buf[head];
}
