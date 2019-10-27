#pragma once

class Deque {
 public:
    Deque(): buf(new int[1]), head(0), tail(0), capacity(1), size(0) {}
    Deque(const Deque&) = delete;
    Deque(Deque&&) = delete;
    Deque& operator= (const Deque&) = delete;
    Deque& operator= (Deque&&) = delete;
    ~Deque();
    
    bool empty() const;
    void reallocate(size_t new_size);
    void push_front(int value);
    void push_back(int value);
    int pop_front();
    int pop_back();

 private:
    int* buf;
    int head;
    int tail;
    size_t capacity;
    size_t size;
};
