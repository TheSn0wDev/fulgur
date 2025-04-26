#pragma once
#include <iostream>
#include <string>

class Logger {
public:
    static void info(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }

    static void warn(const std::string& message) {
        std::cout << "[WARN] " << message << std::endl;
    }

    static void error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }

    static void debug(const std::string& message) {
        std::cout << "[DEBUG] " << message << std::endl;
    }
};