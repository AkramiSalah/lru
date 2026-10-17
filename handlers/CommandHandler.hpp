#pragma once
#include <vector>
#include <string>
#include <optional>
#include "../custom-backend/LRUCache.hpp"

using LRUCache= custom::LRUCache;
class CommandHandler{
public:    
    explicit CommandHandler(LRUCache& cache) : cache_(cache){}

    std::string handleCommand(const std::vector<std::string>& command);
private:
    static constexpr std::string_view S_GET_USAGE_STRING = "Usage:\n GET <key>\n";
    static constexpr std::string_view S_PUT_USAGE_STRING = "Usage:\n PUT <key> <value>\n";
    static constexpr std::string_view S_GENERAL_USAGE_STRING = "Usage:\n PUT <key> <value>\n GET <key>";

    LRUCache& cache_;

    //helpers
    std::optional<int> deserializeInt(const std::string& token);

    std::optional<std::string> serializeInt(int n);

    std::string handleGet(const std::vector<std::string>& command);

    std::string handlePut(const std::vector<std::string>& command);

};