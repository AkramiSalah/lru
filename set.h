#pragma once
#include <memory>
#include <vector>
#include <string>

class set{
public:
    int key;
    int value;

    static std::unique_ptr<set> deserialize(const std::vector<std::string>& commandWords);

private:
    static constexpr int SET_COMMAND_LENGTH = 3;    
};