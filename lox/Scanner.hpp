#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>

#include "Lox.hpp"

class Scanner {
    private:
        std::string source;
        std::vector<Token> tokens;

        int start;
        int current;
        int line;

        bool isAtEnd();
        void scanToken();
        void addToken(TokenType tType);
        void addToken(TokenType tType, std::string literal);
        char advance();

    public:
        Scanner(std::string source) : source(source)
        {
            start = 0;
            current = 0;
            line = 1;
        }

        std::vector<Token> scanTokens();
};

#endif