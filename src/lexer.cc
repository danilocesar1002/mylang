#include "lexer.hh"
#include "token.hh"

Lexer::Lexer(std::wstring source_) : source(source_) {
    current_character = NULL;

    position = read_position
             = line
             = column
             = 0;
};

Token Lexer::next_token() {
    Token token;
    switch (current_character) {
        case L'=':
            if (peek_character() == L'=') {
                token.type = TokenType::EQUALS;
                read_character();
            }
            else {
                token.type = TokenType::ASSIGN;
            }
            break;
        case L',':
            token.type = TokenType::COMMA;
            break;
        case L':':
            token.type = TokenType::COLON;
            break;
        case L'/':
            token.type = TokenType::DIVISION;
            break;
        case L'\n':
            token.type = TokenType::EOL;
            column = -1;
            line++;
            break;
        case L'>':
            if      (peek_character() == L'=') {
                token.type = TokenType::GT_OR_EQ;
                read_character();
            }
            else if (peek_character() == L'>') {
                token.type = TokenType::RSHIFT;
                read_character();
            }
            else {
                token.type = TokenType::GT;
            }
            break;
        case L'<':
            if      (peek_character() == L'=') {
                token.type = TokenType::LT_OR_EQ;
                read_character();
            }
            else if (peek_character() == L'<') {
                token.type = TokenType::LSHIFT;
                read_character();
            }
            else
                token.type = TokenType::LT;
            break;
        case L'-':
            token.type = TokenType::MINUS;
            break;
        case L'*':
            token.type = TokenType::MULTIPLICATION;
            break;
        case L'(':
            token.type = TokenType::LPAREN;
            break;
        case L'+':
            token.type = TokenType::PLUS;
            break;
        case L')':
            token.type = TokenType::RPAREN;
            break;
        case L'\t':
            token.type = TokenType::TAB;
            break;
        default:
            if (is_number(current_character)) {
                
            }
            else if (is_letter(current_character)) {

            }
            else {
                token.type = TokenType::ILLEGAL;
            }
            break; // TODO: Get keywords and identifiers
    }

    read_character();

    return token;
}

void Lexer::read_character() {
    if (read_position >= source.length())
        current_character = NULL;
    else
        current_character = source[read_position];
    
    position = read_position;
    read_position++;

    column++;
}

wchar_t Lexer::peek_character() {
    if (read_position >= source.length())
        return NULL;
    
    return source[read_position];
}

bool Lexer::is_number(wchar_t chr) {
    return L'0' <= chr && chr <= L'9';
}

bool Lexer::is_letter(wchar_t chr) {
    std::wstring permitted_chars = L"áéíóúÁÉÍÓÚñÑ";
    
    for (int i = 0; i < (int)permitted_chars.length(); i++)
        if (chr == permitted_chars[i])
            return true;

    return (L'a' <= chr && chr <= L'z') || (L'A' <= chr && chr <= L'Z');
}
