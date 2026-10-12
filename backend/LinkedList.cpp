#include "LinkedList.hpp"

LinkedList::LinkedList(uint32_t capacity) : blockPool_(capacity){}

uint32_t LinkedList::getTailIndex() const { return tailIndex_; }
uint32_t LinkedList::getHeadIndex() const { return headIndex_; }
bool LinkedList::full() const { return blockPool_.full(); }

auto LinkedList::getNode(uint32_t blockIndex) -> Node&{
    return *(Node*)(blockPool_.getBlock(blockIndex).payload);
}

std::optional<uint32_t> LinkedList::createNode(KeyType key, ValueType value){
    auto blockIndex = blockPool_.allocBlock();
    if(!blockIndex) return std::nullopt;

    Node& node = getNode(blockIndex.value());
    node.key = key;
    node.value = value;

    return blockIndex.value();
}

void LinkedList::detachNode(uint32_t blockIndex){
    // this function assumes that the block at blockIndex is allocated.
    auto& block = getNode(blockIndex);
    if(blockIndex == tailIndex_){
        tailIndex_ = block.prev;
    }

    if(blockIndex == headIndex_){
        headIndex_ = block.next;
    }

    if(block.next != BLOCK_NULLPTR){
        getNode(block.next).prev = block.prev;
    }

    if(block.prev != BLOCK_NULLPTR){
        getNode(block.prev).next = block.next;
    }

    block.prev = BLOCK_NULLPTR;
    block.next = BLOCK_NULLPTR;
}

void LinkedList::push_back(uint32_t blockIndex){
    if(headIndex_ == BLOCK_NULLPTR && tailIndex_ == BLOCK_NULLPTR){
        getNode(blockIndex).prev = BLOCK_NULLPTR;
        getNode(blockIndex).next = BLOCK_NULLPTR;

        headIndex_ = blockIndex;
        tailIndex_ = blockIndex;
    }
    else if(headIndex_ != BLOCK_NULLPTR && tailIndex_ != BLOCK_NULLPTR){
        getNode(blockIndex).prev = tailIndex_;
        getNode(blockIndex).next = BLOCK_NULLPTR;

        getNode(tailIndex_).next = blockIndex;
        tailIndex_ = blockIndex;
    }
    else{
        throw std::logic_error("somehow lru head is set but tail isnt, or exact opposite");
    }
}

void LinkedList::push_front(uint32_t blockIndex){
    if(headIndex_ == BLOCK_NULLPTR && tailIndex_ == BLOCK_NULLPTR){
        getNode(blockIndex).prev = BLOCK_NULLPTR;
        getNode(blockIndex).next = BLOCK_NULLPTR;

        headIndex_ = blockIndex;
        tailIndex_ = blockIndex;
    }
    else if(headIndex_ != BLOCK_NULLPTR && tailIndex_ != BLOCK_NULLPTR){
        getNode(blockIndex).prev = BLOCK_NULLPTR;
        getNode(blockIndex).next = headIndex_;

        getNode(headIndex_).prev = blockIndex;
        headIndex_ = blockIndex;
    }
    else{
        throw std::logic_error("somehow lru head is set but tail isnt, or exact opposite");
    }
}
