#pragma once
#include <memory>
#include <vector>
#include <string>

class Get{
public:
    int key;
    static std::unique_ptr<Get> deserialize(const std::vector<std::string>& commandWords);

    const std::string serialize() const;

private:
    static constexpr int GET_COMMAND_LENGTH = 2;
};