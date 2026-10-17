#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <string_view>

class Timer {
public:
    explicit Timer(std::string_view label = "")
        : m_label(label),
          m_start(std::chrono::steady_clock::now()) {}

    double elapsedMs() const {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double, std::milli>(now - m_start).count();
    }

    double printElapsed() const {
        double ms = elapsedMs();
        std::cout << m_label << " - " << ms << "ms\n";
        return ms;
    }

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;

private:
    const std::string m_label;
    const std::chrono::time_point<std::chrono::steady_clock> m_start;
};