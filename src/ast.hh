#ifndef INCLUDE_AST_HH
#define INCLUDE_AST_HH

#include "token.hh"
#include <vector>

enum class ASTNodeType: int
{
    Expression,
    Identifier,
    LetStatement,
    Program,
    Statement
};


class ASTNode
{
public:
    ASTNodeType type;
};


class Expression: public ASTNode
{
public:
    Token token;
};


class Identifier: public Expression
{
public:
    Identifier(Token token, Expression *value);

    Expression *value;
};


class Integer: public Expression
{
public:
    Integer(Token token);
private:
    long long value;
};


class Program: public ASTNode
{
public:
    std::vector<Expression* > expressions;

    Program();
};

#endif
