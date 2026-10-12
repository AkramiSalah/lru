#pragma once
#include <cstdint>
#include <optional>
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

    
    uint32_t getTailIndex() const;
    uint32_t getHeadIndex() const;
    bool full() const;
    
    Node& getNode(uint32_t blockIndex);
    
    std::optional<uint32_t> createNode(KeyType key, ValueType value);

    void detachNode(uint32_t blockIndex);

    void push_back(uint32_t blockIndex);
    
    void push_front(uint32_t blockIndex);

private:
    uint32_t headIndex_ = BLOCK_NULLPTR;
    uint32_t tailIndex_ = BLOCK_NULLPTR;
    BlockPool<Node> blockPool_;
};