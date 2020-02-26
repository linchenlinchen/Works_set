//
// Created by L2595 on 2019/5/25.
//

#ifndef OOP_LAB4_BIGNUM_H
#define OOP_LAB4_BIGNUM_H



#include <string>
#include <vector>
using namespace std;

const int LENGTH = 60;


/*Bignum内data按照低位到高位存储*/
class Bignum {
private:
    int data[LENGTH];
    bool signal = true;/*0或者正数时是true*/
public:
    Bignum();
    Bignum(int data[LENGTH] , bool signal);
    Bignum(int num);
    void print();
    string getPrint();
    Bignum operator-();
    Bignum operator+(const Bignum& bignum);
    Bignum operator-(const Bignum& bignum);
    Bignum operator*(const Bignum& bignum);
    Bignum& operator+=(const Bignum& bignum);
    Bignum& operator-=(const Bignum& bignum);
    bool operator>(const Bignum& bignum) const ;
};


#endif //OOP_LAB4_BIGNUM_H
