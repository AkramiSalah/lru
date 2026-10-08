
// #include <cstddef>
// #include <list>
// #include <optional>
// #include <unordered_map>

// LRUCache::LRUCache(size_t capacity) : capacity_(capacity), memory( new int[capacity_]), freelist_head_(0) {
    //     map_.reserve(capacity_);
    // }
    
    // void LRUCache::bump(int nodeIndex){
        //     // make node at memory[nodeIndex] become the head
        // }
        
        // void LRUCache::evict(){
            //     while(list_.size() > capacity_){
                //         KeyType key = list_.back().first;
                //         map_.erase(key);
                //         list_.pop_back();
                //     }
                // }
                
                
                // std::optional<int> LRUCache::get(KeyType key) {
                    //     auto nodeIterator = map_.find(key);
                    //     if(nodeIterator != map_.end()){
                        //         bump(nodeIterator->second);
                        //         return nodeIterator->second->second;
                        //     }
                        //     return std::nullopt;
                        // }
                        
                        // void LRUCache::put(KeyType key, ValueType value) {
                            //     auto nodeIterator = map_.find(key);
                            //     if(nodeIterator != map_.end()){
                                //         bump(nodeIterator->second);
                                //         nodeIterator->second->second = value;
                                //         return;
                                //     }
                                
                                //     list_.emplace_front(key,value);
                                //     map_.insert({key, list_.begin()});
                                //     evict();
                                // }
                                
#include "LRUCache.hpp"
#include <optional>
#include <stdexcept>

LRUCache::LRUCache(const uint32_t capacity) : capacity_(capacity), memory_(new Block[capacity_]), freelist_head_index_(0), lru_head_index_(0), lru_tail_index_(0) {
    if(capacity_ == 0) throw std::invalid_argument("capacity must be greater than 0 !!!");
    if(capacity_ > MAX_CAPACITY) throw std::out_of_range("capacity must be smaller than the maximum unsigned 32bit integer!!!");

    map_.reserve(capacity);
    auto prev_index = BLOCK_NULLPTR;

    for(uint32_t i = 0; i < capacity_ - 1; ++i){
        memory_[i].freeBlock = FreeBlock{.prev = prev_index, .next = i+1};
        prev_index = i;
    }
    memory_[capacity_ - 1].freeBlock = FreeBlock{.prev = prev_index, .next = BLOCK_NULLPTR};

}

std::optional<KeyType> LRUCache::get(KeyType key){
    auto it = map_.find(key);
    if(it == map_.end()) return std::nullopt;
    
    bump(it->second);
    return memory_[it->second].allocatedBlock.val;
}

void LRUCache::put(KeyType key, ValueType value){
    uint32_t dest_index = freelist_head_index_;

    if(freelist_head_index_ == BLOCK_NULLPTR){
        uint32_t dest_index = lru_tail_index_;
    }

    memory_[dest_index].allocatedBlock.key = key;
    memory_[dest_index].allocatedBlock.val = value;
    bump(dest_index);

    if(freelist_head_index_ != BLOCK_NULLPTR)
        freelist_head_index_ = memory_[dest_index].freeBlock.next;

}

void LRUCache::bump(uint32_t nodeIndex){
    if(nodeIndex == lru_head_index_) return;

    AllocatedBlock& blockToBump = memory_[nodeIndex].allocatedBlock;
    
    AllocatedBlock& prevBlock = memory_[blockToBump.prev].allocatedBlock;
    prevBlock.next = blockToBump.next;

    if(nodeIndex != lru_tail_index_){
        AllocatedBlock& nextBlock = memory_[blockToBump.next].allocatedBlock;
        nextBlock.prev = blockToBump.prev;
    }else{
        lru_tail_index_ = blockToBump.prev;
    }

    blockToBump.prev = BLOCK_NULLPTR;
    blockToBump.next = lru_head_index_;
    lru_head_index_ = nodeIndex;    
}

