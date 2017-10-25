#include <map>
#include <string>

void parserMap();
void loadGrammarMap();
using namespace std;

map<int, string> REGEX_GRAMMAR;
map<int, string> Parser_map;

//for map traversal, we start at 1 and not 0

class Rule {
	//Map all Parser Rules
	void parserMap() {
		Parser_map[1] = "Pgm";
		Parser_map[2] = "BBlock";
		Parser_map[3] = "Vargroup";
		Parser_map[4] = "PPVarlist";
		Parser_map[5] = "Varlist";
		Parser_map[6] = "Vardecl";
		Parser_map[7] = "Basekind";
		Parser_map[8] = "Varid";
		Parser_map[9] = "Stmts";
		Parser_map[10] = "Stmt";
		Parser_map[11] = "Stasgn";
		Parser_map[12] = "Stprint";
		Parser_map[13] = "Stwhile";
		Parser_map[14] = "PPexprs";
		Parser_map[15] = "PPexpr1";
		Parser_map[16] = "Exprlist";
		Parser_map[17] = "Moreexprs";
		Parser_map[18] = "E";
		Parser_map[19] = "Expr";
		Parser_map[20] = "R";
		Parser_map[21] = "Rterm";
		Parser_map[22] = "T";
		Parser_map[23] = "Term";
		Parser_map[24] = "Fact";
		Parser_map[25] = "Oprel";
		Parser_map[26] = "Lthan";
		Parser_map[27] = "Gthan";
		Parser_map[28] = "Opadd";
		Parser_map[29] = "Opmul";
	}

	/// Maps all REGEX grammar rules with their ID numbers.
	void loadGrammarMap() {
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
	}
};
