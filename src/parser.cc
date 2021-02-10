#include "parser.hh"

Expression::Expression(Token token) {
    this->token = token;
    type = ASTNodeType::Expression;
}