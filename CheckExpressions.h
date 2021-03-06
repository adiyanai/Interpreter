//
// Created by adi on 23/12/18.
//

#ifndef PROJECT1_CHECKEXPRESSIONS_H
#define PROJECT1_CHECKEXPRESSIONS_H

#include <string>
#include <vector>
using namespace std;

class CheckExpressions {

public:
    CheckExpressions();
    vector<string> getExpressions(vector<string> info, int index);
    string getNumber(string num);
    bool checkOperator(string s1, string s2);
    int getExpressionLength(string exp);
    int countCommas(vector<string> info, int index);
    int getLength(vector<string> info, int index);
};


#endif //PROJECT1_CHECKEXPRESSIONS_H
