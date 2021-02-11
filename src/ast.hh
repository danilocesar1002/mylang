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
    Identifier(Token token, std::wstring value);

    std::wstring value;
};


class LetStatement: public Statement
{
public:
    Token token;
    Identifier *name;
    Expression* value;

    LetStatement(Token token, Identifier *name = NULL, Expression* value = NULL);
};


class Program: public ASTNode
{
public:
    std::vector<Expression* > expressions;

    Program();
};


class Statement: public ASTNode
{
public:
    Token token;
};

#endif