//
// Created by L2595 on 2019/6/4.
//

#include <queue>
#include <iostream>
#include "Matrix.h"
#include "StackForCalculate.h"
using namespace std;



StackForCalculate::StackForCalculate(map<string,Matrix>& name_matrix) {
    this->name_matrix = name_matrix;
}
bool StackForCalculate::isOperator(string str){
    return !(str != "+=" && str != "-=" && str != "*" && str != "+" && str != "-" && str != "~");
}
Matrix& StackForCalculate::findMatrix(const string& name){
    map<string,Matrix>::iterator it;
    for (it = name_matrix.begin(); it!=name_matrix.end(); it++) {
        if(it->first == name){
            return it->second;
        }
    }
}
Matrix &StackForCalculate::getResult(vector<string> strs) {
    int length = strs.size();
    for (int i = 0; i < length; ++i) {
        if(isOperator(strs[i])){
            if(strs[i] == "*"){
                Matrix matrix1 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix matrix2 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix result = matrix2 * matrix1;
                stackForMatrix.push(result);
            } else if(strs[i] == "+"){
                Matrix matrix1 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix matrix2 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix result = matrix1 + matrix2;
                stackForMatrix.push(result);
            }
            else if(strs[i] == "-"){
                Matrix matrix1 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix matrix2 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix result = (matrix2 - matrix1);
                stackForMatrix.push(result);
            }
            else if(strs[i] == "+="){
                Matrix matrix1 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix& matrix2 = stackForMatrix.top();
                stackForMatrix.pop();
                matrix2 += matrix1;
                stackForMatrix.push(matrix2);
            }else if(strs[i] == "-="){
                Matrix matrix1 = stackForMatrix.top();
                stackForMatrix.pop();
                Matrix& matrix2 = stackForMatrix.top();
                stackForMatrix.pop();
                matrix2 -= matrix1;
                stackForMatrix.push(matrix2);
            }
        } else{
            const char* string = strs[i].c_str();
            if(string[0] == '0' || atoi(string) != 0){
                int number = atoi(string);
                int array[Matrix::Width][Matrix::Width] = {{number,0,0},{0,number,0},{0,0,number}};
                Matrix matrix(array);
                stackForMatrix.push(matrix);
            } else{
                Matrix& matrix = findMatrix(strs[i]);
                stackForMatrix.push(matrix);
            }

        }

    }
    return stackForMatrix.top();
//    bool isReverse = false;
//    queue<string> temp_queueForOperator;
//    queue<Matrix> temp_queueForMatrix;
//    /*第一次循环去除~*/
//    for (int i = 0; i < length; ++i) {
//        if(isOperator(strs[i])){
//            isReverse = false;
//            if(strs[i] == "~"){
//                isReverse = true;
//            } else {
//                temp_queueForOperator.push(strs[i]);
//            }
//        } else{
//            Matrix matrix = findMatrix(strs[i]);
//            if(isReverse){matrix = ~matrix;}
//            temp_queueForMatrix.push(matrix);
//        }
//    }
//
//
//    /*得到结果*/
//    int len = temp_queueForMatrix.size();
//    for (int j = 0; j < len; ++j) {
//        stackForMatrix.push(temp_queueForMatrix.front());
//        temp_queueForMatrix.pop();
//
//        stackForOperator.push(temp_queueForOperator.front());
//        if(temp_queueForOperator.front() == "*"){
//            Matrix matrix;
//            matrix = (stackForMatrix.top() * temp_queueForMatrix.front());
//            stackForMatrix.pop();
//            stackForMatrix.push(matrix);
//        }
//        temp_queueForOperator.pop();
//    }
}

