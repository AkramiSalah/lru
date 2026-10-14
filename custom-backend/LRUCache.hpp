#pragma once
#include <cstdint>
#include <optional>
#include <unordered_map>
#include "LinkedList.hpp"

using KeyType = int;
using ValueType = int;

class LRUCache {
public:

    explicit LRUCache(uint32_t capacity);
    ~LRUCache() = default;

    // This class has a non copyable, non moveable member (LinkedList) 
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = delete;
    LRUCache& operator= (LRUCache&&) = delete;
    
    std::optional<ValueType> get(KeyType key); 

    void put(KeyType key, ValueType value);
private:
    LinkedList m_linkedList;
    std::unordered_map<KeyType, uint32_t> m_map; // holds key, and the index of the corrosponding AllocaedBlock 

    void bump(uint32_t blockIndex);
};