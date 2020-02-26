//
// Created by L2595 on 2019/6/3.
//


#include <cstring>
#include "FileUtil.h"

FileUtil::FileUtil(string path){
    this->path = path;
    in.open(path);
}
Bignum FileUtil::str_to_bignum(string str){
    int data[LENGTH];
    memset(data,0,LENGTH * sizeof(int));
    int length = str.length();
    bool signal = true;
    int ples = 1;
    for (int i = 0; i < length; ++i) {
        if(i == 0 && str[0] == '-'){
            signal = false;
            continue;
        }
        data[length-i-ples] = str[i]-48;
    }
    Bignum bignum(data,signal);
    return bignum;
}
vector<string> FileUtil::split(const string &str,const string &pattern) {
    //const char* convert to char*
    char * strc = new char[strlen(str.c_str())+1];
    strcpy(strc, str.c_str());
    vector<string> resultVec;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultVec;
}
map<string, Matrix> FileUtil::getMatrixs() {
    string line;
    getline(in,line);
    int number = stoi(line);
    map<string,Matrix> name_matrix;
    if(in) {
        for (int i = 0; i < number; ++i) {
            getline(in,line);
            string name = line;
            Bignum bignums[Matrix::Width][Matrix::Width];
            for (int j = 0; j < Matrix::Width; ++j) {
                getline(in,line);
                const char* delim = " ";
                vector<string> result = split(line,delim);
                Bignum bignum1 = str_to_bignum(result[0]);
                Bignum bignum2 = str_to_bignum(result[1]);
                Bignum bignum3 = str_to_bignum(result[2]);
                bignums[j][0] = bignum1;
                bignums[j][1] = bignum2;
                bignums[j][2] = bignum3;
            }
            Matrix matrix4(bignums);
            pair <string,Matrix> pair1(name,matrix4);
            name_matrix.insert(pair1);
        }
    }

    map<string,Matrix>::iterator it;
    int length = name_matrix.size();
    for (it = name_matrix.begin(); length!=0; it++,length--) {
        pair<string,Matrix> temp_name_matrix("~"+it->first,~it->second);
        name_matrix.insert(temp_name_matrix);
    }
    return name_matrix;
}

string FileUtil::getLine() {
    string result;
    getline(in,result);
    return result;
}
