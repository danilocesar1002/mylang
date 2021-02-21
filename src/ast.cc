#include "ast.hh"

Assignment::Assignment(Token token, Expression *value) {
    type = ASTNodeType::Assignment;
    this->token = token;
    this->value = value;
}


Program::Program() {
    expressions = std::vector<Expression* >();
    type = ASTNodeType::Program;
}


Integer::Integer(Token token) {
    type = ASTNodeType::Integer;
    value = std::stoi(token.literal);
}


Block::Block() {
    type = ASTNodeType::Block;
}


If::If() {
    type = ASTNodeType::If;
}