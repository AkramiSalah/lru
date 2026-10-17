#include "Timer.hpp"
#include "../backend-custom/LRUCache.hpp"
#include "../backend-standard/LRUCache.hpp"

#include <iostream>
#include <vector>
#include <random>

class WorkloadGenerator{
public:
    enum class Op{ GET, PUT };

    struct Request{
        Op op;
        int key;
        int val;
    };

    explicit WorkloadGenerator(int capacity)
        : gen(rd()),
          boolDist(0.5),
          keyDist(0, 2 * capacity - 1){}

    Request next(){
        int key = keyDist(gen);
        Op op = boolDist(gen) ? Op::GET : Op::PUT;
        return{op, key, key};
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution boolDist;
    std::uniform_int_distribution<int> keyDist;
};


template <typename CacheType>
double benchmarkCache(CacheType& cache, const std::vector<WorkloadGenerator::Request>& requests){
    Timer timer;
    volatile int sink = 0; // trick to make optimizer not optimize this away

    for (const auto& req : requests){
        if (req.op == WorkloadGenerator::Op::GET){
            sink = cache.get(req.key).value_or(0); // value truly doesnt matter so value or zero.
        }
        else{
            cache.put(req.key, req.val);
        }
    }

    return timer.elapsedMs();
}

template<typename CacheType>
void populateCache(CacheType& cache, int itemCount){
    if(itemCount <= 0) return;
    for(int i = 0; i < itemCount; ++i){
        cache.put(i, i);
    }
}

int main(){
    static constexpr int S_CAPACITY = 1'000'000;
    static constexpr int S_NUM_OPS  = 1'000'000;

    std::cout << "Generating " << S_NUM_OPS << " requests...\n";
    WorkloadGenerator workload(S_CAPACITY);
    std::vector<WorkloadGenerator::Request> requests;
    requests.reserve(S_NUM_OPS);

    for (int i = 0; i < S_NUM_OPS; ++i){
        requests.push_back(workload.next());
    }


    // benchmark custom::LRUCache
    custom::LRUCache customCache(S_CAPACITY);
    populateCache(customCache, S_CAPACITY);
    double customMs = benchmarkCache(customCache,requests);


    // benchmark standard::LRUCache
    standard::LRUCache standardCache(S_CAPACITY);
    populateCache(standardCache, S_CAPACITY);
    double standardMs = benchmarkCache(standardCache,requests);



    std::cout << "\n--- Benchmark Results (" << S_NUM_OPS << " ops) ---\n";
    std::cout << "Custom Backend  : " << customMs << " ms\n";
    std::cout << "Standard Backend: " << standardMs << " ms\n";

    double slower = std::max(standardMs, customMs);
    double faster = std::min(standardMs, customMs);
    std::string winner = customMs < standardMs ? "Custom" : "Standard";

    double percentageDiff = slower/faster * 100.0;
    percentageDiff = percentageDiff;

    std::cout << "Result: " << winner << " is " << percentageDiff - 100 << "% faster!\n";

    return 0;
}