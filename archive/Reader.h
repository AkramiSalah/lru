// reader has a stream it reads form : most likely std::cin
// it has rules the user should follow

#pragma once
#include <iostream>
#include <vector>

class Reader{
public:
    std::string readCommand();
    explicit Reader(std::istream& inStream) : inStream(inStream){}
private:
    std::istream& inStream;
    void printUsageString() const;
};