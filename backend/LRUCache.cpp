#include "LRUCache.hpp"
#include <optional>
#include <stdexcept>

LRUCache::LRUCache(const uint32_t capacity) : capacity_(capacity), memory_(new Block[capacity_]), freelist_head_index_(0), lru_head_index_(0), lru_tail_index_(0) {
    if(capacity_ == 0) throw std::invalid_argument("capacity must be greater than 0 !!!");
    if(capacity_ > MAX_CAPACITY) throw std::out_of_range("capacity must be smaller than the maximum unsigned 32bit integer!!!");

    map_.reserve(capacity);
    auto prev_index = BLOCK_NULLPTR;

    for(uint32_t i = 0; i < capacity_ - 1; ++i){
        memory_[i] = Block{.prev = prev_index, .next = i+1};
        prev_index = i;
    }
    memory_[capacity_ - 1] = Block{.prev = prev_index, .next = BLOCK_NULLPTR};

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
        // we have a free block on the free list
        
        dest_index = freelist_head_index_;
        freelist_head_index_ = memory_[dest_index].next;

        memory_[dest_index].prev = lru_tail_index_;
        memory_[lru_tail_index_].next = dest_index;

        memory_[dest_index].key = key;
        memory_[dest_index].val = value;

        lru_tail_index_ = dest_index;

        bump(dest_index);


    }

    map_.insert({key, dest_index});

    // memory_[dest_index].key = key;
    // memory_[dest_index].val = value;

    // memory_[lru_tail_index_].next = dest_index;
    // lru_tail_index_ = dest_index;

    // bump(dest_index);

    // if(freelist_head_index_ != BLOCK_NULLPTR)
    //     freelist_head_index_ = memory_[dest_index].next;

}

void LRUCache::bump(uint32_t nodeIndex){
    if(nodeIndex == lru_head_index_) return;

    Block& blockToBump = memory_[nodeIndex];
    
    Block& prevBlock = memory_[blockToBump.prev];
    prevBlock.next = blockToBump.next;

    if(nodeIndex != lru_tail_index_){
        Block& nextBlock = memory_[blockToBump.next];
        nextBlock.prev = blockToBump.prev;
    }else{
        lru_tail_index_ = blockToBump.prev;
    }

    blockToBump.prev = BLOCK_NULLPTR;
    blockToBump.next = lru_head_index_;
    lru_head_index_ = nodeIndex;    
}