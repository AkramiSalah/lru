#include "Reader.hpp"
#include <sstream>
#include <string>

Reader::Reader(std::istream& is) : m_inStream(is){ } 

std::vector<std::string> Reader::readCommand(){
    std::vector<std::string> commandWords;
    std::string line;

    if(std::getline(m_inStream, line)){
        std::istringstream iss(line);
        std::string word;
        while(iss >> word){
            commandWords.push_back(word);
        }
    }

    return commandWords;
}


