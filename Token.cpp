#include "Token.h"

Token::Token(int t) {
    tag = t;
}

<<<<<<< Updated upstream
string Token::to_string() {
=======
std::string Token::toString() {
>>>>>>> Stashed changes
    ostringstream convert;
    convert << tag;
    string tag_str = convert.str();
    return tag_str;
}


ssssss