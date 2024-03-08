#include "Scanner.hpp"
#include "Lox.hpp"
#include "error_handler.hpp"

#include <iostream>

bool Scanner::isAtEnd()
{
    return current >= source.length();
}

std::vector<Token> Scanner::scanTokens()
{
    while(!isAtEnd())
    {
        start = current;
        scanToken();
    }

    tokens.push_back(Token(TokenType::LEOF, "", "", line));
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
      case '/':
        if (!match('/'))
        {
            addToken(TokenType::SLASH); break;
        }
        else
        {
            while (peek() != '\n' && !isAtEnd()) 
            {
                advance();
            }
        }
        break;
      case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
      case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
      case '<':
        addToken(match('<') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
      case '>':
        addToken(match('>') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
      case ' ':
      case '\r':
      case '\t':
        break;
      case '\n':
        line++;
        break;
      default:
        error(line, "Unexpected character");
        break;
    }
}

void Scanner::addToken(TokenType tType)
{
    addToken(tType, "");
}

void Scanner::addToken(TokenType tType, std::string literal)
{
    std::string text = source.substr(start, current);
    Token temp(tType, text, literal, line);
    tokens.push_back(temp);
}

char Scanner::advance()
{
    return source.at(current++);
}

bool Scanner::match(char expected)
{
    if (isAtEnd())
        return false;
    if (source.at(current) != expected) 
        return false;

    current++;
    return true;
}

char Scanner::peek()
{
    if (isAtEnd()) return '\0';
    return source.at(current);
}