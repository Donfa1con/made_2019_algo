#pragma once

#include <cassert>
#include <iostream>
#include <vector>


class DSU {
  public:
    DSU(size_t size);
    DSU(DSU&) = delete;
    DSU(DSU&&) = delete;
    DSU& operator=(DSU&) = delete;
    DSU& operator=(DSU&&) = delete;
    ~DSU() = default;
    
    int find(int element);
    void merge(int left, int right);

  private:
    std::vector<int> parent;
    std::vector<int> rank;
};
