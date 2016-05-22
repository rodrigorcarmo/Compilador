#include "Literal.h"

Literal::Literal(string s) : Token(LITERAL) {
    this->lexeme = s;
}

string Literal::to_string() {
    return this->lexeme;
}