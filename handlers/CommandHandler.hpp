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
    static constexpr char M_USAGE_STRING[] = "Usage: SET <key> <value>\n";

    LRUCache& cache_;

    //helpers
    std::optional<int> deserializeInt(const std::string& token);

    std::optional<std::string> serializeInt(int n);

    std::string handleGet(const std::vector<std::string>& command);

    std::string handlePut(const std::vector<std::string>& command);

};