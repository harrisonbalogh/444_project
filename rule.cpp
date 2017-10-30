#include <map>
#include <string>
#include "rule.hpp"

using namespace std;

map<int, string> Rule::REGEX_GRAMMAR;
map<int, string> Rule::PARSER_MAP;

//for map traversal, we start at 1 and not 0
//Map all Parser Rules
void Rule::parserMap() {
    PARSER_MAP[1] = "Pgm";
    PARSER_MAP[2] = "BBlock";
    PARSER_MAP[3] = "Vargroup";
    PARSER_MAP[4] = "PPVarlist";
    PARSER_MAP[5] = "Varlist";
    PARSER_MAP[6] = "Vardecl";
    PARSER_MAP[7] = "Basekind";
    PARSER_MAP[8] = "Varid";
    PARSER_MAP[9] = "Stmts";
    PARSER_MAP[10] = "Stmt";
    PARSER_MAP[11] = "Stasgn";
    PARSER_MAP[12] = "Stprint";
    PARSER_MAP[13] = "Stwhile";
    PARSER_MAP[14] = "PPexprs";
    PARSER_MAP[15] = "PPexpr1";
    PARSER_MAP[16] = "Exprlist";
    PARSER_MAP[17] = "Moreexprs";
    PARSER_MAP[18] = "E";
    PARSER_MAP[19] = "Expr";
    PARSER_MAP[20] = "R";
    PARSER_MAP[21] = "Rterm";
    PARSER_MAP[22] = "T";
    PARSER_MAP[23] = "Term";
    PARSER_MAP[24] = "Fact";
    PARSER_MAP[25] = "Oprel";
    PARSER_MAP[26] = "Lthan";
    PARSER_MAP[27] = "Gthan";
    PARSER_MAP[28] = "Opadd";
    PARSER_MAP[29] = "Opmul";
};

/// Maps all REGEX grammar rules with their ID numbers.
void Rule::loadGrammarMap() {
    REGEX_GRAMMAR[1] = "i";		//identifier
    REGEX_GRAMMAR[2] = "prog";	//kprog
    REGEX_GRAMMAR[3] = "vars";     	//vars
    REGEX_GRAMMAR[4] = "print";    	//kprint
    REGEX_GRAMMAR[5] = "while";    	//kwhile
    REGEX_GRAMMAR[6] = "int";      	//kint
    REGEX_GRAMMAR[7] = "float";    	//kfloat
    REGEX_GRAMMAR[8] = "string";   	//kstring
    REGEX_GRAMMAR[9] = ";"; 	// semi
    REGEX_GRAMMAR[10] = ","; 	// comma
    REGEX_GRAMMAR[11] = "=";        // opeq
    REGEX_GRAMMAR[12] = "+";        // plus
    REGEX_GRAMMAR[13] = "-";        // minus
    REGEX_GRAMMAR[14] = "*";        // aster
    REGEX_GRAMMAR[15] = "/";        // slash
    REGEX_GRAMMAR[16] = "!=";       // opne
    REGEX_GRAMMAR[17] = "<";        // angle1
    REGEX_GRAMMAR[18] = "<=";       // ople
    REGEX_GRAMMAR[19] = ">";        // angle2
    REGEX_GRAMMAR[20] = ">=";       // opge
    REGEX_GRAMMAR[21] = "^";        // caret
    REGEX_GRAMMAR[22] = "[";        // bracket1
    REGEX_GRAMMAR[23] = "]";        // bracket2
    REGEX_GRAMMAR[24] = "(";        // parens1
    REGEX_GRAMMAR[25] = ")";        // parens2
    REGEX_GRAMMAR[26] = "{";        // brace1
    REGEX_GRAMMAR[27] = "}";        // brace2
};
