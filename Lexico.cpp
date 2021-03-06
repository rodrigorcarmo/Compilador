#include "Lexico.h"

/*
 Class constructor. Insert all reserved words into the symbols table.
 */
Lexico::Lexico(string filename) {
    this->line_mem2 = this->line_mem1 = this->line = 1;
    this->column_mem1 = this->column_mem1 = this->column = 0;
    this->file.open(filename.c_str());
    if(!this->file.is_open()){
        cout<<"File \"" << filename << "\"does not exist!" <<endl;
        return;
    }
    this->insertReserved(Word::Var);
    this->insertReserved(Word::Begin);
    this->insertReserved(Word::End);
    this->insertReserved(Word::If);
    this->insertReserved(Word::Else);
    this->insertReserved(Word::Then);
    this->insertReserved(Word::End);
    this->insertReserved(Word::Int);
    this->insertReserved(Word::String);
    this->insertReserved(Word::Do);
    this->insertReserved(Word::While);
    this->insertReserved(Word::Is);
    this->insertReserved(Word::In);
    this->insertReserved(Word::Out);
    this->insertReserved(Word::Not);
    this->insertReserved(Word::AndOp);
    this->insertReserved(Word::OrOp);
    this->next_char();
}

/*
 Compare next char of file to c
 */
bool Lexico::compareNext(char c) {
    this->ch=this->next_char();
    if(ch!=c)
        return false;
    return true;
}

/*
 Return next char of file or EOF if end of file
 */
int Lexico::next_char() {
    if((this->ch=file.get()) == EOF)   //read next char
        return EOF;
    this->column++;
    if(this->ch=='\n') {
        this->line++;
        this->column = 0;
    }
    return this->ch;
}

/*
 Check if char c is a delimiter
 */
bool Lexico::is_delimiter(char c) {
    string str(1, c);
    return delimiters.find(str) != std::string::npos;
}

/*
 Insert a reserved word into the symbols table
 */
void Lexico::insertReserved(Word *w) {
    pair<string,Word*> x (w->to_string(),w);
    hashtable.insert(x);

}

/*
 Analyze file and return next valid token found
 */
Token* Lexico::next_token() {
    Token* t;
    // Record line and column of previous 2 tokens
    this->line_mem2   = this->line_mem1;
    this->line_mem1   = this->line;
    this->column_mem2 = this->column_mem1;
    this->column_mem1 = this->column;
beginning:
    // Scape delimiters and EOF
    while(this->is_delimiter(this->ch))
        this->next_char();
    if(this->ch == EOF) {
        return new Token(-1);
    }

    if((t = this->rec_punc_relop()) != NULL)
        if(t->to_string()!="-1")
            return t;
        else
            goto beginning;
    if(this->ch=='{'){
        return this->rec_literal();
    }
    if(isdigit(this->ch)){
        return this->rec_number();
    }
    if(isalpha(this->ch) || this->ch == '_'){
        return this->rec_id_reserv();
    }

    // Char doesn't belong to alphabet
    this->display_error(0, "");
}

/*
 Jump in the file to the first position after a given string
 */
void Lexico::shift_to_after(string s) {
    string s_tmp;
    while(true) {
        s_tmp.clear();
        while(this->ch != s[0]) {
            this->next_char();
            if (this->ch == EOF)
                return;
        }
        for(int i=0; i<s.size(); i++) {
            if (this->ch != s[i])   // fake positive
                break;
            s_tmp += this->ch;
            this->next_char();
        }
        if(s.compare(s_tmp) == 0)
            break;
    }
}

/*
 Print symbols table
 */
void Lexico::print(){
    cout << "\nSymbols Table:\n\n";
    for(auto it=hashtable.begin(); it != hashtable.end();++it){
        cout << " " << (dynamic_cast<Token*>(it->second))->to_string() << "\t:\t" << it->first ;
        cout << std::endl;
    }
}


/*
 Recognize punctuation and relational operation
 */
Token* Lexico::rec_punc_relop() {
    switch(this->ch){
        case '=':
            this->next_char();
            return (Token*)Word::EqOp;
        case '>':
            if(compareNext('=')) {
                this->next_char();
                return (Token*)Word::GeOp;
            }
            else
                return (Token*)Word::GreaterOp;
        case '<':
            if(compareNext('=')) {
                this->next_char();
                return (Token*)Word::LeOp;
            }
            else if(this->ch == '>'){
                this->next_char();
                return (Token*)Word::NeOp;
            }
            else return (Token*)Word::LessOp;
        case '+':
            this->next_char();
            return (Token*)Word::SumOp;
        case '-':
            this->next_char();
            return (Token*)Word::MinusOp;
        case '*':
            this->next_char();
            return (Token*)Word::MultOp;
        case '/':
            if(compareNext('/')) {    // one line comment
                this->shift_to_after("\n");
                return new Token(-1);
            }
            return (Token*)Word::DivOp;
        case '%':
                // multiple lines comment
                this->next_char();
                this->shift_to_after("%");
                return new Token(-1);   
        case '(':
            this->next_char();
            return (Token*)Word::OpenParenthesis;
        case ')':
            this->next_char();
            return (Token*)Word::CloseParenthesis;
        case ',':
            this->next_char();
            return (Token*)Word::Comma;
        case ';':
            this->next_char();
            return (Token*)Word::Semicolon;
        case ':':
            if(compareNext('=')) {
                this->next_char();
                return (Token*)Word::AssignOp;
            }
            this->display_error(1, ":");
        default:
            return NULL;
    }
}

/*
 Recognize literal
 */
Token* Lexico::rec_literal() {
    string s = "";
    this->next_char();
    while(this->ch!='\n' && this->ch!='}' && this->ch!='{'){
        s+=this->ch;
        this->next_char();
    }
    switch(this->ch) {
        case '{':
        case '\n':
            this->display_error(3, s+this->ch);
            break;
        case '}':
            this->ch=next_char();
    }
    return (Token*)(new Literal(s));
}

/*
 Recognize number
 */
Token* Lexico::rec_number() {
    int value = 0;
    do{
        value = 10*value + atoi(&ch);
        this->ch=next_char();
    }while (isdigit(ch));
    return (Token*)(new Num(value));
}

/*
 Recognize identifier or reserved word
 */
Token* Lexico::rec_id_reserv() {
    string s = "";
    if (this->ch == '_') {  // There must be at least 1 char or digit
        s+=this->ch;
        this->ch=next_char();
        if(!isalpha(this->ch) && !isdigit(this->ch))
            this->display_error(2, s);
    }
    do{
        s+=this->ch;
        this->ch=next_char();
    }while(isalpha(this->ch) | isdigit(this->ch));
    if(s.size() > 15)
        this->display_error(4, s);
    return this->insert_word(s);
}

/*
 Display detailed error message and quit execution
 */
void Lexico::display_error(int n, string s) {
    switch(n) {
        case 0:
            cout << "Error: Character : \'" << this->ch <<
            "\' in line " << this->line << ":" << this->column <<
            " does not belong to language Ke$ia" << endl;
            exit(0);
        case 1:
            cout << "Error: Invalid lexeme \"" << s <<
            "\" in line " << this->line << ":" << this->column << endl;
            exit(1);
        case 2:
            cout << "Error: Invalid identifier name \"" << s <<
            "\" in line " << this->line << ":" << this->column << endl;
            exit(2);
        case 3:
            cout << "Error: Wrong format of literal \"" << s <<
            "\" in line " << this->line << ":" << this->column << endl;
            exit(3);
        case 4:
            cout << "Error: Identifier's name \"" << s <<
            "\" in line " << this->line << ":" << this->column <<
            " exceeds maximum length" << endl;
            exit(4);
    }
}

Token* Lexico::insert_word(string s) {
    Word* w;
    unordered_map<string,Word*>::const_iterator got = hashtable.find(s);
    if(got==hashtable.end()){
        w = new Word(s,ID);
        hashtable.insert(std::make_pair<string,Word*>(w->to_string(),((Word*)w)));
        return (Token*)w;
    }
    return (Token*)(got->second);
}

int Lexico::get_line() {
    return this->line_mem1;
}

int Lexico::get_column() {
    return this->column_mem1;
}


