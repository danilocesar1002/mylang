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
    if (current_token.type == TokenType::IF)
        return parse_if_expression();
    if (current_token.type == TokenType::FOR)
        return parse_for_expression();
    if (current_token.type == TokenType::WHILE)
        return parse_while_expression();
    return nullptr; 
}

Expression* Parser::parse_assignment() {
    if (current_token.type != TokenType::IDENT)
        return nullptr;
    
    Assignment *ident = new Assignment();
    ident->token = current_token;
    
    if (expected_token(TokenType::ASSIGN))
        advance_tokens();
    else
        return nullptr;
    
    ident->value = parse_expression();
    return ident;
}

Expression* Parser::parse_integer() {
    if (current_token.type != TokenType::INT)
        return nullptr;
    
    Integer *integer = new Integer(current_token);
    advance_tokens();

    return integer;
}

Expression* Parser::parse_if_expression() {
    if (current_token.type != TokenType::IF)
        return nullptr;
    
    If* new_if = new If();

    advance_tokens();
    new_if->condition = parse_expression();
    new_if->consequence = parse_block();

    if (!expected_token(TokenType::ELSE))
        return nullptr;
    
    new_if->alternative = parse_block();
    
    return new_if;
}

Block* Parser::parse_block() {
    // TODO
    return nullptr;
}

Expression* Parser::parse_for_expression() {
    For* new_for = new For();
    
    if (current_token.type != TokenType::FOR)
        return nullptr;
    advance_tokens();
    new_for->init_var = parse_expression();
    
    if (current_token.type != TokenType::COLON)
        return nullptr;
    advance_tokens();
    new_for->condition = parse_expression();

    if (current_token.type != TokenType::COLON)
        return nullptr;
    advance_tokens();
    new_for->iter_op = parse_expression();

    new_for->subrutine = parse_block();

    return new_for;
}

Expression* Parser::parse_while_expression() {
    While* new_while = new While();

    if (current_token.type != TokenType::WHILE)
        return nullptr;
    advance_tokens();
    new_while->condition = parse_expression();

    new_while->subrutine = parse_block();
    
    return new_while;
}
