//
//  main.cpp
//  444_project
//
//  Created by Harrison Balogh on 9/19/17.
//  Copyright © 2017 Harxer. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
using namespace std;

// Functions Prototypes
string readFile();
void parseTokens(string input);
int getTokenID(string word);
void loadGrammarMap();
void loadGrammarDescriptorMap();

map<int, string> REGEX_GRAMMAR;
map<int, string> REGEX_DESCRIPTOR_GRAMMAR;
int line_num = 1;

int main(int argc, const char * argv[]) {

    loadGrammarMap();
    loadGrammarDescriptorMap();
    string input = readFile();
    parseTokens(input);
    return 0;
}

// Read in from file
string readFile() {
    string line;
    string buildString = "";
    ifstream fileIn ("/Users/marktan/Documents/in.txt");

    if (fileIn.is_open()) {
        while ( getline(fileIn, line)) {
            buildString += line;
        }
    }
    else {
        cout << "Error: Couldn't open file." << endl;
    }
    fileIn.close();
    return buildString;
}

// Parse tokens within an input
void parseTokens(string input) {

    string buildToken = "";

    for (int c = 0; c < strlen(input.c_str()); c++) {
        if (input[c] == ' ' || input[c] == '\n') {

            // Whitespace - token delimited
            int tokenID = getTokenID(buildToken);
            cout << "(Tok: \t" << tokenID;
            cout << "\tline= " << line_num; //line_num needs to increment with each following line, will fix later

            if (tokenID == 0) {
                cout << "\tstr= \"" << buildToken << "\")";
            //if(tokenID == 5) remove quotes from str field, print buildToken
            //if(tokenID == 3 || tokenID == 4) cout << "int= " <<
            }else{
                cout << "\tstr= "  << REGEX_DESCRIPTOR_GRAMMAR[tokenID] << ")";
            }

            // Flush builder
            buildToken = "";
            cout << endl;
        } else {
            buildToken += input[c];
        }
    }
    if (buildToken.compare("")) {
        // Leftover token after for-loop finishes
        int tokenID = getTokenID(buildToken);
        cout << "(Tok: \t" << tokenID;
        cout << "\tline= " << line_num;

        if (tokenID == 0) {
            cout << "\tstr= \"" << buildToken << "\")";
            //if(tokenID == 5) remove quotes from str field, print buildToken
            //if(tokenID == 3 || tokenID == 4) cout << "int= " <<
        } else {
            cout << "\tstr= " << REGEX_DESCRIPTOR_GRAMMAR[tokenID] << ")";
        }
    }
    cout << endl;
}

/// Looks up the given word and returns its ID in the GRAMMAR table.
int getTokenID(string word) {

    map<int, string>::const_iterator it;
    for (it = REGEX_GRAMMAR.begin(); it != REGEX_GRAMMAR.end(); ++it) {
        if (!word.compare(it -> second)) {
            return it -> first;
        }
    }
    // Did not find token ID.
    return 0;
}

//Loads grammap into a map
void loadGrammarMap() {

	REGEX_GRAMMAR[2] = "";	// identifier
	REGEX_GRAMMAR[3] = "";	// integer
	REGEX_GRAMMAR[4] = "";	// float
	REGEX_GRAMMAR[5] = "";	// string

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

    // Miscellaneous
    REGEX_GRAMMAR[99] = "";			//error
    //REGEX_GRAMMAR[0] = "";			//eof
}

//Load descriptions for grammar in a map
void loadGrammarDescriptorMap() {
    // Unpaired Delimiters
    REGEX_DESCRIPTOR_GRAMMAR[6] = "comma";      // ,
    REGEX_DESCRIPTOR_GRAMMAR[7] = "semi";       // ;

    // Keywords
    REGEX_DESCRIPTOR_GRAMMAR[10] = "kprog";     // prog
    REGEX_DESCRIPTOR_GRAMMAR[11] = "kmain";     // main
    REGEX_DESCRIPTOR_GRAMMAR[12] = "kfcn";      // fcn
    REGEX_DESCRIPTOR_GRAMMAR[13] = "kclass";    // class
    REGEX_DESCRIPTOR_GRAMMAR[15] = "kfloat";    // float
    REGEX_DESCRIPTOR_GRAMMAR[16] = "kint";      // int
    REGEX_DESCRIPTOR_GRAMMAR[17] = "kstring";   // string
    REGEX_DESCRIPTOR_GRAMMAR[18] = "kif";       // if
    REGEX_DESCRIPTOR_GRAMMAR[19] = "kelseif";   // elseif
    REGEX_DESCRIPTOR_GRAMMAR[20] = "kelse";     // else
    REGEX_DESCRIPTOR_GRAMMAR[21] = "kwhile";    // while
    REGEX_DESCRIPTOR_GRAMMAR[22] = "kinput";    // input
    REGEX_DESCRIPTOR_GRAMMAR[23] = "kprint";    // print
    REGEX_DESCRIPTOR_GRAMMAR[24] = "knew";      // new
    REGEX_DESCRIPTOR_GRAMMAR[25] = "kreturn";   // return
    REGEX_DESCRIPTOR_GRAMMAR[31] = "angle1";    // <
    REGEX_DESCRIPTOR_GRAMMAR[32] = "angle2";    // >
    REGEX_DESCRIPTOR_GRAMMAR[33] = "brace1";    // {
    REGEX_DESCRIPTOR_GRAMMAR[34] = "brace2";    // }
    REGEX_DESCRIPTOR_GRAMMAR[35] = "bracket1";  // [
    REGEX_DESCRIPTOR_GRAMMAR[36] = "bracket2";  // ]
    REGEX_DESCRIPTOR_GRAMMAR[37] = "parens1";   // (
    REGEX_DESCRIPTOR_GRAMMAR[38] = "parens2";   // )

    // Other punctuation
    REGEX_DESCRIPTOR_GRAMMAR[41] = "aster";     // *
    REGEX_DESCRIPTOR_GRAMMAR[42] = "caret";     // ^
    REGEX_DESCRIPTOR_GRAMMAR[43] = "colon";     // :
    REGEX_DESCRIPTOR_GRAMMAR[44] = "dot";       // .
    REGEX_DESCRIPTOR_GRAMMAR[45] = "equals";    // =
    REGEX_DESCRIPTOR_GRAMMAR[46] = "minus";     // -
    REGEX_DESCRIPTOR_GRAMMAR[47] = "plus";      // +
    REGEX_DESCRIPTOR_GRAMMAR[48] = "splash";    // /

    // Multi-char operators
    REGEX_DESCRIPTOR_GRAMMAR[51] = "oparrow";    // ->
    REGEX_DESCRIPTOR_GRAMMAR[52] = "opeq";       // ==
    REGEX_DESCRIPTOR_GRAMMAR[53] = "opne";       // !=
    REGEX_DESCRIPTOR_GRAMMAR[54] = "ople";       // <=
    REGEX_DESCRIPTOR_GRAMMAR[55] = "opge";       // >=
    REGEX_DESCRIPTOR_GRAMMAR[56] = "opshl";      // <<
    REGEX_DESCRIPTOR_GRAMMAR[57] = "opshr";      // >>

    // Miscellaneous
    REGEX_DESCRIPTOR_GRAMMAR[99] = "error";		//Unknown token
    //REGEX_DESCRIPTOR_GRAMMAR[0] = "eof";		//end of file
}
