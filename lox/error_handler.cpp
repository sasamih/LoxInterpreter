#include <iostream>

#include "error_handler.hpp"

void error(int line, std::string message)
{
    report(line, "", message);
}

void report(int line, std::string where, std::string message)
{
    std::cout << "Line " << line << ": Error " << where << ": " << message << std::endl; 
}