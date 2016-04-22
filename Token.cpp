#include "Token.h"

Token::Token(int t) {
    tag = t;
}

std::string Token::toString() {
    return std::to_string(tag);
}