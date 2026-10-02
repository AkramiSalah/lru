#include "set.h"

std::unique_ptr<set> set::deserialize(const std::vector<std::string>& commandWords){
    if(commandWords.size() == SET_COMMAND_LENGTH && commandWords[0] == "SET" ){
        int key;
        int value;
        try
        {
            key = std::stoi(commandWords[1]);
            value = std::stoi(commandWords[2]);
            return std::make_unique<set>(key, value);
        }
        catch(...){
            return nullptr; // nullptr will be treaded as a no-op later on in the queue, this means itll fail silently, not too good.
        }
    }
}
