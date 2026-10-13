#pragma once
#include <cstdint>
#include "BlockPool.hpp"

class LinkedList{
public:
    using KeyType = int;
    using ValueType = int;

    struct Node{
        uint32_t prev;
        KeyType key;
        ValueType value;
        uint32_t next;
    };

    explicit LinkedList(uint32_t capacity);

    ~LinkedList() = default;

    // Just like the BlockPool class, theres no reason to have this list be copyable. not for this project.
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // If this is ever needed then shoudl probably implement move ctor and move operator= for BlockPool before.
    // Not implemented because YAGNI.
    LinkedList(LinkedList&&) = delete;
    LinkedList& operator= (LinkedList&&) = delete;

    bool full() const { return blockPool_.full(); }
    
    uint32_t getTailIndex() const { return this->getNode(tailSentinel_).prev; }
    uint32_t getHeadIndex() const { return this->getNode(headSentinel_).next; }
    
    Node& getNode(uint32_t blockIndex) { return blockPool_.getBlock(blockIndex).payload; }
    const Node& getNode(uint32_t blockIndex) const { return blockPool_.getBlock(blockIndex).payload; }

    uint32_t createNode(KeyType key, ValueType value);

    void detachNode(uint32_t blockIndex);

    // void push_back(uint32_t blockIndex); code is below. commented out. reasons also below.
    
    void push_front(uint32_t blockIndex);

    uint32_t create_node_at_front(KeyType key, ValueType value);

private:
    uint32_t headSentinel_;
    uint32_t tailSentinel_;
    BlockPool<Node> blockPool_;
};

inline LinkedList::LinkedList(uint32_t capacity) : blockPool_(capacity + 2){
    headSentinel_ = blockPool_.allocBlock();
    tailSentinel_ = blockPool_.allocBlock();

    auto& head = getNode(headSentinel_);
    auto& tail = getNode(tailSentinel_);

    head.prev = BLOCK_NULLPTR;
    head.next = tailSentinel_;

    tail.prev = headSentinel_;
    tail.next = BLOCK_NULLPTR;
}


inline uint32_t LinkedList::createNode(KeyType key, ValueType value){
    auto blockIndex = blockPool_.allocBlock();
    if(blockIndex == BLOCK_NULLPTR) return BLOCK_NULLPTR;

    Node& node = getNode(blockIndex);
    node.prev = BLOCK_NULLPTR;
    node.key = key;
    node.value = value;
    node.next = BLOCK_NULLPTR;
    
    return blockIndex;
}


inline void LinkedList::detachNode(uint32_t blockIndex){
    // this function assumes that the block at blockIndex is allocated.
    auto& node = getNode(blockIndex);
    getNode(node.prev).next = node.next;
    getNode(node.next).prev = node.prev;
}

inline void LinkedList::push_front(uint32_t blockIndex){
    uint32_t oldHeadIndex = getNode(headSentinel_).next;

    Node& node = getNode(blockIndex);
    node.prev = headSentinel_;
    node.next = oldHeadIndex;

    getNode(oldHeadIndex).prev = blockIndex;
    getNode(headSentinel_).next = blockIndex;

}

inline uint32_t LinkedList::create_node_at_front(KeyType key, ValueType value){
    // this function assumes that the LL is NOT full
    auto blockIndex = blockPool_.allocBlock();

    Node& node = getNode(blockIndex);
    node.key = key;
    node.value = value;

    push_front(blockIndex);
    return blockIndex;
}

// NOTE: YAGNI overlooked, im not using this, stays commented out incase i change my mind soon, otherwise DELETE THIS !
// the fact of the matter is that im never pushing back, and if i am i have to move it to the front as soon as i push to back anyway... (LRU)

// void LinkedList::push_back(uint32_t blockIndex){
//     if(headIndex_ == BLOCK_NULLPTR && tailIndex_ == BLOCK_NULLPTR){
//         getNode(blockIndex).prev = BLOCK_NULLPTR;
//         getNode(blockIndex).next = BLOCK_NULLPTR;

//         headIndex_ = blockIndex;
//         tailIndex_ = blockIndex;
//     }
//     else if(headIndex_ != BLOCK_NULLPTR && tailIndex_ != BLOCK_NULLPTR){
//         getNode(blockIndex).prev = tailIndex_;
//         getNode(blockIndex).next = BLOCK_NULLPTR;

//         getNode(tailIndex_).next = blockIndex;
//         tailIndex_ = blockIndex;
//     }
//     else{
//         throw std::logic_error("somehow lru head is set but tail isnt, or exact opposite");
//     }
// }

