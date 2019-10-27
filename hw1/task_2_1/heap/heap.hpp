#pragma once

#include <iostream>

class Heap {
 public:
    Heap(): buf(new int[1]), size(0), capacity(1) {}
    Heap(const Heap&) = delete;
    Heap(Heap&&) = delete;
    Heap& operator= (const Heap&) = delete;
    Heap& operator= (Heap&&) = delete;
    ~Heap();
    
    void reallocate(size_t new_capacity);
    void sift_down(int index);
    void sift_up(int index);
    void insert(int key);
    int extract_max();
    int get_max() const;
    bool is_empty() const;
    
 private:
    int* buf;
    size_t size;
    size_t capacity;
};
