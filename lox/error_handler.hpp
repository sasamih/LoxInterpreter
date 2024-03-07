#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <string>

void error(int line, std::string message);
void report(int line, std::string where, std::string message);

#endif