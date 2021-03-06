#include "lexer.hh"
#include "token.hh"


Lexer::Lexer(std::wstring source_) : source(source_) {
    position = read_position
             = line
             = 0;
    
    column = -1; //read_character() will put it in 0
    read_character();
};

Token Lexer::next_token() {
    skip_whitespace();

    Token token;
    token.line = line;
    token.column = column;

    switch (current_character) {
        case L'=':
            if (peek_character() == L'=') {
                token.type = TokenType::EQUALS;
                token.literal = L"==";
                read_character();
            }
            else {
                token.literal = L"=";
                token.type = TokenType::ASSIGN;
            }
            break;
        case L',':
            token.literal = L",";
            token.type = TokenType::COMMA;
            break;
        case L':':
            token.literal = L":";
            token.type = TokenType::COLON;
            break;
        case L'/':
            token.literal = L"/";
            token.type = TokenType::DIVISION;
            break;
        case L'\n':
            token.literal = L"\n";
            token.type = TokenType::EOL;
            skip_lines();
            break;
        case L'>':
            if      (peek_character() == L'=') {
                token.literal = L">=";
                token.type = TokenType::GT_OR_EQ;
                read_character();
            }
            else if (peek_character() == L'>') {
                token.literal = L">>";
                token.type = TokenType::RSHIFT;
                read_character();
            }
            else {
                token.type = TokenType::GT;
            }
            break;
        case L'<':
            if      (peek_character() == L'=') {
                token.literal = L"<=";
                token.type = TokenType::LT_OR_EQ;
                read_character();
            }
            else if (peek_character() == L'<') {
                token.literal = L"<<";
                token.type = TokenType::LSHIFT;
                read_character();
            }
            else
                token.type = TokenType::LT;
            break;
        case L'-':
            token.literal = L"-";
            token.type = TokenType::MINUS;
            break;
        case L'*':
            token.literal = L"*";
            token.type = TokenType::MULTIPLICATION;
            break;
        case L'(':
            token.literal = L"(";
            token.type = TokenType::LPAREN;
            break;
        case L'+':
            token.literal = L"+";
            token.type = TokenType::PLUS;
            break;
        case L')':
            token.literal = L")";
            token.type = TokenType::RPAREN;
            break;
        case L'\t':
            token.literal = L"\t";
            token.type = TokenType::TAB;
            break;
        case WEOF:
            token.literal = WEOF;
            token.type = TokenType::EOFILE;
            break;
        default:
            if      (is_number(current_character)) {
                token.type = TokenType::INT;
                token.literal = read_number();
            }
            else if (is_letter(current_character)) {
                token.literal = read_identifier();

                if (KEYWORDS.find(token.literal) != KEYWORDS.end())
                    token.type = KEYWORDS[token.literal];
                else
                    token.type = TokenType::IDENT;
            }
            else {
                token.type = TokenType::ILLEGAL;
            }
            break;
    }

    read_character();

    return token;
}

void Lexer::read_character() {
    if (read_position >= source.length())
        current_character = WEOF;
    else
        current_character = source[read_position];
    
    position = read_position;
    read_position++;

    column++;

    if (current_character == L'\n') {
        column = 0;
        line++;
    }
}

void Lexer::skip_whitespace() {
    while (current_character == L' ')
        read_character();
}

void Lexer::skip_lines() {
    while (peek_character() == L'\n') {
        read_character();
        line++;
    }
}

wchar_t Lexer::peek_character() {
    if (read_position >= source.length())
        return WEOF;
    
    return source[read_position];
}

bool Lexer::is_number(wchar_t chr) {
    return L'0' <= chr && chr <= L'9';
}

bool Lexer::is_letter(wchar_t chr) {
    std::wstring permitted_chars = L"_áéíóúÁÉÍÓÚñÑ";
    
    for (int i = 0; i < (int)permitted_chars.length(); i++)
        if (chr == permitted_chars[i])
            return true;

    return (L'a' <= chr && chr <= L'z') || (L'A' <= chr && chr <= L'Z');
}

std::wstring Lexer::read_number() {
    std::wstring num = L"";

    while (is_number(current_character)) {
        num += current_character;
        read_character();
    }
    
    return num;
}

std::wstring Lexer::read_identifier() {
    std::wstring ident = L"";

    do {
        ident += current_character;
        read_character();
    } while (is_letter(current_character) || is_number(current_character));
    
    return ident;
}
