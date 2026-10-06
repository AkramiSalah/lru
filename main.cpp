#include "frontend/Reader.hpp"
#include "handlers/CommandHandler.hpp"
#include <iostream>

// std::string getInputString(){
//     std::string inputString;
//     std::getline(std::cin, inputString, '\n');
//     return inputString;
// }

int main(){
    Reader reader{std::cin};
    std::cout << "> ";
    while(true){
        std::string response = CommandHandler::handleCommand(reader.readCommand());
        std::cout << "|--> "<< response << "\n";
        std::cout << "> ";
    }
    return 0;
}
