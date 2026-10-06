#pragma once
#include <vector>
#include <string>
#include <optional>
#include "../backend/LRUCache.hpp"

class CommandHandler{
public:    
    explicit CommandHandler(LRUCache& cache) : cache_(cache){}

    std::string handleCommand(const std::vector<std::string>& command);
private:
    LRUCache& cache_;

    //helpers
    std::optional<int> deserializeInt(const std::string& token);

    std::string handleGet(const std::vector<std::string>& command);

    std::string handleSet(const std::vector<std::string>& command);

};