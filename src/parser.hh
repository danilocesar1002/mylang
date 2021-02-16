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
    Token current_token;
    Token peek_token;

    void advance_tokens();
    bool expected_token(TokenType token_type);
    Expression* parse_expression();
};

#endif
