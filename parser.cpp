//  parser.cpp
//  444_project
//  9/25/17

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cmath>

using namespace std;

// Functions Prototypes
void parseTokens(string input, int atLine );
string tokenDescriptionForWord(string word, int atLine);
void loadGrammarMap();
bool isDelimiter(char character);

map<int, string> REGEX_GRAMMAR;

int main(int argc, const char * argv[]) {
    
    loadGrammarMap();
    
    // Read input from Stdin
    string input;
    getline( cin, input );
    int lineCount = 1;
    while ( getline( cin, input) ) {
        
        // Will parse and output token descriptions to standard output.
        parseTokens(input, lineCount);
        
        lineCount++;
        
        input = "";
        cin.clear();
    }
    
    return 0;
}

/// Parse token records for a given line and output to default cout.
void parseTokens(string input, int atLine ) {
    
    string buildToken = "";
    
    // Iterate through all input characters
    for (int c = 0; c < strlen(input.c_str()); c++) {
        
        // Check if this is a doublequote-braced string
        if (!buildToken.empty()) {
            // Check for a started string of text
            if (buildToken[0] == '\"') {
                buildToken += input[c];
                // Check for closing doublequote
                if (input[c] == '\"' && c != 0) {
                    
                    cout << "(Tok: " + to_string(5) + " line= " + to_string(atLine) + " str= \"" + buildToken + "\")" << endl;
                    
                    // Flush buildToken
                    buildToken = "";
                }
                continue;
            }
        }
        
        // Token delimited if whitespace, new line, or semicolon
        if ( isDelimiter( input[c]) ) {
            
            // Skip if buildToken is empty
            if (!buildToken.empty()) {
                
                // Output token
                cout << tokenDescriptionForWord(buildToken, atLine) << endl;
                
            }
            
            // Output the delimiter if it isn't whitespace or end line
            if ( input[c] != ' ' && input[c] != '\n') {
                cout << tokenDescriptionForWord(string(1, input[c]), atLine) << endl;
            }
            
            // Flush builder
            buildToken = "";
            
        } else {
            
            // Character is not a delimiter but check if its a comment
            if (buildToken.length() > 0) {
                // 2 slashes in a row indicates a comment. Stop reading rest of line.
                if (buildToken[buildToken.length()-1] == '/' && input[c] == '/') {
                    // Don't read characters in line after determining it is a comment.
                    return;
                }
            }
            
            buildToken += input[c]; // Append token to builder string
        }
    }
    
    if (!buildToken.empty()) {
        // Leftover token after for-loop finishes - output it
        cout << tokenDescriptionForWord(buildToken, atLine) << endl;
    }
}

/// Looks up the given word and returns its ID in the GRAMMAR table.
string tokenDescriptionForWord(string word, int atLine) {
    
    map<int, string>::const_iterator it;
    // Lookup rule matching word. Only keywords, paired delimiters, punctuation, operators
    for (it = REGEX_GRAMMAR.begin(); it != REGEX_GRAMMAR.end(); ++it) {
        
        if (!word.compare(it -> second)) {
            return "(Tok: " + to_string(it -> first) + " line= " + to_string(atLine) + " str= \"" + word + "\")";
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
            return "(Tok: " + to_string(2) + " line= " + to_string(atLine) + " str= \"" + word + "\")";
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
        if (floatAccuracy == -1) {
            // This is an int (id: 3)
            return "(Tok: " + to_string(3) + " line= " + to_string(atLine) + " str= \"" + word + "\" int= " + to_string((int)numberBuilder) + ")";
        } else {
            // This is a float (id: 4)
            return "(Tok: " + to_string(3) + " line= " + to_string(atLine) + " str= \"" + word + "\" float= " + to_string(numberBuilder) + ")";
        }
    }
    
    // Did not find token ID. (id: 99)
    return "(Tok: " + to_string(99) + " line= " + to_string(atLine) + " str= \"" + word + "\")";
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
