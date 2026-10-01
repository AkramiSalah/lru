// reader has a stream it reads form : most likely std::cin
// it has rules the user should follow

#pragma once
#include <iostream>
#include <vector>

class reader{
public:
    std::string readCommand();
    explicit reader(std::istream& inStream) : inStream(inStream){}
private:
    std::istream& inStream;
    static constexpr int GET_COMMAND_LENGTH = 2;
    static constexpr int SET_COMMAND_LENGTH = 3;
    

    void printUsage() const;

    bool validCommand(std::vector<std::string>& commandWords) const;
};