<<<<<<< Updated upstream
CC = g++ -std=c++11
EXEC = pg_lexer
OBJS = Lexico.o Token.o Num.o Word.o Literal.o
H_FILE = Lexico.h Token.h Tag.h Num.h Word.h Literal.h
=======
CC = g++
EXEC = pg_lexer_SEQ
OBJS = Lexico.o Token.o Num.o Word.o
H_FILE = Lexico.h Token.h Tag.h Num.h Word.h
>>>>>>> Stashed changes
MATHFLAG = -lm
FLAGS = -O3 -fopenmp
SEQFLAGS = -O3 

all: $(EXEC)
<<<<<<< Updated upstream
pg_lexer: main.cpp $(OBJS) $(H_FILE)
=======
pg_lexer_SEQ: main.cpp $(OBJS) $(H_FILE)
>>>>>>> Stashed changes
	$(CC) $(SEQFLAGS) $(MATHFLAG) -o $@ main.cpp  $(OBJS)

pg_lexer_OMP: main.cpp $(OBJS) $(H_FILE)
	$(CC) $(FLAGS) $(MATHFLAG) -o $@ main.cpp $(OBJS)


Lexico.o: Lexico.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Lexico.cpp

Token.o: Token.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Token.cpp

Num.o: Num.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Num.cpp

Word.o: Word.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Word.cpp

<<<<<<< Updated upstream
Literal.o: Literal.cpp
	$(CC) $(SEQFLAGS) -o $@ -c Literal.cpp

=======
>>>>>>> Stashed changes
clean: 
	rm -f *.o $(OBJS) $(EXEC)
