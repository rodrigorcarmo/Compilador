#include <iostream>
#include "Lexico.h"

using namespace std;

int main() {
    string path;
    cout<<"Digite o caminho do arquivo"<<endl;
    cin>>path;
    Lexico* l = new Lexico(path);
    l->Analisa();
    return 0;
}