#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
<<<<<<< Updated upstream
#include <unordered_map>
#include "Word.h"
#include "Token.h"
#include "Num.h"
#include "Tag.h"
#include "Literal.h"
=======
>>>>>>> Stashed changes

#ifndef COMPILADOR_LEXICO_H
#define COMPILADOR_LEXICO_H


using namespace std;

class Lexico {
public:
<<<<<<< Updated upstream
    unordered_map<string,Word*> hashtable;
    Lexico(string filename);
    int next_char();
    bool compareNext(char c);
    void insertReserved(Word *w);
    bool is_delimiter(char c);
    Token* next_token();
    void print();
=======
    Lexico(string filename);
    char next_valid_char();
    bool compareNext(char c);
    void insertReserved();
    bool is_delimiter(char c);
    void Analisa();
>>>>>>> Stashed changes

private:
    char ch;
    int line;
<<<<<<< Updated upstream
    int column;
    ifstream file;
    const string delimiters = " \t\r\b\n";
    void shift_to_after(string s);
    Token* rec_punc_relop();
    Token* rec_literal();
    Token* rec_number();
    Token* rec_id_reserv();
    void display_error(int n, string s);
    Token* insert_word(string s);
=======
    ifstream file;
    const string delimiters = " \t\r\b";
>>>>>>> Stashed changes
};


#endif //COMPILADOR_LEXICO_H
