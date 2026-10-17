#include "frontend/Reader.hpp"
#include "handlers/CommandHandler.hpp"
#include <iostream>

int main(){
    Reader reader{std::cin};
    LRUCache cache(10);
    CommandHandler commandHandler(cache);
    std::cout << "> ";
    while(true){
        std::string response = commandHandler.handleCommand(reader.readCommand());
        std::cout << "|--> "<< response << "\n";
        std::cout << "> ";
    }
    return 0;
}