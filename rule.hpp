//
//  rule.h
//  444_project
//
//  Created by Harrison Balogh on 10/29/17.
//  Copyright © 2017 Harxer. All rights reserved.
//

#include <map>
#include <string>

#ifndef rule_h
#define rule_h

class Rule {
public:
    static std::map<int, std::string> REGEX_GRAMMAR;
    static std::map<int, std::string> PARSER_MAP;
    static void parserMap();
    static void loadGrammarMap();
};


#endif /* rule_h */
