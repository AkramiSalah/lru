#pragma once
#include <cstdint>
#include <optional>
#include <stdexcept>

static constexpr uint32_t BLOCK_NULLPTR = 0xFFFFFFFF;

template <typename T>
class BlockPool{
public:
    static constexpr uint32_t MAX_CAPACITY = 0xFFFFFFFF - 1; 

    explicit BlockPool(uint32_t blockCount);
    ~BlockPool();


    // Theres no reason to make this copyable. it defeats the whole purpse
    // For future me: pls.. if you ever need these, pls.. reconsider.
    BlockPool(const BlockPool&) = delete;
    BlockPool& operator=(const BlockPool&) = delete;
    
    // Might implement later, not needed right now. YAGNI.
    BlockPool& operator=(BlockPool&&) = delete;
    BlockPool(BlockPool&&) = delete;

    struct FreeBlock {
    uint32_t next;
    };

    struct UserBlock {
        char payload[sizeof(T)];
    };

    union Slot {
        UserBlock userBlock;
        FreeBlock freeBlock;
    };

    std::optional<uint32_t> allocBlock();
    UserBlock& getBlock(uint32_t blockIndex);
    // void freeBlock(uint32_t blockIndex); // Youd think i need it, but i really dont! so YAGNI. explination in the relevant commit, check git blame.

    // the fact that this Block allocator is used for an LRUCache makes it so that i never ever have to free a block
    // since when the LRUCache is at full capacity and a new item is to be inserted i reuse the least recently used block.
    
private:
    const uint32_t blockCount;
    Slot* memory_;
    uint32_t freelist_head_index_;
};
template<typename T>
auto BlockPool<T>::getBlock(uint32_t blockIndex) -> UserBlock&{
    // this function assumes valid blockIndex.
    return memory_[blockIndex].userBlock; 
}

template<typename T>
std::optional<uint32_t> BlockPool<T>::allocBlock(){
    if(freelist_head_index_ == BLOCK_NULLPTR){
        return std::nullopt;
    }

    uint32_t blockIndex = freelist_head_index_;
    freelist_head_index_ = memory_[blockIndex].freeBlock.next;

    return blockIndex;
}

template<typename T>
BlockPool<T>::BlockPool(uint32_t blockCount) : blockCount(blockCount), freelist_head_index_(0){
    if(blockCount == 0) throw std::invalid_argument("block count must be greater than 0 !!!");
    if(blockCount > MAX_CAPACITY) throw std::invalid_argument("capacity must be smaller than the maximum unsigned 32bit integer!!!");

    memory_ = new Slot[blockCount];
    for(uint32_t i = 0; i < blockCount - 1; ++i){
        memory_[i].freeBlock.next =  i+1;
    }
    memory_[blockCount - 1].freeBlock.next = BLOCK_NULLPTR;
}

template<typename T>
BlockPool<T>::~BlockPool() {
    delete[] memory_; 
}