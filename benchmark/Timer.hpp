#include <chrono>
#include <iostream>
#include <ratio>
#include <string>
#include <string_view>

class Timer{
public:
    Timer(std::string_view logMessage = "Timer") : m_logMessage(logMessage), m_startTimepoint(std::chrono::steady_clock::now()){}

    ~Timer(){
        const auto end = std::chrono::steady_clock::now();
        const std::chrono::duration<double,  std::milli> diff = end - m_startTimepoint;
        std::cout << m_logMessage << " - " <<  diff << "\n";
    }

    // it has become the theme of this codebase, but i seriously can't think of a single reason as to why the Timer needs to be moveable/copyable 
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;
private:
    const std::string m_logMessage;
    const std::chrono::time_point<std::chrono::steady_clock> m_startTimepoint; // might be the longest type i ever wrote ever..
};