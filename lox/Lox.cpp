#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Lox.hpp"

std::vector<std::string> scanTokens(std::string& source)
{
    std::vector<std::string> tokens;

    size_t pos = source.find(' ');
    size_t initialPos = 0;

    // Decompose statement
    while( pos != std::string::npos ) {
        tokens.push_back(source.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = source.find(' ', initialPos);
    }

    // Add the last one
    tokens.push_back( source.substr(initialPos, std::min( pos, source.size() ) - initialPos + 1 ) );

    return tokens;
}

void run(std::string source)
{
    std::vector<std::string> tokens = scanTokens(source);

    // For now, just print the tokens.
    for (auto& token : tokens) {
        std::cout << token << std::endl;
    }
}

void runPrompt()
{
    for(;;)
    {
        std::cout << "> ";
        std::string inLine;
        std::cin >> inLine;
        if (inLine == "quit") break;
        run(inLine);
    }
}

void runFile(std::string path)
{
    std::ifstream in(path, std::ios::binary);

    if (in.is_open())
    {
        std::ostringstream streamBuffer;
        streamBuffer << in.rdbuf();
        std::string str = streamBuffer.str();
        run(str);
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        std::cout << "Usage: lox [script]" << std::endl;
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        runPrompt();
    }

    return 0;
}