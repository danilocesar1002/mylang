#include "parser.hh"
#include "ast.hh"

Parser::Parser(Lexer lexer_) : lexer(lexer_) {
    ident_level = 0;
    advance_tokens();
    advance_tokens();
};

Program Parser::parse_program() {
    Program program;

    while (current_token.type != TokenType::EOFILE) {
        Expression *expression = parse_expression();
        if (expression == nullptr) // there is an error
            break;
        else
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

void Parser::skip_tabs() {
    unsigned int tabs;
    for (tabs = 0; tabs < ident_level && current_token.type == TokenType::TAB; tabs++)
        advance_tokens();
    
    ident_level = tabs;
}

Expression* Parser::parse_expression() {
    Expression *expression = nullptr;
    
    skip_tabs();
    switch (current_token.type) {
        case TokenType::IDENT:
            if (peek_token.type == TokenType::ASSIGN)
                expression = parse_assignment();
            else if (peek_token.type == TokenType::LPAREN)
                expression = parse_call();
            break;
        case TokenType::INT:
            expression = parse_integer();
            break;
        case TokenType::IF:
            expression = parse_if_expression();
            break;
        case TokenType::FOR:
            expression = parse_for_expression();
            break;
        case TokenType::WHILE:
            expression = parse_while_expression();
            break;
        default:
            break;
    }

    if (current_token.type == TokenType::EOL)
        advance_tokens();

    return expression; 
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
    
    If *new_if = new If();

    advance_tokens();
    new_if->condition = parse_expression();
    new_if->consequence = parse_block();

    if (!expected_token(TokenType::ELSE))
        return nullptr;
    
    new_if->alternative = parse_block();
    
    return new_if;
}

Block* Parser::parse_block() {
    if (current_token.type != TokenType::TAB)
        return nullptr; // at least one expression inside the block
    
    Block *block = new Block();
    unsigned int past_ident_level = ident_level;

    // we already know that current_token.type == TokenType::TAB
    if      (peek_token.type == TokenType::TAB) {
        return nullptr; // only one tab of difference between levels
    }
    else if (peek_token.type != TokenType::TAB) {
        advance_tokens();
        // updating ident_level is necessary for parsing blocks inside this block
        ident_level = ident_level + 1;
        block->expressions.push_back(parse_expression());
    }

    while (past_ident_level + 1 == ident_level)
        block->expressions.push_back(parse_expression());
    
    return block;
}

Expression* Parser::parse_for_expression() {
    For *new_for = new For();
    
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
    While *new_while = new While();

    if (current_token.type != TokenType::WHILE)
        return nullptr;
    advance_tokens();
    new_while->condition = parse_expression();

    new_while->subrutine = parse_block();
    
    return new_while;
}

Expression* Parser::parse_call() {
    if (current_token.type != TokenType::IDENT)
        return nullptr;
    Call *call = new Call();
    call->token = current_token;
    advance_tokens();

    if (current_token.type != TokenType::LPAREN)
        return nullptr;
    call->params = parse_params();
    
    return call;
}

Block* Parser::parse_params() {
    if (current_token.type != TokenType::LPAREN)
        return nullptr;
    else
        advance_tokens();
    
    Block *params = new Block();
    while (current_token.type != TokenType::RPAREN) {
        params->expressions.push_back(parse_expression());
        
        if (current_token.type != TokenType::COMMA)
            return nullptr;
    }

    if (current_token.type != TokenType::RPAREN)
        return nullptr;
    else
        return params;
}
