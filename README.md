# lru

## Current Goals:
* create an in memory key value storage with LRU as an eviction policy.
* create a front-end CLI tool to get/set key value pairs

## Possible Future Goals:
* achieve persistance
* add multithreading support
* seperate into server-client model
* use custom memory allocation (slab allocator adjacent)

## Current Working Idea:
- have a Queue of commands which are either set or get objects.
- at runtime just go though the Queue until its empty.

- set/get object:
    - are created/serialized from the cli's input
    - can be consumed by the (in planning) storage class.


### compilation commad:
g++ -std=c++20 -Wall -Wextra -g main.cpp -o lru 