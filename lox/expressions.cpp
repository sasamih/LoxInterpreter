#include "expressions.hpp"

Binary::Binary(Expr left, Token op, Expr right) : left(left), op(op), right(right) { }