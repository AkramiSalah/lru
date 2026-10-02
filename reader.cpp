#include "reader.h"
#include "get.h"

std::string reader::readCommand(){
    // TODO: make this use string view vector instead. change the get,set classes accordingly
    std::vector<std::string> commandWords;
    std::string word;


    while(inStream >> word){
        commandWords.push_back(word);
        if(inStream.peek() == '\n') break;
    }

    auto get_command = get::deserialize(commandWords);
    return get_command->serialize();


    // return getUsageString();
}

const char* reader::getUsageString() const{
    return "Usage:\n SET <key> <value>\n GET <key>\n";
}