//
//  lexer.cpp
//  444_project
//
//  Created by Harrison Balogh on 10/19/17.
//  Copyright © 2017 Harxer. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include "rule.hpp"

using namespace std;
struct Token {
    string type = " ";
    string val = " ";
};

/// This lexical analyzer (or "scanner" or "lexer") transforms a character stream into
/// a token stream.
class Lexer {
    
    public:
    static vector<Token> getTokensFromLine(string input) {
        
        vector <Token> tokens;
        
        string wordAssembler = "";
        
        // Iterate through all input characters
        for (int c = 0; c < strlen(input.c_str()); c++) {
            
            // Check if this is a doublequote-braced string
            if (!wordAssembler.empty()) {
                // Check for a started string of text
                if (wordAssembler[0] == '\"') {
                    wordAssembler += input[c];
                    // Check for closing doublequote
                    if (input[c] == '\"' && c != 0) {
                        
                        // Add token
                        Token commentToken;
                        commentToken.type = to_string(5);
                        commentToken.val = wordAssembler;
                        tokens.push_back(commentToken);
                        
                        // Flush wordAssembler
                        wordAssembler = "";
                    }
                    continue;
                }
            }
            
            // Token delimited if whitespace, new line, or semicolon
            if ( isDelimiter( input[c]) ) {
                
                // Skip if wordAssembler is empty
                if (!wordAssembler.empty()) {
                    
                    // Add token
                    tokens.push_back(tokenDescriptionForWord(wordAssembler));
                    
                }
                
                // Output the delimiter if it isn't whitespace or end line
                if ( input[c] != ' ' && input[c] != '\n') {
                    tokens.push_back(tokenDescriptionForWord(string(1, input[c])));
                }
                
                // Flush builder
                wordAssembler = "";
                
            } else {
                
                // Character is not a delimiter but check if its a comment
                if (wordAssembler.length() > 0) {
                    // 2 slashes in a row indicates a comment. Stop reading rest of line.
                    if (wordAssembler[wordAssembler.length()-1] == '/' && input[c] == '/') {
                        // Don't read characters in line after determining it is a comment.
                        return tokens;
                    }
                }
                
                wordAssembler += input[c]; // Append token to builder string
            }
        }
        
        if (!wordAssembler.empty()) {
            // Leftover token after for-loop finishes - output it
            tokens.push_back(tokenDescriptionForWord(wordAssembler));
        }
        
        return tokens;
    }
    
    private:
    
    /// Looks up the given word and returns its ID in the GRAMMAR table.
    static Token tokenDescriptionForWord(string word) {
        
        Token token;
        
        map<int, string>::const_iterator it;
        // Lookup rule matching word. Only keywords, paired delimiters, punctuation, operators
        for (it = Rule::REGEX_GRAMMAR.begin(); it != Rule::REGEX_GRAMMAR.end(); ++it) {
            
            if (!word.compare(it -> second)) {
                token.type = to_string(it -> first);
                token.val = word;
                return token;
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
                token.type = to_string(2);
                token.val = word;
                return token;
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
                token.type = to_string(3);
                token.val = to_string((int)numberBuilder);
                return token;
            } else {
                // This is a float (id: 4)
                token.type = to_string(4);
                token.val = to_string(numberBuilder);
                return token;
            }
        }
        
        // Did not find token ID. (id: 99)
        token.type = to_string(99);
        token.val = word;
        return token;
    }
    
    /// Returns true if the given character
    static bool isDelimiter(char character) {
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
    
};














