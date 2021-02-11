#include "ast.hh"

Identifier::Identifier(Token token, std::wstring value) {
    type = ASTNodeType::Identifier;
    this->token = token;
    this->value = value;
}


LetStatement::LetStatement(Token token, Identifier *name, Expression* value) {
    type = ASTNodeType::LetStatement;
    this->token = token;
    this->name = name;
    this->value = value;
}


Program::Program() {
    expressions = std::vector<Expression* >();
    type = ASTNodeType::Program;
}
