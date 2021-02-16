#include "ast.hh"

Identifier::Identifier(Token token, Expression *value) {
    type = ASTNodeType::Identifier;
    this->token = token;
    this->value = value;
}


Program::Program() {
    expressions = std::vector<Expression* >();
    type = ASTNodeType::Program;
}


Integer::Integer(Token token) {
    value = std::stoi(token.literal);
}