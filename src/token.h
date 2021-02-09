#ifndef INCLUDE_TOKEN_H
#define INCLUDE_TOKEN_H

#include <string>

enum class TokenType: int
{
    ASSIGN,
    COMMA,
    COLON,
    DIVISION,
    DO,
    EOL,
    FALSE,
    FOR,
    IDENT,
    IF,
    ILLEGAL,
    MINUS,
    MULTIPLICATION,
    LPAREN,
    PLUS,
    RPAREN,
    TAB,
    TRUE,
    WHILE
};

class Token
{
public:
    Token();

    TokenType type;
    int line;
    int column;
};

#endif
