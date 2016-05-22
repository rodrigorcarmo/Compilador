#include "Lexico.h"
#include "Tag.h"
#include "Token.h";
#ifndef COMPILADOR_SINTATICO_H
#define COMPILADOR_SINTATICO_H

using namespace std;

class Sintatico{
	public:
		Sintatico(Lexico analisador);
		int tok;

	private:
		Lexico kesser;
		void advance();
		void eat();
		void program();
		void decl_list();
		void decl();
		void ident_list();
		void type();
		void stmt_list();
		void stmt();
		void assign_stmt();
		void if_stmt();
		void if_stmt_prime();
		void condition();
		void do_stmt();
		void stmt_suffix();
		void read_stmt();
		void write_stmt();
		void writable();
		void expression();
		void expression_prime();
		void simple_expr();
		void term();
		void factor_a();
		void factor();
		void relop();
		void addop();
		void mulop();
		void constant();
		void integer_cont();
		void literal();
		void identifier();
		void letter();
		void digit();
		void nozero();
		void caractere();
};

#endif //COMPILADOR_SINTATICO_H