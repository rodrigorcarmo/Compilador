#include <iostream>
#include "Lexico.h"
#include "Token.h"
#include "Num.h"
#include "Word.h"
#include <cmath>
#include <cstdio>

using namespace std;

int main(int argc, char** argv) {
    string path;
    if (argc > 1) {
        path = argv[1];
    }
    if (path.length() < 1) {
        cout<<"LEXICAL ANALISER 1.0 -> Marcelo e Rodrigo"<<endl;
        cout<<"Please type the full path of the file to be compiled:"<<endl;
        cin>>path;
    }
    Lexico* lex = new Lexico(path);
    Token* tok;
    Word* w;
    Num* num;
    Literal* lit;
    cout << "\nSequence of tokens read:\n\n";
    while(true) {
        tok = lex->next_token();
    	if(tok->to_string()=="-1")
    		break;
        // print Tag number
        printf("%3d  ",atoi(tok->to_string().c_str()));
        
        // print lexeme
        if (atoi(tok->to_string().c_str()) > 3 || atoi(tok->to_string().c_str()) == 1) {
            w = static_cast<Word*>(tok);
            cout<< w->to_string();
        }
        else if (atoi(tok->to_string().c_str()) == 2) {
            num = static_cast<Num*>(tok);
            cout<< num->to_string();
        }
        else if (atoi(tok->to_string().c_str()) == 3) {
            lit = static_cast<Literal*>(tok);
            cout << lit->to_string();
        }
        cout << endl;

    }
    lex->print();
    string pause;
    cout << "Press any key to continue...";
    cin>>pause;
    return 0;
}