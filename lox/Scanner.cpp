#include "Scanner.hpp"
#include "Lox.hpp"

bool Scanner::isAtEnd()
{
    return current >= source.length();
}

std::vector<Token> Scanner::scanTokens()
{
    return tokens;
}

void Scanner::scanToken()
{
    char c = advance();
    switch (c) {
      case '(': addToken(TokenType::LEFT_PAREN); break;
      case ')': addToken(TokenType::RIGHT_PAREN); break;
      case '{': addToken(TokenType::LEFT_BRACE); break;
      case '}': addToken(TokenType::RIGHT_BRACE); break;
      case ',': addToken(TokenType::COMMA); break;
      case '.': addToken(TokenType::DOT); break;
      case '-': addToken(TokenType::MINUS); break;
      case '+': addToken(TokenType::PLUS); break;
      case ';': addToken(TokenType::SEMICOLON); break;
      case '*': addToken(TokenType::STAR); break; 
    }
}

void Scanner::addToken(TokenType tType)
{
    addToken(tType, nullptr);
}

void Scanner::addToken(TokenType tType, std::string literal)
{
    std::string text = source.substr(start, current);
    Token temp(tType, text, literal, line);
}

char Scanner::advance()
{
    return source.at(current++);
}