#include "LRUCache.hpp"
#include "LinkedList.hpp"
#include <cstdint>
#include <optional>


LRUCache::LRUCache(uint32_t capacity) : linkedList(capacity){
    map_.reserve(capacity);
}

std::optional<ValueType> LRUCache::get(KeyType key){
    auto it = map_.find(key);
    if(it == map_.end()) return std::nullopt;
    
    bump(it->second);
    return linkedList.getNode(it->second).value;
}

void LRUCache::put(KeyType key, ValueType value){
    auto it = map_.find(key);
    uint32_t index;

    if(it != map_.end()){
        index = it->second;
    }
    else{
        auto newNodeIndex = linkedList.createNode(key, value);
        index = newNodeIndex.value_or(linkedList.getTail());
    }

    auto& node = linkedList.getNode(index);
    node.key = key;
    node.value = value;
    map_.insert({key, index});
    bump(index);
}

void LRUCache::bump(uint32_t blockIndex){
    linkedList.detachNode(blockIndex);
    linkedList.push_front(blockIndex);
}
