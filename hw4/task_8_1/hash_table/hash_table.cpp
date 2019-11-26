#include "hash_table.hpp"

HashTable::HashTable(): capacity(8), table_size(0), table(new std::string[capacity]) {}

HashTable::~HashTable() {
    delete[] table;
}

size_t HashTable::hash(const char* key, size_t m) const {
    size_t hash_value = 0;
    for(;*key; ++key) {
        hash_value = (hash_value * 3 + *key) % m;
    }
    return hash_value;
}

size_t HashTable::find_index(const std::string& key, const std::string* search_table,
                            size_t m, const std::string& type = "add") const {
    size_t key_hash = hash(key.data(), m);
    size_t new_hash = key_hash;
    int insert_hash = -1;
    size_t i = 0;
    do {
        new_hash = (key_hash + i * (i + 1) / 2) % m;
        i++;
        if (insert_hash == -1 &&
            (search_table[new_hash] == HashTableConstants::deleted || search_table[new_hash] == "")) {
            insert_hash = static_cast<int>(new_hash);
        }
    } while(search_table[new_hash] != "" && search_table[new_hash] != key && i < capacity);
    if (type == "add" && search_table[new_hash] != key) {
        new_hash = insert_hash;
    }
    return new_hash;
}

void HashTable::rehash(size_t new_capacity) {
    std::string* new_table = new std::string[new_capacity];
    for (size_t element_replaced = 0, i = 0; element_replaced < table_size; ++i) {
        if (table[i] != "" && table[i] != HashTableConstants::deleted) {
            size_t index = find_index(table[i], new_table, new_capacity);
            new_table[index] = table[i];
            element_replaced++;
        }
    }
    delete[] table;
    table = new_table;
    capacity = new_capacity;
}

bool HashTable::add(const std::string& key) {
    size_t index = find_index(key, table, capacity);
    if (table[index] != key) {
        table[index] = key;
        table_size++;
        if (table_size >= capacity * HashTableConstants::load_factor) {
            rehash(capacity * 2);
        }
        return true;
    }
    return false;
}

bool HashTable::has(const std::string& key) const {
    size_t index = find_index(key, table,  capacity, "");
    if (table[index] == key) {
        return true;
    }
    return false;
}

bool HashTable::remove(const std::string& key) {
    size_t index = find_index(key, table, capacity, "");
    if (table[index] == key) {
        table[index] = HashTableConstants::deleted;
        table_size--;
        return true;
    }
    return false;
}
