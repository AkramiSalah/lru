#include "Reader.hpp"
#include <sstream>
#include <string>

Reader::Reader(std::istream& is) : is_(is){ } 

std::vector<std::string> Reader::readCommand(){
    std::vector<std::string> commandWords;
    std::string line;

    if(std::getline(is_, line)){
        std::istringstream iss(line);
        std::string word;
        while(iss >> word){
            commandWords.push_back(word);
        }
    }

    return commandWords;
}


