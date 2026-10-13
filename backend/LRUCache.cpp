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

        // map_.erase(node.key);
        // map_.insert({key, index});

        auto nh = map_.extract(node.key);
        nh.key() = key;

        map_.insert(std::move(nh));

        node.key = key;
        node.value = value;
    }
    else{
        index = linkedList.create_node_at_front(key, value); // i know for a fact createNode cant fail since LL isnt full.
        map_.emplace(key, index);
        return; // no need to bump, node was created at front.
    }

    bump(index);
}

void LRUCache::bump(uint32_t blockIndex){
    if(linkedList.getHeadIndex() == blockIndex) return;
    linkedList.detachNode(blockIndex);
    linkedList.push_front(blockIndex);
}
