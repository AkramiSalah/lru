#include "LRUCache.hpp"

#include <list>
#include <unordered_map>

LRUCache::LRUCache(size_t capacity) : capacity_(capacity) {
    map_.reserve(capacity_);
}

void LRUCache::bump(ListIter it){
    list_.splice(list_.cbegin(), list_, it);
}

void LRUCache::evict(){
    while(list_.size() > capacity_){
        KeyType key = list_.back().first;
        map_.erase(key);
        list_.pop_back();
    }
}


int LRUCache::get(KeyType key) {
    auto nodeIterator = map_.find(key);
    if(nodeIterator != map_.end()){
        bump(nodeIterator->second);
        return nodeIterator->second->second;
    }
    return -1;
}

void LRUCache::put(KeyType key, ValueType value) {
    auto nodeIterator = map_.find(key);
    if(nodeIterator != map_.end()){
        bump(nodeIterator->second);
        nodeIterator->second->second = value;
        return;
    }

    list_.emplace_front(key,value);
    map_.insert({key, list_.begin()});
    evict();
}