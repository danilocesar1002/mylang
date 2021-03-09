#include "src/ast.hh"
#include "src/lexer.hh"
#include "src/parser.hh"
#include "src/token.hh"


#include <iostream>

int main () {
    Lexer lexer = Lexer(L"para a = 1 : a = 5 : a = 2 \n \t b = 1");
    std::wcout << L"lexed\n";

    Parser parser = Parser(lexer);
    std::wcout << L"initialized parser\n";

    Program program = parser.parse_program();
    std::wcout << L"parsed\n";

    std::wcout << (int)program.expressions[0]->type << L'\n';

    return 0;
}
