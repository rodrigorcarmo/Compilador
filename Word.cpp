#include "Word.h"

// Inicialization of the constant static objects of the class
<<<<<<< Updated upstream
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
=======
const Word Word::Var("var", VAR);
const Word Word::Begin("begin", BEGIN);
const Word Word::End("end", END);
const Word Word::Is("is", IS);
const Word Word::Int("int", INT);
const Word Word::String("string", STRING);
const Word Word::If("if", IF);
const Word Word::Then("then", THEN);
const Word Word::Else("else", ELSE);
const Word Word::Do("do", DO);
const Word Word::While("while", WHILE);
const Word Word::In("in", IN);
const Word Word::Out("out", OUT);
const Word Word::Not("not", NOT);
const Word Word::Semicolon(";", SEMICOLON);
const Word Word::Comma(",", COMMA);
const Word Word::OpenParenthesis("(", OPEN_PARENTHESIS);
const Word Word::CloseParenthesis(")", CLOSE_PARENTHESIS);
const Word Word::OpenBrace("{", OPEN_BRACE);
const Word Word::CloseBrace("}", CLOSE_BRACE);
const Word Word::EqOp("=", EQ_OP);
const Word Word::GreaterOp(">", GREATER_OP);
const Word Word::GeOp(">=", GE_OP);
const Word Word::LessOp("<", LESS_OP);
const Word Word::LeOp("<=", LE_OP);
const Word Word::NeOp("<>", NE_OP);
const Word Word::SumOp("+", SUM_OP);
const Word Word::MinusOp("-", MINUS_OP);
const Word Word::OrOp("or", OR_OP);
const Word Word::MultOp("*", MULT_OP);
const Word Word::DivOp("/", DIV_OP);
const Word Word::AndOp("and", AND_OP);
const Word Word::AssignOp(":=", ASSIGN_OP);
>>>>>>> Stashed changes

Word::Word(string s, int tag) : Token(tag) {
    lexeme = s;
}

string Word::to_string() {
    return lexeme;
<<<<<<< Updated upstream
}

int Word::get_Tag() {
    return tag;
=======
>>>>>>> Stashed changes
}