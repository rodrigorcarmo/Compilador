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
		this->error(*this->non_terminal);
	}
}

//#define switch  cout << __FUNCTION__ << " " << this->tok_code << endl;\
this->non_terminal = new string(__FUNCTION__);switch


#define switch  this->non_terminal = new string(__FUNCTION__);switch
#define eat     non_terminal = new string(__FUNCTION__);this->eat


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
            this->error("program");
    }
}

void Sintatico::decl_list1() {
    switch(this->tok_code) {
        case ID:
            this->decl();
            this->eat(SEMICOLON);
            this->decl_list2();
            break;
        default:
            this->error("decl_list1");
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
            this->error("decl_list2");
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
            this->error("decl");
    }
}

void Sintatico::ident_list1() {
    switch(this->tok_code) {
        case ID:
            this->eat(ID);
            this->ident_list2();
            break;
        default:
            this->error("ident_list1");
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
            this->error("ident_list2");
    }
}

void Sintatico::type() {
    switch(this->tok_code) {
        case INT:
        case STRING:
            this->eat(this->tok_code);
            break;
        default:
            this->error("type");
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
            this->error("stmt_list1");
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
            this->error("stmt_list2");
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
            this->error("stmt");
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
            this->error("assign_stmt");
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
            this->error("if_stmt1");
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
            this->error("if_stmt2");
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
            this->error("condition");
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
            this->error("do_stmt");
    }
}

void Sintatico::stmt_suffix() {
    switch(this->tok_code) {
        case WHILE:
            this->eat(WHILE);
            this->condition();
            break;
        default:
            this->error("stmt_suffix");
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
            this->error("read_stmt");
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
            this->error("write_stmt");
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
            this->error("writable");
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
            this->error("expression1");
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
            this->error("expression2");
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
            this->error("simple_expr1");
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
            this->error("simple_expr2");
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
            this->error("term1");
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
            this->error("term2");
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
            this->error("factor_a");
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
            this->error("factor");
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
            this->error("relop");
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
            this->error("addop");
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
            this->error("mulop");
    }
}

void Sintatico::constant() {
    switch(this->tok_code) {
        case LITERAL:
        case NUM_CONST:
            this->eat(this->tok_code);
            break;
        default:
            this->error("constant");
    }
}

#undef switch
#undef eat



void Sintatico::error(string s) {
    cout << "Syntax Error in line " << this->kesser->get_line() << ":" <<
    this->kesser->get_column() << " in non_terminal \"" << s << "\"" << endl;
    

#define COMPARE_ERROR(NAME)     if(s.compare(#NAME)==0) goto NAME
#define ENDING                  goto exit_error;

    COMPARE_ERROR(program);
    COMPARE_ERROR(decl_list1);
    COMPARE_ERROR(decl_list2);
    COMPARE_ERROR(decl);
    COMPARE_ERROR(ident_list1);
    COMPARE_ERROR(ident_list2);
    COMPARE_ERROR(type);
    COMPARE_ERROR(stmt_list1);
    COMPARE_ERROR(stmt_list2);
    COMPARE_ERROR(stmt);
    COMPARE_ERROR(assign_stmt);
    COMPARE_ERROR(if_stmt1);
    COMPARE_ERROR(if_stmt2);
    COMPARE_ERROR(condition);
    COMPARE_ERROR(do_stmt);
    COMPARE_ERROR(stmt_suffix);
    COMPARE_ERROR(read_stmt);
    COMPARE_ERROR(write_stmt);
    COMPARE_ERROR(writable);
    COMPARE_ERROR(expression1);
    COMPARE_ERROR(expression2);
    COMPARE_ERROR(simple_expr1);
    COMPARE_ERROR(simple_expr2);
    COMPARE_ERROR(term1);
    COMPARE_ERROR(term2);
    COMPARE_ERROR(factor_a);
    COMPARE_ERROR(factor);
    COMPARE_ERROR(relop);
    COMPARE_ERROR(addop);
    COMPARE_ERROR(mulop);
    COMPARE_ERROR(constant);


    
    
program:
    cout << "Program structure must be: \n [\"var\" decl_list] \"begin\" stmt_list \"end\"" << endl;
    ENDING
    
decl_list1:
decl_list2:
    cout << "decl_list structure must be: \n decl \";\" {decl \";\"}" << endl;
    ENDING
    
decl:
    cout << "decl structure must be: \n ident-list \"is\" type" << endl;
    ENDING
    
ident_list1:
ident_list2:
    cout << "ident_list structure must be: \n identifier {\",\" ident_list}" << endl;
    ENDING
    
type:
    cout << "type must be either \"int\" or \"string\"" << endl;
    ENDING
    
stmt_list1:
stmt_list2:
    cout << "stmt_list structure must be: \n stmt \";\" [stmt_list]" << endl;
    ENDING
    
stmt:
    cout << "stmt must be either assign_stmt, if_stmt, do_stmt, read_stmt or write_stmt" << endl;
    ENDING
    
assign_stmt:
    cout << "assign_stmt structure must be: \n identifier \":=\" simple_expr" << endl;
    ENDING
    
if_stmt1:
if_stmt2:
    cout << "if_stmt structure must be: \n \"if\" condition \"then\" stmt_list {\"else\" stmt_list} \"end\"" << endl;
    ENDING
    
condition:
    cout << "condition must be an expression" << endl;
    ENDING
    
do_stmt:
    cout << "do_stmt structure must be: \n \"do\" stmt-list stmt_suffix" << endl;
    ENDING
    
stmt_suffix:
    cout << "stmt_suffix structure must be: \n \"while\ condition" << endl;
    ENDING
    
read_stmt:
    cout << "read_stmt structure must be: \n \"in\" \"(\" identifier \")\"" << endl;
    ENDING
    
write_stmt:
    cout << "stmt_suffix structure must be: \n \"out\" \"(\" writable \")\"" << endl;
    ENDING
    
writable:
    cout << "writable must be a simple_exp" << endl;
    ENDING
    
expression1:
expression2:
    cout << "expression structure must be: \n simple_expr [relop simple_expr]" << endl;
    ENDING
    
simple_expr1:
simple_expr2:
    cout << "simple_expr structure must be: \n [simple_expr addop] term" << endl;
    ENDING
    
term1:
term2:
    cout << "term structure must be: \n [term mulop] factor_a" << endl;
    ENDING
    
factor_a:
    cout << "factor_a structure must be: \n [\"not\"|\"-\"] factor" << endl;
    ENDING
    
factor:
    cout << "factor must be either identifier, constant or \"(\" expression \")\"" << endl;
    ENDING
    
relop:
    cout << "relop must be either \"=\", \">\", \">=\", \"<\", \"<=\" or \"<>\"" << endl;
    ENDING
    
addop:
    cout << "addop must be either \"+\", \"-\" or \"or\"" << endl;
    ENDING
    
mulop:
    cout << "mulop must be either \"*\", \"/\" or \"and\"" << endl;
    ENDING
    
constant:
    cout << "constant must be either an integer_const or a literal" << endl;
    ENDING
    
    
#undef COMPARE_ERROR
#undef ENDING
    
exit_error:
    exit(10);
}
