#ifndef COMPILADOR_TAG_H
#define COMPILADOR_TAG_H

/*
 Symbolic constants for the token tags
 */
#define ID 1
#define NUM_CONST 2
#define LITERAL 3

// Reserved words
#define VAR 4
#define BEGIN 5
#define END 6
#define IS 7
#define INT 8
#define STRING 9
#define IF 10
#define THEN 11
#define ELSE 12
#define DO 13
#define WHILE 14
#define IN 15
#define OUT 16
#define NOT 17

// Punctuation
#define SEMICOLON 18
#define COMMA 19
#define OPEN_PARENTHESIS 20
#define CLOSE_PARENTHESIS 21

// Relational Operations
#define EQ_OP 24
#define GREATER_OP 25
#define GE_OP 26
#define LESS_OP 27
#define LE_OP 28
#define NE_OP 29

// Add, multiply and attribute Operations
#define SUM_OP 30
#define MINUS_OP 31
#define OR_OP 32
#define MULT_OP 33
#define DIV_OP 34
#define AND_OP 35
#define ASSIGN_OP 36



#endif //COMPILADOR_TAG_H
