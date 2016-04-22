#include "Lexico.h"

Lexico::Lexico(string filename) {
    ch = ' ';
    line = 1;
    file.open(filename);
    if(!file.is_open()){
        cout<<"Arquivo não existe!"<<endl;
        return;
    }
}

void Lexico::readCharacter() {
    file.get(ch);
}

bool Lexico::compareNext(char c) {
    readCharacter();
    if(ch!=c)
        return false;
    ch = ' ';
    return true;
}

void Lexico::Analisa() {
    for(;;readCharacter()){
        if(ch==' ' || ch=='\t' || ch=='\r' || ch=='\b')
            continue;
        else if(ch=='\n')
            line++;
        else
            break;
    }

    switch(ch){

    }

    if(isdigit(ch)){
        int valor = 0;
        do{
            //valor = 10*valor + atoi((char*)ch);
            readCharacter();
        }while (isdigit(ch));

    }

    if(isalpha(ch)){

    }
}

