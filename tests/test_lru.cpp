#include <iostream>
#include <cassert>
#include "../custom-backend/LRUCache.hpp"

void test_capacity_one() {
    custom::LRUCache cache(1);

    cache.put(2, 1);
    assert(cache.get(2).value_or(-1) == 1);

    cache.put(3, 2); // evicts 2
    assert(cache.get(2).value_or(-1) == -1);
    assert(cache.get(3).value_or(-1) == 2);

    std::cout << "[PASS] Capacity 1\n";
}

void test_update_does_not_evict() {
    custom::LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(1, 10); // bumps 1 again, changes val to 10
    cache.put(3, 3);  // evits 2

    assert(cache.get(2).value_or(-1) == -1);
    assert(cache.get(1).value_or(-1) == 10);
    assert(cache.get(3).value_or(-1) == 3);

    std::cout << "[PASS] Update existing key preserves recency\n";
}

void test_get_refreshes_recency() {
    custom::LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1).value_or(-1) == 1); // 1 is now MRU, 2 is LRU

    cache.put(3, 3);                        // should evict 2

    assert(cache.get(2).value_or(-1) == -1);
    assert(cache.get(1).value_or(-1) == 1);
    assert(cache.get(3).value_or(-1) == 3);

    std::cout << "[PASS] Get refreshes recency\n";
}

int main() {

    test_capacity_one();
    test_update_does_not_evict();
    test_get_refreshes_recency();

    std::cout << "All edge case suites passed!\n Yipeeeeeeee\n";
    return 0;
}