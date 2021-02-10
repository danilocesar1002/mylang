#ifndef INCLUDE_TOKEN_HH
#define INCLUDE_TOKEN_HH

#include <string>

enum class TokenType: int
{
    ASSIGN,
    COMMA,
    COLON,
    DIVISION,
    DO,
    EOL,
    EQUALS,
    FALSE,
    FOR,
    GT,
    GT_OR_EQ,
    IDENT,
    IF,
    ILLEGAL,
    INT,
    LT,
    LT_OR_EQ,
    MINUS,
    MULTIPLICATION,
    LPAREN,
    LSHIFT,
    PLUS,
    RPAREN,
    RSHIFT,
    TAB,
    TRUE,
    WHILE
};

class Token
{
public:
    Token();

    TokenType type;
    std::wstring literal;
    int line, column;
};

#endif
