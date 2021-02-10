#ifndef INCLUDE_LEXER_HH
#define INCLUDE_LEXER_HH

#include "token.hh"

class Lexer
{
public:
    Lexer(std::wstring source_);
    Token next_token();

private:
    void read_character();
    void skip_whitespace();
    wchar_t peek_character();

    bool is_number(wchar_t chr);
    bool is_letter(wchar_t chr);

    std::wstring read_number();
    std::wstring read_identifier();

    std::wstring source;
    wchar_t current_character;
    unsigned int read_position, position;
             int line, column;
};

#endif
