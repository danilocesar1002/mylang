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

        if (expression != NULL)
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
    
     
}
