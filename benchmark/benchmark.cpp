#include "Timer.hpp"
#include "../backend-custom/LRUCache.hpp"
#include "../backend-standard/LRUCache.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>

struct BenchResult {
    double initMs = 0.0;
    double populateMs = 0.0;
};


template<typename CacheType>
void populateCache(CacheType& cache, int itemCount){
    if(itemCount <= 0) return;
    for(int i = 0; i < itemCount; ++i){
        cache.put(i, i);
    }
}

template<typename CacheType>
BenchResult benchCache(std::string_view cacheName, uint32_t capacity, uint32_t insertCount) {
    if (capacity == 0 || insertCount == 0) return {-1.0, -1.0};

    Timer initTimer("  [" + std::string(cacheName) + "] Init");
    CacheType cache(capacity);
    double initMs = initTimer.printElapsed();

    Timer popTimer("  [" + std::string(cacheName) + "] Populate");
    populateCache(cache, insertCount);
    double popMs = popTimer.printElapsed();

    return {initMs, popMs};
}

void runBenchmarks(uint32_t capacity, uint32_t insertCount, std::string_view label){
    std::cout   << '\n'
                << "========================================\n"
                << " Benchmark: " << label << '\n'
                << " (Capacity: " << capacity << ", Items: " << insertCount << ")\n"
                << "----------------------------------------\n";


    BenchResult customResult   = benchCache<custom::LRUCache>("Custom  ", capacity, insertCount);
    BenchResult standardResult = benchCache<standard::LRUCache>("standard", capacity, insertCount);
    std::cout << "----------------------------------------\n";
    if (customResult.populateMs > 0.0) {
        double popSpeedup = standardResult.populateMs / customResult.populateMs;
        std::cout << " Populate : Custom is " << popSpeedup << "x faster\n";
    }
    
    double customTotal = customResult.initMs + customResult.populateMs;
    double standardTotal = standardResult.initMs + standardResult.populateMs;
    if (customTotal > 0.0) {
        double totalSpeedup = standardTotal / customTotal;
        std::cout << " Total    : Custom is " << totalSpeedup << "x faster\n";
    }
}


struct TestCase {
    std::string_view label;
    uint32_t capacity;
    uint32_t inserts;
};

int main(){
    constexpr TestCase cases[] = {
        // High eviction rate
        {"Extreme Eviction",          100, 1'000'000},
        {"10x Eviction",           10'000,   100'000},
        {"2x Eviction",            10'000,    20'000},
        
        // Exact fit
        {"Exact Fit (1M)",      1'000'000, 1'000'000},
        {"Exact Fit (100k)",      100'000,   100'000},
        {"Exact Fit (10k)",        10'000,    10'000},

        // Zero evictions
        {"Sparse Cache (1% used)",  1'000'000,    10'000},
        {"Sparse Cache (10% used)",   100'000,    10'000},
    };

    for (const auto& test : cases) {
        runBenchmarks(test.capacity, test.inserts, test.label);
    }

    return 0;
}