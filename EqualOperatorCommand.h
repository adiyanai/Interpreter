//
// Created by adi on 18/12/18.
//

#ifndef PROJECT1_EQUALOPERATORCOMMAND_H
#define PROJECT1_EQUALOPERATORCOMMAND_H
#include "Command.h"


class EqualOperatorCommand : Command{

public:
    EqualOperatorCommand();
    int doCommand(vector<string> info, int index, SymbolTable* varsMap);
};


#endif //PROJECT1_EQUALOPERATORCOMMAND_H
