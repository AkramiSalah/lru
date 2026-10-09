#pragma once
#include <cstdint>
#include <optional>
#include <unordered_map>



using KeyType = int;
using ValueType = int;


struct Block{
    unsigned int prev;
    int key;
    int val;
    unsigned int next;
};

class LRUCache {
public:
    using KeyType = int;
    using ValueType = int;

    static constexpr uint32_t BLOCK_NULLPTR = 0xFFFFFFFF; 

    LRUCache() = delete; // an LRU cache has to have a capacity!

    explicit LRUCache(const uint32_t capacity);
    
    std::optional<int> get(KeyType key); 

    void put(KeyType key, ValueType value);
private:
    const uint32_t capacity_;
    Block* memory_;
    uint32_t freelist_head_index_;
    uint32_t lru_head_index_;
    uint32_t lru_tail_index_;
    std::unordered_map<KeyType, uint32_t> map_; // holds key, and the index of the corrosponding AllocaedBlock 

    static constexpr uint32_t MAX_CAPACITY = 0xFFFFFFFF - 1; 


    Block& getBlock(uint32_t blockIndex);
    
    void detachBlock(uint32_t blockIndex);
    
    void lru_list_push_back(uint32_t blockIndex);
    
    void lru_list_push_front(uint32_t blockIndex);
    
    std::optional<uint32_t> allocBlock();
    
    void bump(uint32_t blockIndex);
};

