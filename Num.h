#include "Token.h"


#ifndef NUM_H
#define NUM_H


using namespace std;

class Num: public Token {
private:
    int value;
public:
    Num(int value);
    string to_string();
};

#endif /* NUM_H */
