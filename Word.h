#include "Token.h"

#ifndef WORD_H
#define WORD_H

using namespace std;

class Word : public Token {
private:
    string lexeme;
<<<<<<< Updated upstream

public:
    Word(string s, int tag);
    string to_string();
    int get_Tag();
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
=======
public:
    Word(string s, int tag);
    string to_string();
    static const Word Var;
    static const Word Begin;
    static const Word End;
    static const Word Is;
    static const Word Int;
    static const Word String;
    static const Word If;
    static const Word Then;
    static const Word Else;
    static const Word Do;
    static const Word While;
    static const Word In;
    static const Word Out;
    static const Word Not;
    static const Word Semicolon;
    static const Word Comma;
    static const Word OpenParenthesis;
    static const Word CloseParenthesis;
    static const Word OpenBrace;
    static const Word CloseBrace;
    static const Word EqOp;
    static const Word GreaterOp;
    static const Word GeOp;
    static const Word LessOp;
    static const Word LeOp;
    static const Word NeOp;
    static const Word SumOp;
    static const Word MinusOp;
    static const Word OrOp;
    static const Word MultOp;
    static const Word DivOp;
    static const Word AndOp;
    static const Word AssignOp;
>>>>>>> Stashed changes
};

#endif /* WORD_H */
