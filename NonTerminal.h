#include <string>
#include <iostream>
#include <sstream>
#include "Tag.h"    // a header with symbolic definitions for the possible tags

#ifndef NONTERMINAL_TOKEN_H
#define NONTERMINAL_TOKEN_H

using namespace std;

/*
 Token class framework
 */
class NonTerminal {
public:
    string name;
    int classe;
    int type;
    NonTerminal(string name);
};


#endif //NONTERMINAL_TOKEN_H
