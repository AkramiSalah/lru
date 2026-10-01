#include "reader.h"


std::string reader::readCommand(){
    std::vector<std::string> commandWords;
    std::string word;
    std::string fullCommand; // this is just for now, later we will just build a set/get commnad and return it form here. or something similar.


    while(inStream >> word){
        commandWords.push_back(word);
        if(inStream.peek() == '\n') break;
    }

    if(validCommand(commandWords)){
        return fullCommand;
    }

    return "yikes";
}

void reader::printUsage() const{
    std::cout << "Usage:\n SET <key> <value>\n GET <key>\n";
}


bool reader::validCommand(std::vector<std::string>& commandWords) const{
        if(commandWords.size() != SET_COMMAND_LENGTH && commandWords.size() != GET_COMMAND_LENGTH ) return false;
        if(commandWords.size() == SET_COMMAND_LENGTH && commandWords[0] == "SET" ){
            int key;
            int value;
            try
            {
                key = std::stoi(commandWords[1]);
                value = std::stoi(commandWords[2]);
                return true;
            }
            catch(...){
                return false;
            }
        }
        else if(commandWords.size() == GET_COMMAND_LENGTH && commandWords[0] == "GET" ){
            int key;
            try
            {
                key = std::stoi(commandWords[1]);
                return true;
            }
            catch(...){
                return false;
            }
        }
        return false;
    }