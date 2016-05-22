#include "Sintatico.h"

Sintatico::Sintatico(Lexico analisador){
	this->kesser = analisador;
	this->tok = this->kesser.next_token();
}

void Sintatico::advance(){
	this->tok = this->kesser.next_token();
}

void Sintatico::eat(int t){
	if(this->tok==t){
		advance();
	}
	else{
		error();
	}
}

void Sintatico::program(){
	eat('[');
	decl_list();
	eat(']');
	eat("begin");
	stmt_list();
	eat("end");
}

void Sintatico::decl_list(){
	decl();
	eat(';');
	eat('{');
	decl();
	eat(';');
	eat('}');
}

void Sintatico::ident_list(){
	identifier();
	eat('{');
	eat(',');
	identifier();
	eat('}');
}