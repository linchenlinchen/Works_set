#include <iostream>
#include <fstream>
#include <map>
#include "Bignum.h"
#include "Matrix.h"
#include "FileUtil.h"
#include "StackForCalculate.h"
using namespace std;


template<typename T>
void _swap(T &a, T &b)
{
    T tmp = T();
    tmp = a;
    a = b;
    b = tmp;
}

vector<string> splitToVec(const vector<string>& strs){
    int length = strs.size();
    vector<string> result;
    for (int i = 0; i < length; ++i) {
        string::size_type pos;
        if((pos = strs[i].find("+="))!= -1 && strs[i] != "+="){
            result.push_back(strs[i].substr(0,pos));
            result.emplace_back("+=");
            result.push_back(strs[i].substr(pos+2,strs[i].size()-(pos+2)));
        } else if((pos = strs[i].find("-="))!= -1 && strs[i] != "-="){
            result.push_back(strs[i].substr(0,pos));
            result.emplace_back("-=");
            result.push_back(strs[i].substr(pos+2,strs[i].size()-(pos+2)));
        } else if((pos = strs[i].find('*'))!= -1 && strs[i] != "*"){
            result.push_back(strs[i].substr(0,pos));
            result.emplace_back("*");
            result.push_back(strs[i].substr(pos+1,strs[i].size()-(pos+1)));
        } else if((pos = strs[i].find('+'))!= -1 && strs[i] != "+" && strs[i] != "+="){
            result.push_back(strs[i].substr(0,pos));
            result.emplace_back("+");
            result.push_back(strs[i].substr(pos+1,strs[i].size()-(pos+1)));
        } else if((pos = strs[i].find('-'))!= -1 && strs[i] != "-" && strs[i] != "-=" && strs[i].find('-') != 0){
            result.push_back(strs[i].substr(0,pos));
            result.emplace_back("-");
            result.push_back(strs[i].substr(pos+1,strs[i].size()-(pos+1)));
        }  else{
            result.push_back(strs[i]);
        }
    }
    return  result;
}
bool isNeedSplit(const vector<string>& strs){
    int length = strs.size();
    for (int i = 0; i < length; ++i) {
        if(strs[i] != "+=" && strs[i] != "-=" && strs[i] != "*" && strs[i] != "+" && strs[i] != "-" &&
        (strs[i].find('+')!=-1 || (strs[i].find('-') != -1 && strs[i].find('-') != 0) || strs[i].find('*') != -1)){
            return true;
        }
    }
    return false;
}
bool isOperator(const string &str){
    return !(str != "+=" && str != "-=" && str != "*" && str != "+" && str != "-" && str != "~");
}
int getPriority(const string &str){
    if(str == "*"){
        return 3;
    } else if(str == "+" || str == "-"){
        return 2;
    } else if(str == "+=" || str == "-="){
        return 1;
    }
    return 0;
}
vector<string> getClearSplitResults(string str){
    vector<string> strs;
    strs.push_back(str);
    while (isNeedSplit(strs)){
        strs = splitToVec(strs);
    }
    return strs;
}
vector<string> getPosfixResult(vector<string> strs){
    int largest = 0;
    int length = strs.size();
    stack<string> stackForOperator;
    vector<string> posfix;
    for (int i = 0; i < length; ++i) {
        if(isOperator(strs[i])){
            int nowPriority = getPriority(strs[i]);
            if(nowPriority > largest){
                stackForOperator.push(strs[i]);
                largest = nowPriority;
            } else{
                int len = stackForOperator.size();
                for (int j = 0; j < len; j++) {
                    posfix.push_back(stackForOperator.top());
                    stackForOperator.pop();
                }
                stackForOperator.push(strs[i]);
                largest = nowPriority;
            }
        } else{
            posfix.push_back(strs[i]);
        }
    }
    int len = stackForOperator.size();
    for (int j = 0; j < len; j++) {
        posfix.push_back(stackForOperator.top());
        stackForOperator.pop();
    }
    return posfix;
}
int main() {
    auto *pair1 = new pair<vector<string*>,string>;
    delete(pair1);
    /*读写文件路径*/
    string matrixsPath = "testcase_matrix.in";
    string expressionPath = "testcase_expression.in";
    string resultPath = "result.out";

    /*读取matrix.in文件*/
    FileUtil fileUtil(matrixsPath);
    map<string,Matrix> name_matrix = fileUtil.getMatrixs();

    /*读取expression.in文件转化并计算结果*/
    FileUtil fileUtil1(expressionPath);
    ofstream out(resultPath);
    string line;
    while (!(line = fileUtil1.getLine()).empty()) {
        vector<string> splitResult = getClearSplitResults(line);
        vector<string> posfixResult = getPosfixResult(splitResult);
        StackForCalculate stackForCalculate(name_matrix);
        Matrix result = stackForCalculate.getResult(posfixResult);
        result.print();
        string input_result = result.getPrint();
        out << input_result;
        out << "\n";
    }



    return 0;
//
//    int data1[LENGTH] = {2,4,2,5,5,4,5,7,4,5,7,8,5,8,4,7};
//    Bignum bignum(data1,true);
//    int data2[LENGTH] = {5,7,2,5,7,8,5,3,1,2,3,1,8,5,0};
//    Bignum big(data2, false);
//    int a[3][3] = {{10,20,30},{40,50,60},{70,80,90}};
//    int b[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
//    int c[3][3] = {{4,2,6},{5,3,7},{0,-2,-8}};
//    Matrix matrix(a);
//    Matrix matrix1(b);
//    Matrix matrix2(c);
//    Matrix matrix3;
////    (matrix+matrix1-matrix2).print();
////    (matrix+matrix1*matrix2).print();
////    matrix3 = matrix+matrix1+=matrix2;
//////    (matrix+matrix1-=matrix2).print();
////    Matrix matrix4(b);
////    (-1*matrix4).print();
}

