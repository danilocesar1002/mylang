#include "ast.hh"

Assignment::Assignment() {
    type = ASTNodeType::Assignment;
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

For::For() {
    type = ASTNodeType::For;
}

While::While() {
    type = ASTNodeType::While;
}
