#pragma once
#include <list>
#include <optional>
#include <unordered_map>

namespace standard {
class LRUCache {
public:
    using KeyType = int;
    using ValueType = int;
    using KeyValuePair = std::pair<KeyType, ValueType>;
    using ListIter = std::list<KeyValuePair>::iterator;

    LRUCache() = delete; // an LRU cache has to have a capacity!

    explicit LRUCache(size_t capacity);
    
    std::optional<ValueType> get(KeyType key); 

    void put(KeyType key, ValueType value);
private:
    size_t m_capacity;
    std::list<KeyValuePair> m_list;
    std::unordered_map<KeyType, ListIter> m_map;

    void bump(ListIter it);

    void evict();

};
}