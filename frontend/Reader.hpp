#pragma once
#include <vector>
#include <iostream>

class Reader{
public:
    explicit Reader(std::istream& is = std::cin);
    std::vector<std::string> readCommand();
private:
    std::istream& is_;
};