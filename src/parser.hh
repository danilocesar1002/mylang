#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H

#include "lexer.hh"
#include "ast.hh"

class Parser
{
public:
    Parser(Lexer lexer_);
    Program parse_program();
private:
    Lexer lexer;
};

#endif
