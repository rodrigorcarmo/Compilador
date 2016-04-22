#include <string>
#include <iostream>
#ifndef COMPILADOR_TOKEN_H
#define COMPILADOR_TOKEN_H


class Token {
public:
    int tag;
    Token(int t);
    std::string toString();
};


#endif //COMPILADOR_TOKEN_H
