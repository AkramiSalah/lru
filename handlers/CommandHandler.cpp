#include "CommandHandler.hpp"
#include <optional>


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

// helpers
std::optional<int> CommandHandler::deserializeInt(const std::string& token){
    try{
        return std::stoi(token);
    }catch(...){
        return std::nullopt;
    }
}


std::optional<std::string> CommandHandler::serializeInt(int n){
    try{
        return std::to_string(n);
    }catch(...){
        return std::nullopt;
    }
    
}

std::string CommandHandler::handleGet(const std::vector<std::string>& command){
    std::string errorString = "Usage: GET <key>\n";

    if(command.size() < 2){
        return errorString + "didn't get a key. try again.";
    }else if(command.size() > 2){
        return errorString  + "got too many arguments, try again.";
    }

    auto deserializedKey = deserializeInt(command[1]);
    if(!deserializedKey){
        return "ERROR: key was not able to be proccesed, make sure its of an int type";
    }

    auto value = cache_.get(deserializedKey.value());
    if(value){
        auto serializedValue = serializeInt(value.value());
        if(serializedValue) return serializedValue.value();
        return "ERROR: the key was found, but the value could not be serialized :(";
    }

    return "Not Found: this value was either never in the cache, or was in the cache, but was evicted.";
}

std::string CommandHandler::handleSet(const std::vector<std::string>& command){
    std::string errorString = "Usage: SET <key> <value>\n";
    if(command.size() < 3){
        return errorString + "didn't get a key, or a value, or both. try again.";
    }else if(command.size() > 3){
        return errorString + "got too many arguments, try again.";
    }

    auto deserializedKey = deserializeInt(command[1]);
    if(!deserializedKey){
        return "ERROR: key was not able to be proccesed, make sure its of an int type";
    }

    auto deserializedValue= deserializeInt(command[2]);
    if(!deserializedValue){
        return "ERROR: value was not able to be proccesed, make sure its of an int type";
    }

    cache_.put(deserializedKey.value(), deserializedValue.value());
    return "key value pair was set";
}