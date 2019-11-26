#pragma once
#include <string>

namespace HashTableConstants {
    const std::string deleted = "@";
    const float load_factor = 0.75;
}

class HashTable {
  public:
    HashTable();
    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;
    ~HashTable();
    
    bool has(const std::string& key) const;
    bool add(const std::string& key);
    bool remove(const std::string& key);
  private:
    void rehash(size_t new_capacity);
    size_t hash(const char* key, size_t m) const;
    size_t find_index(const std::string& key, const std::string* search_table,
                      size_t m, const std::string& type) const;
    
    size_t capacity;
    size_t table_size;
    std::string* table;
};
