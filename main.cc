#include "src/lexer.hh"
#include "src/token.hh"

#include <iostream>

int main () {
    Lexer lexer = Lexer(L"abc = 4");
    Token tokens[3];
    
    for (int i = 0; i < 3; i++) {
        tokens[i] = lexer.next_token();
        std::wcout << (int)tokens[i].type << ' ' << tokens[i].literal << L'\n';
    }

    return 0;
}
