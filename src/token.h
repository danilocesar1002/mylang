#include <string>

enum class TokenType: int
{
    ASSIGN,
    COMMA,
    DIVISION,
    DO,
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
    Token(TokenType type_, std::string literal_);

    std::string literal;
    TokenType type;
};
