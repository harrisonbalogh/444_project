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
#include <string>
#include <cmath>

using namespace std;

// Functions Prototypes
string readFile(); // Temporary method for reading the input
void parseTokens(string input);
int getTokenID(string word);
void loadGrammarMap();
void loadGrammarDescriptorMap();
bool isDelimiter(char character);

map<int, string> REGEX_GRAMMAR;
map<int, string> REGEX_GRAMMAR_DESCRIPTOR;

int main(int argc, const char * argv[]) {
    
    loadGrammarMap();
    loadGrammarDescriptorMap();
    
    string input = readFile();
    
    parseTokens(input);
    
    cout << endl;
    return 0;
}


/// Read in from file
string readFile() {
    string line;
    string buildString = "";
    ifstream fileIn ("/Users/harrisonbalogh/Developer/444_project/in.txt");
    
    if (fileIn.is_open()) {
        while ( getline(fileIn, line)) {
            buildString += line + "\n";
        }
    }
    else {
        cout << "Error: Couldn't open file." << endl;
    }
    fileIn.close();
    return buildString;
}

/// Parse token records from provided input.
void parseTokens(string input) {
    
    string buildToken = "";
    // This will allow iterator below to skip all remaining characters in a line if it encounters '//'
    bool commentedLine = false;
    
    // Iterate through all input
    for (int c = 0; c < strlen(input.c_str()); c++) {
        
        // Don't read characters in line after determining it is a comment.
        if (commentedLine) {
            // Toggle commentedLine flag if it is true and reached end of line.
            if ( input[c] == '\n') {
                buildToken = "";
                commentedLine = false;
            }
            continue;
        }
        
        // Check if this is a doublequote-braced string
        if (!buildToken.empty()) {
            // Check for a started string of text
            if (buildToken[0] == '\"') {
                buildToken += input[c];
                // Check for closing doublequote
                if (input[c] == '\"' && c != 0) {
                    
                    cout << "'" << buildToken << "' is " << REGEX_GRAMMAR_DESCRIPTOR[5] << endl;
                    
                    // Flush buildToken
                    buildToken = "";
                }
                continue;
            }
        }
        
        // Token delimited if whitespace, new line, or semicolon
        if ( isDelimiter( input[c]) ) {
            
            // Skip if buildToken is empty
            if (buildToken.empty()) {
                
                // Output the delimiter if it isn't whitespace or end line
                if ( input[c] != ' ' && input[c] != '\n') {
                    int delimiterID = getTokenID(string({input[c]}));
                    cout << "'" << input[c] << "' is " << REGEX_GRAMMAR_DESCRIPTOR[delimiterID] << endl;
                }
                
                continue;
            }
            
            cout << "'" << buildToken << "' is ";
            
            int tokenID = getTokenID(buildToken);
            
            // Output token
            cout << REGEX_GRAMMAR_DESCRIPTOR[tokenID] << endl;
            
            // Output the delimiter if it isn't whitespace or end line
            if ( input[c] != ' ' && input[c] != '\n') {
                int delimiterID = getTokenID(string({input[c]}));
                cout << "'" << input[c] << "' is " << REGEX_GRAMMAR_DESCRIPTOR[delimiterID] << endl;
            }
            
            // Flush builder
            buildToken = "";
            
        } else {
            
            // Character is not a delimiter but check if its a comment
            if (buildToken.length() > 0) {
                // 2 slashes in a row indicates a comment. Stop reading rest of line.
                if (buildToken[buildToken.length()-1] == '/' && input[c] == '/') {
                    commentedLine = true;
                    // Output found comment token
                    cout << "'//' is comment" << endl;
                    continue;
                }
            }
            
            buildToken += input[c];
        }
    }
    
    if (!buildToken.empty()) {
        // Leftover token after for-loop finishes
        cout << "'" << buildToken << "' is ";
        
        int tokenID = getTokenID(buildToken);
        
        // Output token
        cout << REGEX_GRAMMAR_DESCRIPTOR[tokenID] << endl;
    }
    cout << endl;
}

/// Looks up the given word and returns its ID in the GRAMMAR table.
int getTokenID(string word) {
    
    map<int, string>::const_iterator it;
    // Lookup rule matching word. Only keywords, paired delimiters, punctuation, operators
    for (it = REGEX_GRAMMAR.begin(); it != REGEX_GRAMMAR.end(); ++it) {
        
        if (!word.compare(it -> second)) {
            return it -> first;
        }
        
    }
    
    // Note if its a negative number for integer/float parsing
    bool negativePrefix = false;
    // Check for minus sign (plus sign is default)
    if (word.length() >= 2) {
        if (word[0] == '-') {
            negativePrefix = true;
        }
        if (word[0] == '+' || word[0] == '-') {
            // Truncate word to not include prefix
            word = word.substr(1);
        }
    }
    
    // Check if its an ID
    if (word.length() > 0) {
        // First character indicates if its an ID
        if ((word[0] >= 'A' && word[0] <= 'Z') || (word[0] >= 'a' && word[0] <= 'z') || word[0] == '_') {
            return 2;
        }
    }
    
    int floatAccuracy = -1; // Indicates the digit place of float. -1 means it's not a float
    float numberBuilder = -1; // -1 Indicates that no digits have yet been found
    
    for (int c = 0; c < word.length(); c++) {
        
        // Check if encounted a digit
        if (word[c] >= '0' && word[c] <= '9') {
            
            // Indicate when first digit has been found
            if (numberBuilder == -1)
                numberBuilder = 0;
            
            // Check if it's a float. If -1 is true, it's an Int
            if (floatAccuracy != -1) {
                
                // Increment float accuracy after adding current decimal place
                numberBuilder += (1 / pow(10, floatAccuracy++)) * (word[c] - '0');
                
            } else {
                // Shift current number and add new digit
                numberBuilder = numberBuilder * 10 + (word[c] - '0');
            }

        // Check if encountered a '.' and there are digits before the '.' and there wasn't already a '.'
        } else  if (word[c] == '.' && numberBuilder != -1 && floatAccuracy == -1) {
            
            floatAccuracy = 1;
            
        } else {
            
            // Character wasn't recognized, not a float or int.
            numberBuilder = -1; // indicate that no number was found
            break;
        
        }
    }
    
    // Check if number was parsed
    if (numberBuilder != -1) {
        
        // Int ID: 3, Float ID: 4
        return (floatAccuracy == -1) ? 3 : 4;
        
//        return negativePrefix ? -numberBuilder : numberBuilder;
    }
    
    // Did not find token ID.
    return 99; // Unknown Token ID
}

/// Returns true if the given character
bool isDelimiter(char character) {
    if (character == ' ') {
        return true;
    } else if (character == ';') {
        return true;
    } else if (character == ',') {
        return true;
    } else if (character == '\n') {
        return true;
    }
    return false;
}

/// Push a record to the console after it has been read in by parseTokens()
//void outputToken() {
    // output all token records, one per line.
//}

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
    
    // Miscellaneous
    
}

void loadGrammarDescriptorMap() {
    
    // Special words
    REGEX_GRAMMAR_DESCRIPTOR[2] = "id";         // .*
    REGEX_GRAMMAR_DESCRIPTOR[3] = "int";        // +/- & DIGITS
    REGEX_GRAMMAR_DESCRIPTOR[4] = "float";      // +/- & DIGITS . DIGITS
    REGEX_GRAMMAR_DESCRIPTOR[5] = "string";     // '"' .* '"'
    
    // Unpaired Delimiters
    REGEX_GRAMMAR_DESCRIPTOR[6] = "comma";      // ,
    REGEX_GRAMMAR_DESCRIPTOR[7] = "semi";       // ;
    
    // Keywords
    REGEX_GRAMMAR_DESCRIPTOR[10] = "kprog";     // prog
    REGEX_GRAMMAR_DESCRIPTOR[11] = "kmain";     // main
    REGEX_GRAMMAR_DESCRIPTOR[12] = "kfcn";      // fcn
    REGEX_GRAMMAR_DESCRIPTOR[13] = "kclass";    // class
    REGEX_GRAMMAR_DESCRIPTOR[15] = "kfloat";    // float
    REGEX_GRAMMAR_DESCRIPTOR[16] = "kint";      // int
    REGEX_GRAMMAR_DESCRIPTOR[17] = "kstring";   // string
    REGEX_GRAMMAR_DESCRIPTOR[18] = "kif";       // if
    REGEX_GRAMMAR_DESCRIPTOR[19] = "kelseif";   // elseif
    REGEX_GRAMMAR_DESCRIPTOR[20] = "kelse";     // else
    REGEX_GRAMMAR_DESCRIPTOR[21] = "kwhile";    // while
    REGEX_GRAMMAR_DESCRIPTOR[22] = "kinput";    // input
    REGEX_GRAMMAR_DESCRIPTOR[23] = "kprint";    // print
    REGEX_GRAMMAR_DESCRIPTOR[24] = "knew";      // new
    REGEX_GRAMMAR_DESCRIPTOR[25] = "kreturn";   // return
    REGEX_GRAMMAR_DESCRIPTOR[31] = "angle1";    // <
    REGEX_GRAMMAR_DESCRIPTOR[32] = "angle2";    // >
    REGEX_GRAMMAR_DESCRIPTOR[33] = "brace1";    // {
    REGEX_GRAMMAR_DESCRIPTOR[34] = "brace2";    // }
    REGEX_GRAMMAR_DESCRIPTOR[35] = "bracket1";  // [
    REGEX_GRAMMAR_DESCRIPTOR[36] = "bracket2";  // ]
    REGEX_GRAMMAR_DESCRIPTOR[37] = "parens1";   // (
    REGEX_GRAMMAR_DESCRIPTOR[38] = "parens2";   // )
    
    // Other punctuation
    REGEX_GRAMMAR_DESCRIPTOR[41] = "aster";     // *
    REGEX_GRAMMAR_DESCRIPTOR[42] = "caret";     // ^
    REGEX_GRAMMAR_DESCRIPTOR[43] = "colon";     // :
    REGEX_GRAMMAR_DESCRIPTOR[44] = "dot";       // .
    REGEX_GRAMMAR_DESCRIPTOR[45] = "equals";    // =
    REGEX_GRAMMAR_DESCRIPTOR[46] = "minus";     // -
    REGEX_GRAMMAR_DESCRIPTOR[47] = "plus";      // +
    REGEX_GRAMMAR_DESCRIPTOR[48] = "splash";    // /
    
    // Multi-char operators
    REGEX_GRAMMAR_DESCRIPTOR[51] = "oparrow";    // ->
    REGEX_GRAMMAR_DESCRIPTOR[52] = "opeq";       // ==
    REGEX_GRAMMAR_DESCRIPTOR[53] = "opne";       // !=
    REGEX_GRAMMAR_DESCRIPTOR[54] = "ople";       // <=
    REGEX_GRAMMAR_DESCRIPTOR[55] = "opge";       // >=
    REGEX_GRAMMAR_DESCRIPTOR[56] = "opshl";      // <<
    REGEX_GRAMMAR_DESCRIPTOR[57] = "opshr";      // >>
    
    // Miscellaneous
    REGEX_GRAMMAR_DESCRIPTOR[99] = "error";      // Unknown Token
}

















