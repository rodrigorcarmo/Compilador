#include <string>
#include <iostream>
#include <sstream>
#include "Tag.h"    // a header with symbolic definitions for the possible tags

#ifndef COMPILADOR_TOKEN_H
#define COMPILADOR_TOKEN_H

using namespace std;

/*
 Token class framework
 */
class Token {
public:
    int tag;
    Token(int t);
<<<<<<< Updated upstream
    //virtual ~Token();
     string to_string();
=======
    string toString();
>>>>>>> Stashed changes
};


#endif //COMPILADOR_TOKEN_H
