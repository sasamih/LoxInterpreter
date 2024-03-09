#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include "Lox.hpp"

class Expr
{
    protected:

    public:
};

class Binary : public Expr
{
    protected:
        Expr left;
        Token op;
        Expr right;
    public:
        Binary(Expr left, Token op, Expr right);
};

#endif