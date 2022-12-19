#pragma once

#include <string>
#include <iostream>

class Logger {
public:
    static void error(const std::string& msg);
    static void warning(const std::string& msg);
    template <typename T>
    static void warning(const std::string& name, T value) {
        std::cout << "Warning : ";
        std::cout << name << " : " << static_cast<std::underlying_type<T>::type>(value) << "\n";
    }
    static void warning(const std::string& name, int value);
    static void warning(const std::string& name, const std::string& value);
};

