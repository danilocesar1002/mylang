#include "src/lexer.hh"
#include "src/token.hh"

#include <iostream>

int main () {
    Lexer lexer = Lexer(L"abc = 4");
    Token tokens[5];
    tokens[0] = lexer.next_token();

    for (int i = 0; i < 5 - 1 && tokens[i].type != TokenType::EOFILE; i++) {
        std::wcout << (int)tokens[i].type << ' ' << tokens[i].literal << L'\n';
        tokens[i + 1] = lexer.next_token();
    }

    return 0;
}
