#include "LRUCache.hpp"
#include <cstdint>
#include <optional>
#include <stdexcept>

LRUCache::LRUCache(const uint32_t capacity) :
    capacity_(capacity),
    memory_(new Block[capacity_]),
    freelist_head_index_(0),
    lru_head_index_(BLOCK_NULLPTR),
    lru_tail_index_(BLOCK_NULLPTR)
{

    if(capacity_ == 0) throw std::invalid_argument("capacity must be greater than 0 !!!");
    if(capacity_ > MAX_CAPACITY) throw std::out_of_range("capacity must be smaller than the maximum unsigned 32bit integer!!!");

    map_.reserve(capacity);
    
    auto prev_index = BLOCK_NULLPTR;
    
    KeyType dummyKey = 0xDEADBEEF; // For debugging purposes
    ValueType dummyValue = 0xBABECAFE; // TODO : REMOVE LATER!!!!!
    
    for(uint32_t i = 0; i < capacity_ - 1; ++i){
        memory_[i] = Block{.prev = prev_index, .key = dummyKey, .val = dummyValue, .next = i+1,};
        prev_index = i;
    }
    memory_[capacity_ - 1] = Block{.prev = prev_index, .key = dummyKey, .val = dummyValue, .next = BLOCK_NULLPTR};

}

std::optional<KeyType> LRUCache::get(KeyType key){
    auto it = map_.find(key);
    if(it == map_.end()) return std::nullopt;
    
    bump(it->second);
    return memory_[it->second].val;
}

void LRUCache::put(KeyType key, ValueType value){
    uint32_t dest_index = freelist_head_index_;

    if(freelist_head_index_ == BLOCK_NULLPTR){
        dest_index = lru_tail_index_;
        map_.erase(memory_[dest_index].key);
        memory_[dest_index].key = key;
        memory_[dest_index].val = value;

        bump(dest_index);

    }else{
Block& LRUCache::getBlock(uint32_t blockIndex){
    // this function assumes valid blockIndex.
    return memory_[blockIndex]; 
}

void LRUCache::detachBlock(uint32_t blockIndex){
    // this function assumes that the block at blockIndex is allocated.
    auto& block = getBlock(blockIndex);
    if(blockIndex == lru_tail_index_){
        lru_tail_index_ = block.prev;
    }

    if(blockIndex == lru_head_index_){
        lru_head_index_ = block.next;
    }

    if(block.next != BLOCK_NULLPTR){
        getBlock(block.next).prev = block.prev;
    }

    if(block.prev != BLOCK_NULLPTR){
        getBlock(block.prev).next = block.next;
    }
}
}