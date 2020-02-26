//
// Created by L2595 on 2019/6/3.
//

#ifndef OOP_LAB4_PLUS_FILEUTIL_H
#define OOP_LAB4_PLUS_FILEUTIL_H
#include <fstream>
#include <string>
#include "Matrix.h"
#include <map>

using namespace std;

class FileUtil {
private:
    string path;
    ifstream in;
public:
    FileUtil(string path);
    Bignum str_to_bignum(string str);
    vector<string> split(const string &str,const string &pattern) ;
    map<string,Matrix> getMatrixs();
    string getLine();
};


#endif //OOP_LAB4_PLUS_FILEUTIL_H
