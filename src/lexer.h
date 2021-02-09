#ifndef INCLUDE_LEXER_H
#define INCLUDE_LEXER_H

#include "token.h"

class Lexer
{
public:
    Lexer(std::string source_);
    Token next_token();

private:
    void read_character();


    std::string source;
    char current_character;
    int read_position;
    int position;
};

#endif
