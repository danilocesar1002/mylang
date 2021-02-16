#include "parser.hh"
#include "ast.hh"


Parser::Parser(Lexer lexer_) : lexer(lexer_) {

    advance_tokens();
    advance_tokens();
};

Program Parser::parse_program() {
    Program program;

    while (current_token.type != TokenType::EOFILE) {
        Expression *expression = parse_expression();

        if (expression != nullptr)
            program.expressions.push_back(expression);
    }

    return program;
}

void Parser::advance_tokens() {
    current_token = peek_token;
    peek_token = lexer.next_token();
}

bool Parser::expected_token(TokenType token_type) {
    if (peek_token.type == token_type) {
        advance_tokens();
        return true;
    }

    return false;
}

Expression* Parser::parse_expression() {
    if (current_token.type == TokenType::IDENT && peek_token.type == TokenType::ASSIGN)
        return parse_assignment();
    if (current_token.type == TokenType::INT)
        return parse_integer();
    
    return nullptr; 
}

Expression* Parser::parse_assignment() {
    Identifier *ident = new Identifier(current_token, NULL);
    
    advance_tokens();
    advance_tokens();
    
    ident->value = parse_expression();
    return ident;
}


Expression* Parser::parse_integer() {
    Integer *integer = new Integer(current_token);
    advance_tokens();

    return integer;
}