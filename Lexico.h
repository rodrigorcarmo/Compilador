#include <string>
#include <iostream>
#include <fstream>
#ifndef COMPILADOR_LEXICO_H
#define COMPILADOR_LEXICO_H

using namespace std;

class Lexico {
public:
    char ch;
    int line;
    Lexico(string filename);
    void Analisa();

private:
    void readCharacter();
    bool compareNext(char c);
    void insertReserved();
    ifstream file;
};


#endif //COMPILADOR_LEXICO_H
