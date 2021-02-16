#include "ast.hh"

Identifier::Identifier(Token token, std::wstring value) {
    type = ASTNodeType::Identifier;
    this->token = token;
    this->value = value;
}


Program::Program() {
    expressions = std::vector<Expression* >();
    type = ASTNodeType::Program;
}
