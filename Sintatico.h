#include<iostream>
#include<cmath>
#include<cstring>
#include "Lexico.h"
#include "Tag.h"
#include "Token.h"
#include "Lexico.h"

#ifndef COMPILADOR_SINTATICO_H
#define COMPILADOR_SINTATICO_H

using namespace std;

class Sintatico{
public:
    Sintatico(Lexico* analisador);
    void run();
private:
    Lexico* kesser;
    Token* tok;
    int tok_code;
    void advance();
    void eat(int t);
    void program();
    void decl_list1();
    void decl_list2();
    void decl();
    void ident_list1();
    void ident_list2();
    void type();
    void stmt_list1();
    void stmt_list2();
    void stmt();
    void assign_stmt();
    void if_stmt1();
    void if_stmt2();
    void condition();
    void do_stmt();
    void stmt_suffix();
    void read_stmt();
    void write_stmt();
    void writable();
    void expression1();
    void expression2();
    void simple_expr1();
    void simple_expr2();
    void term1();
    void term2();
    void factor_a();
    void factor();
    void relop();
    void addop();
    void mulop();
    void constant();
    void error(string s);
    string *non_terminal;
    /*
    void integer_cont();
    void literal();
    void identifier();
    void letter();
    void digit();
    void nozero();
    void caractere();
     */
};

#endif //COMPILADOR_SINTATICO_H