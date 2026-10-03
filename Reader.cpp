#include "Reader.h"
#include "Get.h"

std::string Reader::readCommand(){
    // TODO: make this use string view vector instead. change the get,set classes accordingly
    std::vector<std::string> commandWords;
    std::string word;


    while(inStream >> word){
        commandWords.push_back(word);
        if(inStream.peek() == '\n') break;
    }

    auto get_command = Get::deserialize(commandWords);
    if(get_command == nullptr){
        printUsageString();
        return readCommand();
    }
    return get_command->serialize();


    // return getUsageString();
}

void Reader::printUsageString() const{
    std::cout << "Usage:\n SET <key> <value>\n GET <key>\n";
}