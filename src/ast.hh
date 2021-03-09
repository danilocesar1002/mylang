#ifndef INCLUDE_AST_HH
#define INCLUDE_AST_HH

#include "token.hh"
#include <vector>

enum class ASTNodeType: int
{
    Expression,
    Assignment,
    Block,
    For,
    If,
    Integer,
    LetStatement,
    Program,
    Statement,
    While
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
    Assignment();

    Expression *value;
};


class Integer: public Expression
{
public:
    Integer(Token token);
    long long value;
};


class Block: public ASTNode
{
public:
    std::vector<Expression* > expressions;

    Block();
};


class If: public Expression
{
public:
    If();
    Expression* condition;
    Block* consequence;
    Block* alternative;
};


class For: public Expression
{
public:
    For();
    Expression* init_var;
    Expression* condition;
    Expression* iter_op;
    Block* subrutine;
};


class While: public Expression
{
public:
    While();
    Expression* condition;
    Block* subrutine;
};


class Program: public ASTNode
{
public:
    std::vector<Expression* > expressions;

    Program();
};

#endif
