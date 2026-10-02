#include "get.h"
#include <format>

std::unique_ptr<get> get::deserialize(const std::vector<std::string>& commandWords){
    if(commandWords.size() == GET_COMMAND_LENGTH && commandWords[0] == "GET" ){
        int key;
        try
        {
            key = std::stoi(commandWords[1]);
            return std::make_unique<get>(key);
        }
        catch(...){
            return nullptr; // nullptr will be treaded as a no-op later on in the queue, this means itll fail silently, not too good.
        }
    }
    return nullptr;
}

const std::string get::serialize() const{
    return std::format("GET {}", key);
}
