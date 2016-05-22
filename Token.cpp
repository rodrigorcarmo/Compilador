#include "Token.h"

Token::Token(int t) {
    tag = t;
}

string Token::to_string() {
    ostringstream convert;
    convert << tag;
    string tag_str = convert.str();
    return tag_str;
}


ssssss