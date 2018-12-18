//
// Created by adi on 17/12/18.
//

#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H
#include <string>
#include <vector>
#include <map>
#include "Command.h"
#include "CommandsMap.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
using namespace std;

class Parser {
map<string, Command*> commands;
SymbolTable varsMap;
public:
    Parser();
    void parser(vector<string> info);
};


#endif //PROJECT1_PARSER_H
