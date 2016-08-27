#include "Sintatico.h"

Sintatico::Sintatico(Lexico* analisador){
	this->kesser = analisador;
    this->advance();
}

void Sintatico::run() {
    nonterminal_stack.push(new NonTerminal(string("program")));
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
    NonTerminal *de, *st;
    switch(this->tok_code) {
        case VAR:
            this->eat(VAR);
            
            de = new NonTerminal("decl_list1");
            nonterminal_stack.push(de);
            this->decl_list1();
            this->eat(BEGIN);
            
            st = new NonTerminal("stmt_list1");
            nonterminal_stack.push(st);
            this->stmt_list1();
            this->eat(END);
            
            if(de->type == VOID)
                nonterminal_stack.top()->type = st->type;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
        case BEGIN:
            this->eat(BEGIN);
                st = new NonTerminal("stmt_list1");
                nonterminal_stack.push(st);
            this->stmt_list1();
            this->eat(END);
                nonterminal_stack.top()->type = st->type;
            break;
        default:
            this->error("program");
    }
    nonterminal_stack.pop();
}

void Sintatico::decl_list1() {
    NonTerminal *de, *dl;
    switch(this->tok_code) {
        case ID:
            de = new NonTerminal("decl");
            nonterminal_stack.push(de);
            this->decl();
            this->eat(SEMICOLON);
        
            dl = new NonTerminal("decl_list2");
            nonterminal_stack.push(dl);
            this->decl_list2();
            
            if(de->type == VOID)
                nonterminal_stack.top()->type = dl->type;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
        default:
            this->error("decl_list1");
    }
    nonterminal_stack.pop();
}

void Sintatico::decl_list2() {
    NonTerminal *dl;
    switch(this->tok_code) {
        case BEGIN:
            nonterminal_stack.top()->type = VOID;
            break;
        case ID:
            dl = new NonTerminal("decl_list1");
            nonterminal_stack.push(dl);
            this->decl_list1();
            
            nonterminal_stack.top()->type = dl->type;
            break;
        default:
            this->error("decl_list2");
    }
    nonterminal_stack.pop();
}

void Sintatico::decl() {
    NonTerminal *id, *ty;
    string identifier;
    switch(this->tok_code) {
        case ID:
            id = new NonTerminal("ident_list1");
            nonterminal_stack.push(id);
            this->ident_list1();
            this->eat(IS);
            
            ty = new NonTerminal("type");
            nonterminal_stack.push(ty);
            this->type();
            
            // Assign type to each identifier
            while (words.size() > 0) {
                identifier = words.top();
                words.pop();
                insert_type_ST(identifier, ty->type);
            }
            
            if(id->type != ERROR)
                nonterminal_stack.top()->type = VOID;
            break;
        default:
            this->error("decl");
    }
    nonterminal_stack.pop();
}

void Sintatico::ident_list1() {
    NonTerminal *id;
    Word*w;
    switch(this->tok_code) {
        case ID:
            w = static_cast<Word*>(this->tok);
            words.push(w->to_string());
            this->eat(ID);
            
            id = new NonTerminal("ident_list2");
            nonterminal_stack.push(id);
            this->ident_list2();
            
            nonterminal_stack.top()->type = id->type;
            break;
        default:
            this->error("ident_list1");
    }
    nonterminal_stack.pop();
}

void Sintatico::ident_list2() {
    NonTerminal *id;
    switch(this->tok_code) {
        case IS:
            nonterminal_stack.top()->type = VOID;
            break;
        case COMMA:
            this->eat(COMMA);
            
            id = new NonTerminal("ident_list1");
            nonterminal_stack.push(id);
            this->ident_list1();
            
            nonterminal_stack.top()->type = id->type;
            break;
        default:
            this->error("ident_list2");
    }
    nonterminal_stack.pop();
}

void Sintatico::type() {
    switch(this->tok_code) {
        case INT:
        case STRING:
            nonterminal_stack.top()->type = this->tok_code;
            this->eat(this->tok_code);
            break;
        default:
            this->error("type");
    }
    nonterminal_stack.pop();
}

void Sintatico::stmt_list1() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case ID:
        case IF:
        case DO:
        case IN:
        case OUT:
            ex = new NonTerminal("SEMICOLON");
            nonterminal_stack.push(ex);
            this->stmt();
            this->eat(SEMICOLON);
            
            ex2 = new NonTerminal("stmt_list2");
            nonterminal_stack.push(ex2);
            this->stmt_list2();
            
            nonterminal_stack.top()->type = VOID;
            break;
        default:
            this->error("stmt_list1");
    }
    nonterminal_stack.pop();
}

void Sintatico::stmt_list2() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case END:
        case ELSE:
        case WHILE:
            nonterminal_stack.top()->type = VOID;
            break;
        case ID:
        case IF:
        case DO:
        case IN:
        case OUT:
            ex = new NonTerminal("stmt_list1");
            nonterminal_stack.push(ex);
            this->stmt_list1();
            
            if(ex->type == VOID)
                nonterminal_stack.top()->type = VOID;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
        default:
            this->error("stmt_list2");
    }
    nonterminal_stack.pop();
}

void Sintatico::stmt() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case ID:
            ex = new NonTerminal("assign_stmt");
            nonterminal_stack.push(ex);
            this->assign_stmt();
            break;
        case IF:
            ex = new NonTerminal("if_stmt1");
            nonterminal_stack.push(ex);
            this->if_stmt1();
            break;
        case DO:
            ex = new NonTerminal("do_stmt");
            nonterminal_stack.push(ex);
            this->do_stmt();
            break;
        case IN:
            ex = new NonTerminal("read_stmt");
            nonterminal_stack.push(ex);
            this->read_stmt();
            break;
        case OUT:
            ex = new NonTerminal("write_stmt");
            nonterminal_stack.push(ex);
            this->write_stmt();
            break;
        default:
            this->error("stmt");
    }
    
    nonterminal_stack.top()->type = ex->type;
    nonterminal_stack.pop();
}

void Sintatico::assign_stmt() {
    NonTerminal *ex, *ex2;
    Word* w;
    int t;
    switch(this->tok_code) {
        case ID:
            w = static_cast<Word*>(this->tok);
            t = this->kesser->hashtable[(w->to_string())]->tipo;
            this->eat(ID);
            this->eat(ASSIGN_OP);
            
            ex = new NonTerminal("simple_expr1");
            nonterminal_stack.push(ex);
            this->simple_expr1();
            
            if(t == ex->type)
            nonterminal_stack.top()->type = VOID;
            break;
        default:
            this->error("assign_stmt");
    }
    nonterminal_stack.pop();
}

void Sintatico::if_stmt1() {
    NonTerminal *ex, *ex2, *ex3;
    switch(this->tok_code) {
        case IF:
            this->eat(IF);
            
            ex = new NonTerminal("condition");
            nonterminal_stack.push(ex);
            this->condition();
            this->eat(THEN);
            
            ex2 = new NonTerminal("stmt_list1");
            nonterminal_stack.push(ex2);
            this->stmt_list1();
            
            ex3 = new NonTerminal("if_stmt2");
            nonterminal_stack.push(ex3);
            this->if_stmt2();
            
            if (ex->type == INT && ex2->type == VOID)
                nonterminal_stack.top()->type = ex3->type;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
        default:
            this->error("if_stmt1");
    }
    nonterminal_stack.pop();
}

void Sintatico::if_stmt2() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case END:
            this->eat(END);
            
            nonterminal_stack.top()->type = VOID;
            break;
        case ELSE:
            this->eat(ELSE);
            
            ex = new NonTerminal("stmt_list1");
            nonterminal_stack.push(ex);
            this->stmt_list1();
            this->eat(END);
            
            nonterminal_stack.top()->type = ex->type;
            break;
        default:
            this->error("if_stmt2");
    }
    nonterminal_stack.pop();
}

void Sintatico::condition() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            ex = new NonTerminal("expression1");
            nonterminal_stack.push(ex);
            this->expression1();
            
            nonterminal_stack.top()->type = ex->type;
            break;
        default:
            this->error("condition");
    }
    nonterminal_stack.pop();
}

void Sintatico::do_stmt() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case DO:
            this->eat(DO);
            this->stmt_list1();
            this->stmt_suffix();
            
            nonterminal_stack.top()->type = VOID;
            break;
        default:
            this->error("do_stmt");
    }
    nonterminal_stack.pop();
}

void Sintatico::stmt_suffix() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case WHILE:
            this->eat(WHILE);
            this->condition();
            
            nonterminal_stack.top()->type = VOID;
            break;
        default:
            this->error("stmt_suffix");
    }
    nonterminal_stack.pop();
}

void Sintatico::read_stmt() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case IN:
            this->eat(IN);
            this->eat(OPEN_PARENTHESIS);
            this->eat(ID);
            this->eat(CLOSE_PARENTHESIS);
            
            nonterminal_stack.top()->type = VOID;
            break;
        default:
            this->error("read_stmt");
    }
    nonterminal_stack.pop();
}

void Sintatico::write_stmt() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case OUT:
            this->eat(OUT);
            this->eat(OPEN_PARENTHESIS);
            
            ex = new NonTerminal("writable");
            nonterminal_stack.push(ex);
            this->writable();
            this->eat(CLOSE_PARENTHESIS);
            
            if (ex->type == INT || ex->type == VOID)
                nonterminal_stack.top()->type = VOID;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
        default:
            this->error("write_stmt");
    }
    nonterminal_stack.pop();
}

void Sintatico::writable() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            ex = new NonTerminal("simple_expr1");
            nonterminal_stack.push(ex);
            this->simple_expr1();
            
            nonterminal_stack.top()->type = ex->type;
            break;
        default:
            this->error("writable");
    }
    nonterminal_stack.pop();
}

void Sintatico::expression1() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case CLOSE_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            ex = new NonTerminal("simple_expr1");
            nonterminal_stack.push(ex);
            this->simple_expr1();
            
            ex2 = new NonTerminal("expression2");
            nonterminal_stack.push(ex2);
            this->expression2();
            
            if (ex->type == INT && (ex2->type == INT || ex2->type == VOID))
                nonterminal_stack.top()->type = ex->type;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
        default:
            this->error("expression1");
    }
    nonterminal_stack.pop();
}

void Sintatico::expression2() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case CLOSE_PARENTHESIS:
        case SEMICOLON:
        case THEN:
            nonterminal_stack.top()->type = VOID;
            break;
        case EQ_OP:
        case GREATER_OP:
        case GE_OP:
        case LESS_OP:
        case LE_OP:
        case NE_OP:
            ex = new NonTerminal("relop");
            nonterminal_stack.push(ex);
            this->relop();
            
            ex2 = new NonTerminal("simple_expr1");
            nonterminal_stack.push(ex2);
            this->simple_expr1();
            
            nonterminal_stack.top()->type = ex2->type;
            break;
        default:
            this->error("expression2");
    }
    nonterminal_stack.pop();
}

void Sintatico::simple_expr1() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            ex = new NonTerminal("term1");
            nonterminal_stack.push(ex);
            this->term1();
            
            ex = new NonTerminal("simple_expr2");
            nonterminal_stack.push(ex);
            this->simple_expr2();
            
            if (ex->type == INT && (ex2->type == INT || ex2->type == VOID))
                nonterminal_stack.top()->type = ex->type;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
            break;
        default:
            this->error("simple_expr1");
    }
    nonterminal_stack.pop();
}

void Sintatico::simple_expr2() {
    NonTerminal *ex, *ex2;
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
            nonterminal_stack.top()->type = VOID;
            break;
        case SUM_OP:
        case MINUS_OP:
        case OR_OP:
            ex = new NonTerminal("addop");
            nonterminal_stack.push(ex);
            this->addop();
            
            ex2 = new NonTerminal("simple_expr1");
            nonterminal_stack.push(ex2);
            this->simple_expr1();
            
            nonterminal_stack.top()->type = ex2->type;
            break;
        default:
            this->error("simple_expr2");
    }
    nonterminal_stack.pop();
}

void Sintatico::term1() {
    NonTerminal *ex, *ex2;
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
        case NOT:
        case MINUS_OP:
            ex = new NonTerminal("factor_a");
            nonterminal_stack.push(ex);
            this->factor_a();
            
            ex2 = new NonTerminal("term2");
            nonterminal_stack.push(ex2);
            this->term2();
            
            if (ex->type == INT && (ex2->type == INT || ex2->type == VOID))
                nonterminal_stack.top()->type = ex->type;
            else
                nonterminal_stack.top()->type = ERROR;
            break;
        default:
            this->error("term1");
    }
    nonterminal_stack.pop();
}

void Sintatico::term2() {
    NonTerminal *ex, *ex2;
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
            nonterminal_stack.top()->type = VOID;
            break;
        case MULT_OP:
        case DIV_OP:
        case AND_OP:
            ex = new NonTerminal("mulop");
            nonterminal_stack.push(ex);
            this->mulop();
            
            ex2 = new NonTerminal("term1");
            nonterminal_stack.push(ex2);
            this->term1();
            
            nonterminal_stack.top()->type = ex2->type;
            break;
        default:
            this->error("term2");
    }
    nonterminal_stack.pop();
}

void Sintatico::factor_a() {
    NonTerminal *ex;
    switch(this->tok_code) {
        case ID:
        case LITERAL:
        case OPEN_PARENTHESIS:
        case NUM_CONST:
            ex = new NonTerminal("factor");
            nonterminal_stack.push(ex);
            this->factor();
            
            nonterminal_stack.top()->type = ex->type;
            break;
        case NOT:
        case MINUS_OP:
            this->eat(this->tok_code);
            
            ex = new NonTerminal("factor");
            nonterminal_stack.push(ex);
            this->factor();
            
            nonterminal_stack.top()->type = ex->type;
            break;
        default:
            this->error("factor_a");
    }
    nonterminal_stack.pop();
}

void Sintatico::factor() {
    NonTerminal *ex;
    Word *w;
    switch(this->tok_code) {
        case ID:
            w = static_cast<Word*>(this->tok);
            nonterminal_stack.top()->type = this->kesser->hashtable[(w->to_string())]->tipo;
            this->eat(ID);
            break;
        case OPEN_PARENTHESIS:
            this->eat(OPEN_PARENTHESIS);
            
            ex = new NonTerminal("expression1");
            nonterminal_stack.push(ex);
            this->expression1();
            this->eat(CLOSE_PARENTHESIS);
            
            nonterminal_stack.top()->type = ex->type;
            break;
        case LITERAL:
        case NUM_CONST:
            ex = new NonTerminal("constant");
            nonterminal_stack.push(ex);
            this->constant();
            
            nonterminal_stack.top()->type = ex->type;
            break;
        default:
            this->error("factor");
    }
    nonterminal_stack.pop();
}


void Sintatico::relop() {
    switch(this->tok_code) {
        case EQ_OP:
        case GREATER_OP:
        case GE_OP:
        case LESS_OP:
        case LE_OP:
        case NE_OP:
            nonterminal_stack.top()->type = VOID;
            this->eat(this->tok_code);
            break;
        default:
            this->error("relop");
    }
    nonterminal_stack.pop();
}

void Sintatico::addop() {
    switch(this->tok_code) {
        case SUM_OP:
        case MINUS_OP:
        case OR_OP:
            nonterminal_stack.top()->type = VOID;
            this->eat(this->tok_code);
            break;
        default:
            this->error("addop");
    }
    nonterminal_stack.pop();
}

void Sintatico::mulop() {
    switch(this->tok_code) {
        case MULT_OP:
        case DIV_OP:
        case AND_OP:
            nonterminal_stack.top()->type = VOID;
            this->eat(this->tok_code);
            break;
        default:
            this->error("mulop");
    }
    nonterminal_stack.pop();
}

void Sintatico::constant() {
    NonTerminal *id, *ty;
    switch(this->tok_code) {
        case LITERAL:
            nonterminal_stack.top()->type = STRING;
            this->eat(this->tok_code);
            break;
        case NUM_CONST:
            nonterminal_stack.top()->type = INT;
            this->eat(this->tok_code);
            break;
        default:
            this->error("constant");
    }
    nonterminal_stack.pop();
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
    cout << "stmt_suffix structure must be: \n \"while\" condition" << endl;
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
