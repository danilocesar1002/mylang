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
    unsigned int ident_level;

    void advance_tokens();
    void skip_tabs();
    bool expected_token(TokenType token_type);
    Expression* parse_expression();
    Expression* parse_assignment();
    Expression* parse_integer();
    Expression* parse_if_expression();
    Expression* parse_for_expression();
    Expression* parse_while_expression();
    Block* parse_block();
};

#endif
