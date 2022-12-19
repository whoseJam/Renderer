#include <iostream>

#include "Logger.h"

using namespace std;

void Logger::error(const string& msg) {
    cout << "Error : " << msg << "\n";
    exit(-1);
}

void Logger::warning(const string& msg) {
    cout << "Warning : " << msg << "\n";
}

void Logger::warning(const string& name, const string& value) {
    std::cout << "Warning : ";
    std::cout << name << " : " << value << "\n";
}

void Logger::warning(const std::string& name, int value) {
    std::cout << "Warning : ";
    std::cout << name << " : " << value << "\n";
}