#pragma once
#include <list>
#include <unordered_map>

class LRUCache {
public:
    LRUCache() = delete; // an LRU cache has to have a capacity!

    explicit LRUCache(int capacity);
    
    int get(int key); 

    void put(int key, int value);
private:
    std::size_t capacity_;
    std::list<std::pair<int, int>> list_; // holds [key,val]
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map_;

    void bump(std::list<std::pair<int, int>>::iterator it);

    void evict();

};

