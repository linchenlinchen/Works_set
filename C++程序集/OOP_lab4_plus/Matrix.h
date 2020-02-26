//
// Created by L2595 on 2019/6/1.
//

#ifndef OOP_LAB4_MATRIX_H
#define OOP_LAB4_MATRIX_H

#include "Bignum.h"
#include <string>
using namespace std;

class Matrix {
private:
public:
    const static int Width = 3;
    Bignum bignum[Width][Width];

    Matrix();
    explicit Matrix(Bignum bignum[Width][Width]);
    explicit Matrix(int array[Width][Width]);
    void print();
    string getPrint();
    Matrix operator+(const Matrix& matrix);
    Matrix operator-(const Matrix& matrix);
    Matrix operator*(const Matrix& matrix);
    Matrix operator~();
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
};
Matrix operator*(int num,const Matrix& matrix);
Matrix operator*( const Matrix& matrix,int num);

#endif //OOP_LAB4_MATRIX_H
