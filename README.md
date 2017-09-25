# CECS 444 Project: A2 Lexer
//@author: Harrison Balogh, Charlie Buth, Mark Tan
//Files necessary to run program: main.cpp, in.txt

# Features:
    The desired text file is specified in the code itself, so if one were to test a different file, the appropriate lines of code must be changed to reflect that. Most importantly, the name of the file path must change depending on what file is desired for use and what operating system is chosen for running the program.

# Functions & Methods:
    string readFile()                   //@author: Harrison Balogh, Charlie Buth
    void parseTokens(string input)      //@author: Harrison Balogh, Mark Tan
    int getTokenID(string word)         //@author: Harrison Balogh
    void loadGrammarMap()               //@author: Mark Tan
    void loadGrammarDescriptorMap()     //@author: Mark Tan

# Bugs:
    Each line of code in your desired program must end with a space (' ') because this program considers it to be a possible line break in addition to the standard '\n'. However, text files do not have a function that allows line breaks to be written in the code without it actually appearing in a text editor. Therefore, if one were to leave the spaces out, the program would not compile user input as intended.

# Description:
    This C++ program reads a txt file that consists of an A2 program and converts each character or string into a token. For each token, it will be displayed on the console with this format: (Tok: <ID#> line= <line> str= "<token>" [int= <int> | float= <float>]?). In order to assign an ID to each character or string, a map will be used to identify what each part of the program represents. This means that all characters can be easily assigned. For example, a comma (',') will have an ID of 6, therefore the two attributes will be incorporated together.
