#include "LRUCache.hpp"

#include <list>
#include <optional>
#include <unordered_map>

namespace standard {

LRUCache::LRUCache(size_t capacity) : m_capacity(capacity) {
    m_map.reserve(m_capacity);
}

void LRUCache::bump(ListIter it){
    m_list.splice(m_list.cbegin(), m_list, it);
}

void LRUCache::evict(){
    while(m_list.size() > m_capacity){
        KeyType key = m_list.back().first;
        m_map.erase(key);
        m_list.pop_back();
    }
}


std::optional<LRUCache::ValueType> LRUCache::get(KeyType key) {
    auto nodeIterator = m_map.find(key);
    if(nodeIterator != m_map.end()){
        bump(nodeIterator->second);
        return nodeIterator->second->second;
    }
    return std::nullopt;
}

void LRUCache::put(KeyType key, ValueType value) {
    auto nodeIterator = m_map.find(key);
    if(nodeIterator != m_map.end()){
        bump(nodeIterator->second);
        nodeIterator->second->second = value;
        return;
    }

    m_list.emplace_front(key,value);
    m_map.insert({key, m_list.begin()});
    evict();
}

}