#include "LRUCache.hpp"
#include "LinkedList.hpp"
#include <cstdint>
#include <optional>


namespace custom {
LRUCache::LRUCache(uint32_t capacity) : m_linkedList(capacity){
    m_map.reserve(capacity);
}

std::optional<LRUCache::ValueType> LRUCache::get(KeyType key){
    auto it = m_map.find(key);
    if(it == m_map.end()) return std::nullopt;
    
    bump(it->second);
    return m_linkedList.getNode(it->second).value;
}

void LRUCache::put(KeyType key, ValueType value){
    auto it = m_map.find(key);
    uint32_t index;
    if(it != m_map.end()){
        index = it->second;
        auto& node = m_linkedList.getNode(index);
        node.value = value;
    }
    else if(m_linkedList.full()){
        index = m_linkedList.getTailIndex();
        auto& node = m_linkedList.getNode(index);
        
        // map_.erase(node.key);
        // map_.insert({key, index});
        
        auto nh = m_map.extract(node.key);
        nh.key() = key;
        
        m_map.insert(std::move(nh));
        
        node.key = key;
        node.value = value;
    }
    else{
        index = m_linkedList.create_node_at_front(key, value); // i know for a fact createNode cant fail since LL isnt full.
        m_map.emplace(key, index);
        return; // no need to bump, node was created at front.
    }
    
    bump(index);
}

void LRUCache::bump(uint32_t blockIndex){
    if(m_linkedList.getHeadIndex() == blockIndex) return;
    m_linkedList.detachNode(blockIndex);
    m_linkedList.push_front(blockIndex);
}
}