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
    const char* getUsageString() const;
};