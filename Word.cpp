#include "Word.h"

// Inicialization of the constant static objects of the class
Word* Word::Var = new Word("var", VAR);
Word* Word::Begin = new Word("begin", BEGIN);
Word* Word::End = new Word("end", END);
Word* Word::Is = new Word("is", IS);
Word* Word::Int = new Word("int", INT);
Word* Word::String = new Word("string", STRING);
Word* Word::If = new Word("if", IF);
Word* Word::Then = new Word("then", THEN);
Word* Word::Else = new Word("else", ELSE);
Word* Word::Do = new Word("do", DO);
Word* Word::While = new Word("while", WHILE);
Word* Word::In = new Word("in", IN);
Word* Word::Out = new Word("out", OUT);
Word* Word::Not = new Word("not", NOT);
Word* Word::Semicolon = new Word(";", SEMICOLON);
Word* Word::Comma = new Word(",", COMMA);
Word* Word::OpenParenthesis = new Word("(", OPEN_PARENTHESIS);
Word* Word::CloseParenthesis = new Word(")", CLOSE_PARENTHESIS);
Word* Word::EqOp = new Word("=", EQ_OP);
Word* Word::GreaterOp = new Word(">", GREATER_OP);
Word* Word::GeOp = new Word(">=", GE_OP);
Word* Word::LessOp = new Word("<", LESS_OP);
Word* Word::LeOp = new Word("<=", LE_OP);
Word* Word::NeOp = new Word("<>", NE_OP);
Word* Word::SumOp = new Word("+", SUM_OP);
Word* Word::MinusOp = new Word("-", MINUS_OP);
Word* Word::OrOp = new Word("or", OR_OP);
Word* Word::MultOp = new Word("*", MULT_OP);
Word* Word::DivOp = new Word("/", DIV_OP);
Word* Word::AndOp = new Word("and", AND_OP);
Word* Word::AssignOp = new Word(":=", ASSIGN_OP);

Word::Word(string s, int tag) : Token(tag) {
    lexeme = s;
}

string Word::to_string() {
    return lexeme;
}

int Word::get_Tag() {
    return tag;
}