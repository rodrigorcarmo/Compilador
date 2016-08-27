#include "Token.h"

#ifndef WORD_H
#define WORD_H

using namespace std;

class Word : public Token {
private:
    string lexeme;

public:
    Word(string s, int tag);
    string to_string();
    int get_Tag();
    int tipo;
    static Word* Var;
    static Word* Begin;
    static Word* End;
    static Word* Is;
    static Word* Int;
    static Word* String;
    static Word* If;
    static Word* Then;
    static Word* Else;
    static Word* Do;
    static Word* While;
    static Word* In;
    static Word* Out;
    static Word* Not;
    static Word* Semicolon;
    static Word* Comma;
    static Word* OpenParenthesis;
    static Word* CloseParenthesis;
    static Word* EqOp;
    static Word* GreaterOp;
    static Word* GeOp;
    static Word* LessOp;
    static Word* LeOp;
    static Word* NeOp;
    static Word* SumOp;
    static Word* MinusOp;
    static Word* OrOp;
    static Word* MultOp;
    static Word* DivOp;
    static Word* AndOp;
    static Word* AssignOp;
    
};

#endif /* WORD_H */
