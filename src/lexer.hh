#ifndef INCLUDE_LEXER_HH
#define INCLUDE_LEXER_HH

#include "token.hh"
#include <unordered_map>

class Lexer
{
public:
    Lexer(std::wstring source_);
    Token next_token();

private:
    void read_character();
    void skip_whitespace();
    void skip_lines();
    wchar_t peek_character();

    bool is_number(wchar_t chr);
    bool is_letter(wchar_t chr);

    std::wstring read_number();
    std::wstring read_identifier();

    std::wstring source;
    wchar_t current_character;
    unsigned int read_position, position;
             int line, column;

    std::unordered_map<std::wstring, TokenType> KEYWORDS = {
        {L"si", TokenType::IF},
        {L"para", TokenType::FOR},
        {L"sino", TokenType::ELSE},
        {L"mientras", TokenType::WHILE}
    };
};

#endif
