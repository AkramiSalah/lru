#pragma once
#include <list>
#include <memory>
#include <optional>
#include <unordered_map>

// class LRUCache {
// public:
//     using KeyType = int;
//     using ValueType = int;
//     using KeyValuePair = std::pair<KeyType, ValueType>;
//     using ListIter = std::list<KeyValuePair>::iterator;

//     LRUCache() = delete; // an LRU cache has to have a capacity!

//     explicit LRUCache(size_t capacity);
    
//     std::optional<int> get(KeyType key); 

//     void put(KeyType key, ValueType value);
// private:
//     size_t capacity_;
//     std::list<KeyValuePair> list_;
//     std::unordered_map<KeyType, ListIter> map_;

//     void bump(ListIter it);

//     void evict();

// };

using KeyType = int;
using ValueType = int;

// class Node{
// public:
//     void setNext(int newNext){
//         next = newNext;
//     }
    
//     void setPrev(int newPrev){
//         prev = newPrev;
//     }
    
//     void setKey(int newKey){
//         key = newKey;
//     }

//     void setValue(int newValue){
//         value = newValue;
//     }

// private:
//     int prev;
//     int next;
//     KeyType key;
//     ValueType value; 
// };

// struct FreeListNode{
//     FreeListNode* prev;
//     FreeListNode * next;
//     int nodeIndex;

    
//     FreeListNode() : prev(nullptr), nodeIndex(-1), next(nullptr) {}

//     FreeListNode(FreeListNode* prev, int nodeIndex, FreeListNode* next) : prev(prev), nodeIndex(nodeIndex), next(next) {}
// };


// class FreeList{
//     FreeList(size_t size) : head (nullptr){
//         auto currNode = head;
//         for(size_t i = 0; i < size; ++i){
//             auto nextNode = new FreeListNode(currNode, static_cast<int>(i), nullptr);
//             currNode->next = nextNode;
//             currNode = nextNode;
//         }
//     }

//     // this class should only be created with the custom ctor, and be destructed, i see no good reason to make it copyable or moveable or defualt constructable, imagine the bugs...
//     FreeList() = delete;
//     FreeList(const FreeList&) = delete;
//     FreeList& operator=(const FreeList&) = delete;
//     FreeList(FreeList&&) = delete;
//     FreeList& operator=(FreeList&&) = delete;
    
//     ~FreeList(){
//         auto curr = head;
//         while(curr){
//             auto next = curr->next;
//             delete curr;
//             curr = next;
//         }
//     }
// private:
//     FreeListNode* head;

//     bool empty() const {
//         return head->nodeIndex == -1;
//     }
// };





// class LRUCache {
// public:
//     using KeyType = int;
//     using ValueType = int;

//     LRUCache() = delete; // an LRU cache has to have a capacity!

//     explicit LRUCache(size_t capacity);
    
//     std::optional<int> get(KeyType key); 

//     void put(KeyType key, ValueType value);
// private:
//     size_t capacity_;
//     int* memory;
//     FreeListNode freelist_head_;
//     std::unordered_map<KeyType, int> map_;

//     void bump(int nodeIndex);
// };

struct AllocatedBlock{
    unsigned int prev;
    int key;
    int val;
    unsigned int next;
};

struct FreeBlock{
    unsigned int prev;
    int padding[2];
    unsigned int next;
};

union Block{
    AllocatedBlock allocatedBlock;
    FreeBlock freeBlock;
};

class LRUCache {
public:
    using KeyType = int;
    using ValueType = int;

    static constexpr uint32_t BLOCK_NULLPTR = 0xFFFFFFFF; 

    LRUCache() = delete; // an LRU cache has to have a capacity!

    explicit LRUCache(const uint32_t capacity);
    
    std::optional<int> get(KeyType key); 

    void put(KeyType key, ValueType value);
private:
    const uint32_t capacity_;
    Block* memory_;
    uint32_t freelist_head_index_;
    uint32_t lru_head_index_;
    uint32_t lru_tail_index_;
    std::unordered_map<KeyType, uint32_t> map_; // holds key, and the index of the corrosponding AllocaedBlock 

    static constexpr uint32_t MAX_CAPACITY = 0xFFFFFFFF - 1; 


    void bump(uint32_t nodeIndex);
};

