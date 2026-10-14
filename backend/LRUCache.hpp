#pragma once
#include <list>
#include <optional>
#include <unordered_map>

class LRUCache {
public:
    using KeyType = int;
    using ValueType = int;
    using KeyValuePair = std::pair<KeyType, ValueType>;
    using ListIter = std::list<KeyValuePair>::iterator;

    LRUCache() = delete; // an LRU cache has to have a capacity!

    explicit LRUCache(size_t capacity);
    
    std::optional<int> get(KeyType key); 

    void put(KeyType key, ValueType value);
private:
    size_t capacity_;
    std::list<KeyValuePair> list_;
    std::unordered_map<KeyType, ListIter> map_;

    void bump(ListIter it);

    void evict();

};