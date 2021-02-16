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
    
    Expression *expression = program.expressions[0];
    std::wcout << L"NodeType: " << (int)expression->type << L'\n';
    Assignment *ident = static_cast<Assignment*>(expression);
    
    Expression *value = ident->value;
    std::wcout << L"ValueType: " << (int)value->type << L'\n';
    Integer *integer = static_cast<Integer*>(value);
    std::wcout << L"Value: " << integer->value << L'\n';
    
    return 0;
}
