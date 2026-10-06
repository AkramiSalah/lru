#include "CommandHandler.hpp"
#include "../backend/LRUCache.hpp"

using namespace CommandHandler;
std::string handleGet(const std::vector<std::string>& command){
    std::string errorString = "Usage: GET <key>\n";

    if(command.size() < 2){
        return errorString + "didn't get a key. try again.";
    }else if(command.size() > 2){
        return errorString  + "got too many arguments, try again.";
    }

    // TODO : actual logic here....
    return "yipee";

}

std::string handleSet(const std::vector<std::string>& command){
    std::string errorString = "Usage: SET <key> <value>\n";
    if(command.size() < 3){
        return errorString + "didn't get a key, or a value, or both. try again.";
    }else if(command.size() > 3){
        return errorString + "got too many arguments, try again.";
    }

    // TODO : actual logic here....
    return "yipeee";

}

std::string CommandHandler::handleCommand(const std::vector<std::string>& command){

    if(command.size() == 0){
        return ""; // i want to allow the user to just press enter to go down a few lines without spitting errors in his face.
    }
    else if(command[0] == "GET"){
        return handleGet(command);
    }else if (command[0] == "SET"){
        return handleSet(command);
    }

    //else
    return "Usage:\n SET <key> <value>\n GET <key>";
    
}