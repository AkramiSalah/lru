cmake_minimum_required(VERSION 3.20)
project(lru LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to an optimised build (the benchmarks are meaningless at -O0).
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra)


# One static library per component (LinkedList.hpp and BlockPool.hpp are header-only).
add_library(backend_standard STATIC backend-standard/LRUCache.cpp)
add_library(backend_custom  STATIC backend-custom/LRUCache.cpp)
add_library(frontend STATIC frontend/Reader.cpp)
add_library(handlers STATIC handlers/CommandHandler.cpp)

target_link_libraries(handlers PUBLIC backend_custom)

# CLI
add_executable(lru main.cpp)
target_link_libraries(lru PRIVATE frontend handlers)

# Tests
add_executable(lru_tests tests/test_lru.cpp)
target_link_libraries(lru_tests PRIVATE backend_custom)
target_compile_options(lru_tests PRIVATE -UNDEBUG) # -UNDEBUG makes asserts work again 


# Benchmarks 
add_executable(lru_bench benchmarks/benchmark.cpp)
target_link_libraries(lru_bench PRIVATE backend_custom backend_standard)

add_executable(lru_sim_bench benchmarks/simulated_workload_bench.cpp)
target_link_libraries(lru_sim_bench PRIVATE backend_custom backend_standard)