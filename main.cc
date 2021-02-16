#include "src/ast.hh"
#include "src/lexer.hh"
#include "src/parser.hh"
#include "src/token.hh"


#include <iostream>

int main () {
    Lexer lexer = Lexer(L"abc = 4");
    Parser parser = Parser(lexer);

    Program program = parser.parse_program();

    std::wcout << program.expressions.size() << L'\n';

    return 0;
}
