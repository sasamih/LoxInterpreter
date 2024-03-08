#include "Scanner.hpp"
#include "Lox.hpp"
#include "error_handler.hpp"

#include <iostream>

Scanner::Scanner(std::string source) : source(source)
{
    start = 0;
    current = 0;
    line = 1;

    keywords.insert({"and", TokenType::AND});
    keywords.insert({"class", TokenType::CLASS});
    keywords.insert({"else", TokenType::ELSE});
    keywords.insert({"false", TokenType::FALSE});
    keywords.insert({"for", TokenType::FOR});
    keywords.insert({"fun", TokenType::FUN});
    keywords.insert({"if" , TokenType::IF});
    keywords.insert({"nil", TokenType::NIL});
    keywords.insert({"or", TokenType::OR});
    keywords.insert({"print", TokenType::PRINT});
    keywords.insert({"return", TokenType::RETURN});
    keywords.insert({"super", TokenType::SUPER});
    keywords.insert({"this", TokenType::THIS});
    keywords.insert({"true", TokenType::TRUE});
    keywords.insert({"var", TokenType::VAR});
    keywords.insert({"while", TokenType::WHILE});
}

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
      case '"':
        string();
        break;
      default:
        if (isDigit(c))
        {
            number();
        }
        else if (isAlpha(c))
        {
            identifier();
        }
        else
        {
            error(line, "Unexpected character");
        }
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

char Scanner::peekNext()
{
    if (current+1 >= source.length()) return '\0';
    return source.at(current+1);
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
        {
            line++;
        }
        advance();
    }

    if (isAtEnd())
    {
        error(line, "Unterminated string");
    }

    advance();

    std::string value = source.substr(start + 1, current - 2);
    addToken(TokenType::STRING, value);
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isAlphaNumeric(char c)
{
    return isDigit(c) || isAlpha(c);
}

void Scanner::number()
{
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext()))
    {
        advance();
    }

    while (isDigit(peek())) advance();

    addToken(TokenType::NUMBER, source.substr(start, current));
}

void Scanner::identifier()
{
    while (isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current);
    auto it = keywords.find(text);

    TokenType type;
    if (it != keywords.end())
    {
        type = it->second;
    }
    else
    {
        type = TokenType::IDENTIFIER;
    }

    addToken(type);
}