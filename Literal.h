#ifndef Literal_h
#define Literal_h

#include "Token.h"
#include <stdio.h>
using namespace std;

class Literal : public Token {
private:
    string lexeme;
public:
    Literal(string s);
    string to_string();
};

#endif /* Literal_h */