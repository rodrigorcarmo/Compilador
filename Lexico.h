#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <unordered_map>
#include "Word.h"
#include "Token.h"
#include "Num.h"
#include "Tag.h"
#include "Literal.h"

#ifndef COMPILADOR_LEXICO_H
#define COMPILADOR_LEXICO_H


using namespace std;

class Lexico {
public:
    unordered_map<string,Word*> hashtable;
    Lexico(string filename);
    int next_char();
    bool compareNext(char c);
    void insertReserved(Word *w);
    bool is_delimiter(char c);
    Token* next_token();
    void print();
    int get_line();
    int get_column();

private:
    char ch;
    int line;
    int line_mem1;
    int line_mem2;
    int column;
    int column_mem1;
    int column_mem2;
    ifstream file;
    const string delimiters = " \t\r\b\n";
    void shift_to_after(string s);
    Token* rec_punc_relop();
    Token* rec_literal();
    Token* rec_number();
    Token* rec_id_reserv();
    void display_error(int n, string s);
    Token* insert_word(string s);
};


#endif //COMPILADOR_LEXICO_H
