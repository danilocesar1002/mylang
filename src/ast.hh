#ifndef INCLUDE_AST_HH
#define INCLUDE_AST_HH

#include "token.hh"

enum class ASTNodeType: int
{
    Expression
};

class ASTNode
{
public:
    virtual std::wstring literal() = 0;
};


class Expression: public ASTNode
{
public:
    Token token;
    ASTNodeType type;

    Expression(Token token);
    std::wstring literal();
};

#endif
