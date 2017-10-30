//  parser.cpp
//  444_project
//
//  Authors: Harrison Balogh, Bunly Buth, Mark Tan
//
//  Contact: harrisonbalogh@gmail.com
//
//  9/25/17

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include "lexer.cpp"
#include "rule.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Rule::loadGrammarMap();
    Rule::parserMap();
    
    // Read input from Stdin
    string input;
    getline( cin, input );
    while ( getline( cin, input) ) {
        
        vector<string> tokens = Lexer::getTokensFromLine(input);
        
        for (int x = 0; x < tokens.size(); x++) {
            cout << tokens[x] << endl;
        }
        
        input = "";
        cin.clear();
    }
    
    return 0;
}
