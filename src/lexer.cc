#include "lexer.h"
#include "token.h"

Lexer::Lexer(std::string source_) : source(source_) {
    current_character = NULL;
    position = read_position = 0;
};

Token Lexer::next_token() {
    Token token;
    switch (current_character) {
        case '=':
            token.type = TokenType::ASSIGN;
            break;
        case ',':
            token.type = TokenType::COMMA;
            break;
        case ':':
            token.type = TokenType::COLON;
            break;
        case '/':
            token.type = TokenType::DIVISION;
            break;
        case '\n':
            token.type = TokenType::EOL;
            break;
        case '-':
            token.type = TokenType::MINUS;
            break;
        case '*':
            token.type = TokenType::MULTIPLICATION;
            break;
        case '(':
            token.type = TokenType::LPAREN;
            break;
        case '+':
            token.type = TokenType::PLUS;
            break;
        case ')':
            token.type = TokenType::RPAREN;
            break;
        case '\t':
            token.type = TokenType::TAB;
            break;
        default:
            break; // TODO: Get keywords and identifiers
    }
}

void Lexer::read_character() {
    if (read_position >= source.size())
        current_character = NULL;
    else
        current_character = source[read_position];
    
    position = read_position;
    read_position++;
}

