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
        auto& node = linkedList.getNode(index);
        node.value = value;
    }
    else if(linkedList.full()){
        index = linkedList.getTailIndex();
        auto& node = linkedList.getNode(index);

        map_.erase(node.key);
        map_.emplace(key, index);

        node.key = key;
        node.value = value;
    }
    else{
        index = linkedList.createNode(key, value).value(); // i know for a fact createNode cant fail since LL isnt full.
        map_.emplace(key, index);
    }

    bump(index);
}

void LRUCache::bump(uint32_t blockIndex){
    linkedList.detachNode(blockIndex);
    linkedList.push_front(blockIndex);
}
