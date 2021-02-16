#ifndef INCLUDE_AST_HH
#define INCLUDE_AST_HH

#include "token.hh"
#include <vector>

enum class ASTNodeType: int
{
    Expression,
    Assignment,
    Integer,
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


class Assignment: public Expression
{
public:
    Assignment(Token token, Expression *value);

    Expression *value;
};


class Integer: public Expression
{
public:
    Integer(Token token);
    long long value;
};


class Program: public ASTNode
{
public:
    std::vector<Expression* > expressions;

    Program();
};

#endif
