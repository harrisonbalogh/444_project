void Parser_map();
void loadGrammarMap();
map <int,string> Parser_map;
map<int, string> REGEX_GRAMMAR;
using namespace std;

class Rule() {
  void Parser_map () {
    Parser_map[] = "BBlock";        //Pgm
    Parser_map[] = "Vargroup";      //BBlock
    Parser_map[] = "PPVarlist";     //Vargroup
    Parser_map[] = "Vardecl";       //Varlist
    Parser_map[] = "Varlist";       //PPvarlist, Varlist
    Parser_map[] = "Stmt";          //Stmts
    Parser_map[] = "Stmts";         //Stmts
    Parser_map[] = "Varid";         //stasgn
    Parser_map[] = "PPexpr1";       //stprint
    Parser_map[] = "Expr";          //PPexpr1
    Parser_map[] = "Fact";          //T, Term,
    Parser_map[] = "Rterm";         //E, Expr
    Parser_map[] = "Exprlist";      //PPexprs, Moreexprs
    Parser_map[] = "Basekind";      //Vardecl
    Parser_map[] = "Opadd";         //Rterm
    Parser_map[] = "Term";          //R, Rterm
    Parser_map[] = "Oprel";         //Expr
    Parser_map[] = "Opmul";         //Term
    Parser_map[] = "Lthan";         //Oprel
    Parser_map[] = "Gthan";         //Oprel
    Parser_map[] = "kwdvars";       //Vargroup
    Parser_map[] = "kwdwhile";      //Stwhile
    Parser_map[] = "kwdprog";       //PGM
    Parser_map[] = "'int'";         //Basekind
    Parser_map[] = "'float'";       //Basekind
    Parser_map[] = "'string'";      //Basekind
    Parser_map[] = "Moreexprs"      //Exprlist
    Parser_map[] = "id"             //Varid
    Parser_map[] = "E";             //E, Expr
    Parser_map[] = "R";             //R, Rterm
    Parser_map[] = "T";             //T, Term
    Parser_map[] = "Stwhile";       //Stmt
    Parser_map[] = "Stprint";       //Stmt
Parser_map[] = "Stasgn";        //Stmt
Parser_Map[] = "eps";           //E, R, T, Moreexprs, Stmts, Varlist, Vargrop,
}

/// Maps all REGEX grammar rules with their ID numbers.
void loadGrammarMap() {
    // Unpaired Delimiters
    REGEX_GRAMMAR[6] = ","; // comma
    REGEX_GRAMMAR[7] = ";"; // semi
    
    // Keywords
    REGEX_GRAMMAR[10] = "prog";     // kprog
    REGEX_GRAMMAR[11] = "main";     // kmain
    REGEX_GRAMMAR[12] = "fcn";      // kfcn
    REGEX_GRAMMAR[13] = "class";    // kclass
    REGEX_GRAMMAR[15] = "float";    // kfloat
    REGEX_GRAMMAR[16] = "int";      // kint
    REGEX_GRAMMAR[17] = "string";   // kstring
    REGEX_GRAMMAR[18] = "if";       // kif
    REGEX_GRAMMAR[19] = "elseif";   // kelseif
    REGEX_GRAMMAR[20] = "else";     // kelse
    REGEX_GRAMMAR[21] = "while";    // kwhile
    REGEX_GRAMMAR[22] = "input";    // kinput
    REGEX_GRAMMAR[23] = "print";    // kprint
    REGEX_GRAMMAR[24] = "new";      // knew
    REGEX_GRAMMAR[25] = "return";   // kreturn
    REGEX_GRAMMAR[31] = "<";        // angle1
    REGEX_GRAMMAR[32] = ">";        // angle2
    REGEX_GRAMMAR[33] = "{";        // brace1
    REGEX_GRAMMAR[34] = "}";        // brace2
    REGEX_GRAMMAR[35] = "[";        // bracket1
    REGEX_GRAMMAR[36] = "]";        // bracket2
    REGEX_GRAMMAR[37] = "(";        // parens1
    REGEX_GRAMMAR[38] = ")";        // parens2
    
    // Other punctuation
    REGEX_GRAMMAR[41] = "*";        // aster
    REGEX_GRAMMAR[42] = "^";        // caret
    REGEX_GRAMMAR[43] = ":";        // colon
    REGEX_GRAMMAR[44] = ".";        // dot
    REGEX_GRAMMAR[45] = "=";        // equals
    REGEX_GRAMMAR[46] = "-";        // minus
    REGEX_GRAMMAR[47] = "+";        // plus
    REGEX_GRAMMAR[48] = "/";        // splash
    
    // Multi-char operators
    REGEX_GRAMMAR[51] = "->";       // oparrow
    REGEX_GRAMMAR[52] = "==";       // opeq
    REGEX_GRAMMAR[53] = "!=";       // opne
    REGEX_GRAMMAR[54] = "<=";       // ople
    REGEX_GRAMMAR[55] = ">=";       // opge
    REGEX_GRAMMAR[56] = "<<";       // opshl
    REGEX_GRAMMAR[57] = ">>";       // opshr
}
}



