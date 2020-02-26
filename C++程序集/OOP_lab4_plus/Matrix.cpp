#include <utility>

//
// Created by L2595 on 2019/6/1.
//

#include <iostream>
#include "Matrix.h"

Matrix operator*( int num,const Matrix& matrix){
    Matrix result;
    for (int i = 0; i < Matrix::Width; ++i) {
        for (int j = 0; j < Matrix::Width; ++j) {
            Bignum big_num(num);
            result.bignum[i][j] = (big_num * matrix.bignum[i][j]);
        }
    }
    return result;
}
Matrix operator*( const Matrix& matrix,int num){
    Matrix result;
    for (int i = 0; i < Matrix::Width; ++i) {
        for (int j = 0; j < Matrix::Width; ++j) {
            Bignum big_num(num);
            result.bignum[i][j] = (big_num * matrix.bignum[i][j]);
        }
    }
    return result;
}
Matrix::Matrix() = default;
Matrix::Matrix(Bignum bignum[Width][Width]){
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            this->bignum[i][j] = bignum[i][j];
        }
    }
}
Matrix::Matrix(int array[Width][Width]){
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            Bignum bignum1(array[i][j]);
            this->bignum[i][j] = bignum1;
        }
    }
}
Matrix Matrix::operator+(const Matrix &matrix) {
    Matrix matrix1;
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            matrix1.bignum[i][j] = this->bignum[i][j] + matrix.bignum[i][j];
        }
    }
    return matrix1;
}
Matrix Matrix::operator-(const Matrix &matrix) {
    Matrix matrix1;
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            matrix1.bignum[i][j] = this->bignum[i][j] - matrix.bignum[i][j];
        }
    }
    return matrix1;
}
void Matrix::print() {
    for (auto &i : bignum) {
        for (auto &j : i) {
            j.print();
            std::cout<<"    ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}
string Matrix::getPrint(){
    string result;
    for (int k = 0; k < Width; ++k) {
        for (int i = 0; i < Width; ++i) {
            result.append(bignum[k][i].getPrint());
            if(i != Width - 1){result.append(" ");}
        }
        result.append("\n");
    }
    return result;
}
Matrix Matrix::operator*(const Matrix &matrix) {
    Matrix matrix1;
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            Bignum block_result(0);
            for (int k = 0; k < Width; ++k) {
                block_result +=this->bignum[i][k]*matrix.bignum[k][j];
            }
            matrix1.bignum[i][j] = block_result;
        }
    }
    return matrix1;
}
Matrix Matrix::operator~() {
    Matrix result;
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            result.bignum[i][j] = this->bignum[j][i];
        }
    }
    return result;
}
Matrix& Matrix::operator+=(const Matrix &matrix) {
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            this->bignum[i][j] += matrix.bignum[i][j];
        }
    }
    return *this;
}
Matrix& Matrix::operator-=(const Matrix &matrix) {
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Width; ++j) {
            this->bignum[i][j] -= matrix.bignum[i][j];
        }
    }
    return *this;
}





