#pragma once
#include <cstdint>
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
        T payload;
    };

    union Slot {
        UserBlock userBlock;
        FreeBlock freeBlock;
    };

    uint32_t allocBlock();
    UserBlock& getBlock(uint32_t blockIndex);
    const UserBlock& getBlock(uint32_t blockIndex) const;

    bool full() const;
    // void freeBlock(uint32_t blockIndex); // Youd think i need it, but i really dont! so YAGNI. explination in the relevant commit, check git blame.

    // the fact that this Block allocator is used for an LRUCache makes it so that i never ever have to free a block
    // since when the LRUCache is at full capacity and a new item is to be inserted i reuse the least recently used block.
    
private:
    const uint32_t m_blockCount;
    Slot* m_data;
    uint32_t m_freelistHeadIndex;
};

template<typename T>
inline bool BlockPool<T>::full() const{
    return m_freelistHeadIndex == BLOCK_NULLPTR;
}

template<typename T>
auto BlockPool<T>::getBlock(uint32_t blockIndex) -> UserBlock&{
    // this function assumes valid blockIndex.
    return m_data[blockIndex].userBlock; 
}

template<typename T>
auto BlockPool<T>::getBlock(uint32_t blockIndex) const -> const UserBlock&{
    // this function assumes valid blockIndex.
    return m_data[blockIndex].userBlock; 
}

template<typename T>
uint32_t BlockPool<T>::allocBlock(){
    if(full()){
        return BLOCK_NULLPTR;
    }

    uint32_t blockIndex = m_freelistHeadIndex;
    m_freelistHeadIndex = m_data[blockIndex].freeBlock.next;

    return blockIndex;
}

template<typename T>
BlockPool<T>::BlockPool(uint32_t blockCount) : m_blockCount(blockCount), m_freelistHeadIndex(0){
    if(blockCount == 0) throw std::invalid_argument("block count must be greater than 0 !!!");
    if(blockCount > MAX_CAPACITY) throw std::invalid_argument("capacity must be smaller than the maximum unsigned 32bit integer!!!");

    m_data = new Slot[blockCount];
    for(uint32_t i = 0; i < blockCount - 1; ++i){
        m_data[i].freeBlock.next =  i+1;
    }
    m_data[blockCount - 1].freeBlock.next = BLOCK_NULLPTR;
}

template<typename T>
BlockPool<T>::~BlockPool() {
    delete[] m_data; 
}