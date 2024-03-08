#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>
#include <map>

#include "Lox.hpp"

class Scanner {
    private:
        std::string source;
        std::vector<Token> tokens;

        int start;
        int current;
        int line;
        std::map<std::string, TokenType> keywords;

        bool isAtEnd();
        void scanToken();
        void addToken(TokenType tType);
        void addToken(TokenType tType, std::string literal);
        char advance();
        bool match(char expected);
        char peek();
        char peekNext();
        void string();
        bool isDigit(char c);
        bool isAlpha(char c);
        bool isAlphaNumeric(char c);
        void number();
        void identifier();

    public:
        Scanner(std::string source);

        std::vector<Token> scanTokens();
};

#endif