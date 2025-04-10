#pragma once

#include <iostream>
#include <list>

// Game logger
class Logger
{
public:
    static Logger& instance() {
        static Logger instance;
        return instance;
    }

    void info(const std::string message);
    void danger(const std::string message);
    void combat(const std::string message);
    void warning(const std::string message);

    std::list<std::string>* getLogMessages();
private:
    std::list<std::string> logMessages;

    Logger();
    ~Logger();

    // Prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};