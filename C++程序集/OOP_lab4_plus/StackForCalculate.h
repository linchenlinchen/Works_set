//
// Created by L2595 on 2019/6/4.
//

#include <stack>
#include <map>
#include "Matrix.h"
#ifndef OOP_LAB4_PLUS_STACKFORCALCULATE_H
#define OOP_LAB4_PLUS_STACKFORCALCULATE_H
using namespace std;

class StackForCalculate {
public:
    map<string,Matrix> name_matrix;
    stack<Matrix> stackForMatrix;

    StackForCalculate(map<string,Matrix>& name_matrix);
    bool isOperator(string str);
    Matrix& findMatrix(const string& name);
    Matrix& getResult(vector<string> strs);
};


#endif //OOP_LAB4_PLUS_STACKFORCALCULATE_H
