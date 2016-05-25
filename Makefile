CC = g++ -std=c++11
EXEC = pg_lexer
OBJS = Sintatico.o Lexico.o Token.o Num.o Word.o Literal.o
H_FILE = Sintatico.h Lexico.h Token.h Tag.h Num.h Word.h Literal.h
MATHFLAG = -lm
FLAGS = -O3 -fopenmp
SEQFLAGS = -O3 

all: $(EXEC)
pg_lexer: main.cpp $(OBJS) $(H_FILE)
	$(CC) $(SEQFLAGS) $(MATHFLAG) -o $@ main.cpp  $(OBJS)

pg_lexer_OMP: main.cpp $(OBJS) $(H_FILE)
	$(CC) $(FLAGS) $(MATHFLAG) -o $@ main.cpp $(OBJS)


Sintatico.o: Sintatico.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Sintatico.cpp

Lexico.o: Lexico.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Lexico.cpp

Token.o: Token.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Token.cpp

Num.o: Num.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Num.cpp

Word.o: Word.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Word.cpp

Literal.o: Literal.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Literal.cpp

clean: 
	rm -f *.o $(OBJS) $(EXEC)
