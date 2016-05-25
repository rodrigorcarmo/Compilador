#include "Sintatico.h"

Sintatico::Sintatico(Lexico* analisador){
	this->kesser = analisador;
    this->advance();
}

void Sintatico::run() {
    this->program();
}

void Sintatico::advance(){
	this->tok = this->kesser->next_token();
    this->tok_code = atoi(this->tok->to_string().c_str());
}

void Sintatico::eat(int t){
	if(this->tok_code == t){
		this->advance();
	}
	else{
		this->error();
	}
}



void Sintatico::program() {
    switch(this->tok_code) {
        case VAR:
            this->eat(VAR);
            this->decl_list1();
            this->eat(BEGIN);
            this->stmt_list1();
            this->eat(END);
            break;
        case BEGIN:
            this->eat(BEGIN);
            this->stmt_list1();
            this->eat(END);
            break;
        default:
            this->error();
    }
}

void Sintatico::decl_list1() {
    switch(this->tok_code) {
        case ID:
            this->decl();
            this->eat(SEMICOLON);
            this->decl_list2();
        default:
            this->error();
    }
}

void Sintatico::decl_list2() {
    switch(this->tok_code) {
        case BEGIN:
            break;
        case ID:
            this->decl_list1();
            break;
        default:
            this->error();
    }
}

void Sintatico::decl() {
    switch(this->tok_code) {
        case ID:
            this->ident_list1();
            this->eat(IS);
            this->type();
            break;
        default:
            this->error();
    }
}

void Sintatico::ident_list1() {
    switch(this->tok_code) {
        case ID:
            this->eat(ID);
            this->ident_list2();
            break;
        default:
            this->error();
    }
}

void Sintatico::ident_list2() {
    switch(this->tok_code) {
        case IS:
            break;
        case COMMA:
            this->eat(COMMA);
            this->ident_list1();
            break;
        default:
            this->error();
    }
}

void Sintatico::type() {
    switch(this->tok_code) {
        case INT:
            this->eat(INT);
            break;
        case STRING:
            this->eat(STRING);
            break;
        default:
            this->error();
    }
}

void Sintatico::stmt_list1() {
    switch(this->tok_code) {
        case ID:
        case IF:
        case DO:
        case IN:
        case OUT:
            this->stmt();
            this->eat(SEMICOLON);
            this->stmt_list2();
            break;
        default:
            this->error();
    }
}

void Sintatico::stmt_list2() {
    switch(this->tok_code) {
        case END:
        case ELSE:
        case WHILE:
            break;
        case ID:
        case IF:
        case DO:
        case IN:
        case OUT:
            this->stmt_list1();
            break;
        default:
            this->error();
    }
}

void Sintatico::stmt() {
    switch(this->tok_code) {
        case ID:
            this->assign_stmt();
            break;
        case IF:
            this->if_stmt1();
            break;
        case DO:
            this->do_stmt();
            break;
        case IN:
            this->read_stmt();
            break;
        case OUT:
            this->write_stmt();
            break;
        default:
            this->error();
    }
}

void Sintatico::assign_stmt() {
    switch(this->tok_code) {
        case ID:
            this->eat(ID);
            this->eat(ASSIGN_OP);
            this->simple_expr1();
            break;
        default:
            this->error();
    }
}

void Sintatico::if_stmt1() {
    switch(this->tok_code) {
        case IF:
            this->eat(IF);
            this->condition();
            this->eat(THEN);
            this->stmt_list1();
            this->if_stmt2();
            break;
        default:
            this->error();
    }
}

void Sintatico::if_stmt2() {
    switch(this->tok_code) {
        case END:
            this->eat(END);
            break;
        case ELSE:
            this->eat(ELSE);
            this->stmt_list1();
            this->eat(END);
            break;
        default:
            this->error();
    }
}

void Sintatico::condition() {
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            this->expression1();
            break;
        default:
            this->error();
    }
}

void Sintatico::do_stmt() {
    switch(this->tok_code) {
        case DO:
            this->eat(DO);
            this->stmt_list1();
            this->stmt_suffix();
            break;
        default:
            this->error();
    }
}

void Sintatico::stmt_suffix() {
    switch(this->tok_code) {
        case WHILE:
            this->eat(WHILE);
            this->condition();
            break;
        default:
            this->error();
    }
}

void Sintatico::read_stmt() {
    switch(this->tok_code) {
        case IN:
            this->eat(IN);
            this->eat(OPEN_PARENTHESIS);
            this->eat(ID);
            this->eat(CLOSE_PARENTHESIS);
            break;
        default:
            this->error();
    }
}

void Sintatico::write_stmt() {
    switch(this->tok_code) {
        case OUT:
            this->eat(OUT);
            this->eat(OPEN_PARENTHESIS);
            this->writable();
            this->eat(CLOSE_PARENTHESIS);
            break;
        default:
            this->error();
    }
}

void Sintatico::writable() {
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            this->simple_expr1();
            break;
        default:
            this->error();
    }
}

void Sintatico::expression1() {
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case CLOSE_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            this->simple_expr1();
            this->expression2();
            break;
        default:
            this->error();
    }
}

void Sintatico::expression2() {
    switch(this->tok_code) {
        case CLOSE_PARENTHESIS:
        case SEMICOLON:
        case THEN:
            break;
        case EQ_OP:
        case GREATER_OP:
        case GE_OP:
        case LESS_OP:
        case LE_OP:
        case NE_OP:
            this->relop();
            this->simple_expr1();
            break;
        default:
            this->error();
    }
}

void Sintatico::simple_expr1() {
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            this->term1();
            this->simple_expr2();
            break;
        default:
            this->error();
    }
}

void Sintatico::simple_expr2() {
    switch(this->tok_code) {
        case CLOSE_PARENTHESIS:
        case SEMICOLON:
        case THEN:
        case EQ_OP:
        case GREATER_OP:
        case GE_OP:
        case LESS_OP:
        case LE_OP:
        case NE_OP:
            break;
        case SUM_OP:
        case MINUS_OP:
        case OR_OP:
            this->addop();
            this->simple_expr1();
            break;
        default:
            this->error();
    }
}

void Sintatico::term1() {
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            this->factor_a();
            this->term2();
            break;
        default:
            this->error();
    }
}

void Sintatico::term2() {
    switch(this->tok_code) {
        case CLOSE_PARENTHESIS:
        case SEMICOLON:
        case THEN:
        case EQ_OP:
        case GREATER_OP:
        case GE_OP:
        case LESS_OP:
        case LE_OP:
        case NE_OP:
        case SUM_OP:
        case MINUS_OP:
        case OR_OP:
            break;
        case MULT_OP:
        case DIV_OP:
        case AND_OP:
            this->mulop();
            this->term1();
            break;
        default:
            this->error();
    }
}

void Sintatico::factor_a() {
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
            this->factor();
            break;
        case NOT:
        case MINUS_OP:
            this->eat(this->tok_code);
            this->factor();
            break;
        default:
            this->error();
    }
}

void Sintatico::factor() {
    switch(this->tok_code) {
        case ID:
            this->eat(ID);
            break;
        case OPEN_PARENTHESIS:
            this->eat(OPEN_PARENTHESIS);
            this->expression1();
            this->eat(CLOSE_PARENTHESIS);
            break;
        case LITERAL:
        case NUM_CONST:
            this->constant();
            break;
        default:
            this->error();
    }
}


void Sintatico::relop() {
    switch(this->tok_code) {
        case EQ_OP:
        case GREATER_OP:
        case GE_OP:
        case LESS_OP:
        case LE_OP:
        case NE_OP:
            this->eat(this->tok_code);
            break;
        default:
            this->error();
    }
}

void Sintatico::addop() {
    switch(this->tok_code) {
        case SUM_OP:
        case MINUS_OP:
        case OR_OP:
            this->eat(this->tok_code);
            break;
        default:
            this->error();
    }
}

void Sintatico::mulop() {
    switch(this->tok_code) {
        case MULT_OP:
        case DIV_OP:
        case AND_OP:
            this->eat(this->tok_code);
            break;
        default:
            this->error();
    }
}

void Sintatico::constant() {
    switch(this->tok_code) {
        case LITERAL:
        case NUM_CONST:
            this->eat(this->tok_code);
            break;
        default:
            this->error();
    }
}



void Sintatico::error() {
    cout << "Syntax Error in line " << this->kesser->get_line() << "\n" << endl;
    exit(10);
}


/*
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
*/