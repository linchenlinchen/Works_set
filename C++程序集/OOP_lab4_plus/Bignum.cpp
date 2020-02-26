//
// Created by L2595 on 2019/5/25.
//

#include <iostream>
#include "Bignum.h"

Bignum::Bignum(){
    for (int i = 0; i < LENGTH; ++i) {
        this->data[i] = 0;
    }
    this->signal = true;
}
Bignum::Bignum(int* data, bool signal) {
    for (int i = 0; i < LENGTH; ++i) {
        this->data[i] = data[i];
    }
    this->signal = signal;
}
Bignum::Bignum(int num) {
    if(num < 0){
        this->signal = false;
        num = -num;
    } else{
        this->signal = true;
    }
    int pre = num;
    for (int &i : this->data) {
        int now_bit = pre%10;
        pre = pre/10;
        i = now_bit;
    }
}

void Bignum::print() {
    char sign = (this->signal)? '+': '-';
    char s = ((sign == '-') ? sign : ' ');
    std::cout<< s;
    int beginNumber = LENGTH - 1;
    /*高位的无效0不打印*/
    for (int i = beginNumber; i >= 0; i--) {
        if(this->data[i] != 0){
            beginNumber = i;
            break;
        }
        if(i == 0){
            beginNumber = 0;
        }
    }
    /*打印有效位*/
    for (int j = beginNumber; j >= 0; j--) {
        std::cout<<this->data[j];
    }
    std::cout<<';';
}

string Bignum::getPrint() {
    string sign = (this->signal)? "+": "-";
    string s = ((sign == "-") ? sign : "");
    int beginNumber = LENGTH - 1;
    /*高位的无效0不打印*/
    for (int i = beginNumber; i >= 0; i--) {
        if(this->data[i] != 0){
            beginNumber = i;
            break;
        }
        if(i == 0){
            beginNumber = 0;
        }
    }
    /*打印有效位*/
    for (int j = beginNumber; j >= 0; j--) {
        s.append(to_string(this->data[j]));
    }
    /*for (int i = LENGTH-1; i >= 0; i--) {
        sign.append(to_string(this->data[i]));
    }*/
    return s;
}
Bignum Bignum::operator-() {
    int data[LENGTH];
    for (int i = 0; i < LENGTH; ++i) {
        data[i] = this->data[i];
    }
    bool signal = !this->signal;
    return {data,signal};
}
bool Bignum::operator>(const Bignum &bignum) const {
    if(this->signal && bignum.signal){
        for (int i = LENGTH - 1; i >= 0; i--) {
            if(this->data[i] > bignum.data[i]){
                return true;
            }
            if(bignum.data[i] > this->data[i]){
                return false;
            }
        }
    }
    if(!this->signal && !bignum.signal){
        for (int i = LENGTH - 1; i >= 0; i--) {
            if(this->data[i] > bignum.data[i]){
                return false;
            }
            if(bignum.data[i] > this->data[i]){
                return true;
            }
        }
    }
    if(!this->signal && bignum.signal){
        return false;
    }
    if(this->signal && !bignum.signal){
        return true;
    }
    return false;
}
Bignum Bignum::operator+(const Bignum &bignum) {
    Bignum me = *this;
    Bignum you = bignum;
    Bignum result;

    if(this->signal && bignum.signal) {
        int nums[LENGTH];
        int carry = 0;
        for (int i = 0; i < LENGTH; ++i) {
            nums[i] = (carry + this->data[i] + bignum.data[i]) % 10;
            carry = (carry + this->data[i] + bignum.data[i]) / 10;
        }
        return {nums, true};
    }
    if(!bignum.signal){
        you = -you;
        result = me-you;
        return result;
    }
    if(!this->signal){
        me = -me;
        result = you-me;
        return result;
    }
}
Bignum Bignum::operator-(const Bignum &bignum) {
    Bignum me = *this;
    Bignum you = bignum;
    Bignum result;
    /*均为正数，即(a)-(b)的形式*/
    if(this->signal && bignum.signal){
        int carry = 0;
        int nums[LENGTH];
        /*b>a*/
        if(bignum>*this){
            return -(you-me);
        }
            /*a>=b*/
        else{
            for (int i = 0; i < LENGTH; ++i) {
                nums[i] = (this->data[i]-carry >= bignum.data[i]) ? (this->data[i]-bignum.data[i]-carry) : (this->data[i] - bignum.data[i] + 10 - carry);
                carry = (this->data[i]-carry >= bignum.data[i]) ? 0 : 1;
            }
            return Bignum(nums,true);
        }
    }
    /*减数是负数.即a-(-b)的形式*/
    if(!bignum.signal){
        you = -you;
        return (me+you);
    }
    /*被减数是负数，减数是正数。即(-a)-(b)的形式*/
    if(!this->signal){
        me = -me;
        return -(me+you);
    }
}
Bignum Bignum::operator*(const Bignum &bignum) {
    bool signal;
    signal = (this->signal && bignum.signal) || (!this->signal && !bignum.signal);

    Bignum result(0);
    for (int i = 0; i < LENGTH; ++i) {
        int carry = 0;
        int nums[LENGTH];
        for (int k = 0; k < i; ++k) {
            nums[k] = 0;
        }
        for (int j = 0; j < LENGTH; ++j) {
            nums[i+j] = (carry + this->data[i] * bignum.data[j])%10;
            carry = (carry + this->data[i] * bignum.data[j])/10;
        }
        Bignum temp(nums,signal);
        result = result + temp;
    }
    return result;
}
Bignum& Bignum::operator+=(const Bignum &bignum) {
    Bignum temp = *this + bignum;
    this->signal = temp.signal;
    for (int i = 0; i < LENGTH; ++i) {
        this->data[i] = temp.data[i];
    }
    return *this;
}
Bignum& Bignum::operator-=(const Bignum &bignum) {
    Bignum temp = *this - bignum;
    this->signal = temp.signal;
    for (int i = 0; i < LENGTH; ++i) {
        this->data[i] = temp.data[i];
    }
    return *this;
}


