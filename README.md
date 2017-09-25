# CECS 444 Project: A2 Lexer
    Creators: Harrison Balogh, Bunly Buth, Mark Tan
    Files necessary to run program: main.cpp, in.txt
    This file describes the A2 Lexer and its functions.

# Description:
    This C++ program reads a txt file that consists of an A2 program and converts each character or string into a token.
    For each token, it will be displayed on the console with this format: 'character' is [character description].
    In order to assign an ID to each character or string, a map will be used to identify what each part of the program represents.
    This means that all characters can be easily assigned. For example, a comma (',') will have an ID of 6, therefore the two attributes will be incorporated together.

# Functions:
    string readFile()
        Creators: Harrison Balogh, Bunly Buth, Mark Tan
        This function requests a user to type in the file name for the desired program and reads the file.
    void parseTokens(string input)
        Creators: Harrison Balogh, Mark Tan
        This function produces token records based on a given input.
    int getTokenID(string word)
        Creator: Harrison Balogh
        This function looks up a given character or string and returns its ID in the grammar map.
    void loadGrammarMap()
        Creator: Mark Tan
        This function maps each character or string in the A2 lexicon into a grammar map.
    void loadGrammarDescriptorMap()
        Creator: Mark Tan
        This function maps each character or string in the A2 lexicon into a grammar description map.
    bool isDelimiter(char character)
        Creator: Harrison Balogh
        This function checks whether a given character is a delimiter.
