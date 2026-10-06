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
- have a core lru backend
- have a front end thats a primitive CLI with a limited set of commands:
     SET <key> <value>
     GET <key>
all single proccess single thread no need to over complicate.

current architecture:
CommandHandler has a backend
it receives commands from the front end

## Possible Furutre Improvements:
- migrate to a Python based fornt end with richer command options
- ditch the std lib based lru backend and make a custom one using free lists  


### compilation commad:
g++ -std=c++20 -Wall -Wextra main.cpp frontend/Reader.cpp handlers/CommandHandler.cpp -o lru
