#include "Num.h"

Num::Num(int value) : Token(NUM_CONST){
    this->value = value;
}

string Num::to_string() {
    ostringstream convert;
    convert << value;
    string value_str = convert.str();
    return value_str;
}