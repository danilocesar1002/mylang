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

        if (expression != nullptr)
            program.expressions.push_back(expression);
    }

    return program;
}

void Parser::advance_tokens() {
    current_token = peek_token;
    peek_token = lexer.next_token();
}

void Parser::skip_lines() {
    while (current_token.type == TokenType::EOL)
        advance_tokens();
}

bool Parser::expected_token(TokenType token_type) {
    if (peek_token.type == token_type) {
        advance_tokens();
        return true;
    }

    return false;
}

void Parser::skip_tabs() {
    /*
     * This should be the only method that manipulates ident_level.
     */

    unsigned int tabs;
    for (tabs = 0; current_token.type == TokenType::TAB; tabs++)
        advance_tokens();
    
    ident_level = tabs;
}

bool Parser::verify_ident_level() {
    /*
     * This function assumes that nobody else touched the tokens since the last
     * expression was parsed.
     */

    unsigned int cur_level = ident_level;
    skip_tabs();
    return cur_level == ident_level;
}

Expression* Parser::parse_expression() {
    Expression *expression = nullptr;

    verify_ident_level();

    switch (current_token.type) {
        case TokenType::IDENT:
            if (peek_token.type == TokenType::ASSIGN)
                expression = parse_assignment();
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

    if (current_token.type != TokenType::EOL && current_token.type != TokenType::EOFILE)
        return nullptr; // EOL after expression rule

    if (expression != nullptr && current_token.type == TokenType::EOL)
        skip_lines(); // skip any number of lines after an expression

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
    Block *block = new Block();
    unsigned int past_ident_level = ident_level;

    do
        block->expressions.push_back(parse_expression());
    while (past_ident_level < ident_level);
    
    
    return nullptr;
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
