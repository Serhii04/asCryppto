#ifndef LONG_NUMBER
#define LONG_NUMBER

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <stdio.h>

// Errors with windows
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

typedef uint32_t base_t;
const int num_size = 32;
const std::string HEX[16] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
};


class LongNumber{
public:
    LongNumber(int size);
    LongNumber(std::vector<uint64_t> number);
    LongNumber(std::string number);
    void print() const;
    std::string str() const;
    std::string to_string() const;
    void set(unsigned long long number);
    void set(std::vector<uint64_t> number);
    void set(LongNumber number);
    LongNumber set_by_hex(std::string number);
    int size() const;
    void resize(int size);
    std::string to_hex_string() const;
    int higest_bit_id() const;
    int lovest_bit() const;
    LongNumber smolarize();
    int at_bit(int i);

    std::vector<base_t> *number = nullptr;
};


#include "long_number_2.cpp"

LongNumber LongAdd(LongNumber A, LongNumber B);
int LongCmp(LongNumber A, LongNumber B);
LongNumber LongSub(LongNumber A, LongNumber B);
LongNumber LongMulOneDigit(LongNumber A, unsigned long long b);
LongNumber LongLeftShift(LongNumber A);
LongNumber LongShiftDigitsToHigh(LongNumber A, int l);
LongNumber LongLeftShift_expandable(LongNumber A);
LongNumber LongShiftDigitsToHigh_expandable(LongNumber A, int l);
LongNumber LongRightShift(LongNumber A);
LongNumber LongRightShift(LongNumber A, int n);
LongNumber LongMul(LongNumber A, LongNumber B);
int BitLength(LongNumber A);
LongNumber LongDivMod(LongNumber A, LongNumber B);
LongNumber LongDivFraction(LongNumber A, LongNumber B);
LongNumber LongPower1(LongNumber A, LongNumber B);
LongNumber LongPower2 (LongNumber A, LongNumber B);
LongNumber LongPowerWindow(LongNumber A, LongNumber B);
LongNumber LongSquare(LongNumber A);

LongNumber EuclidsBinaryAlgorithm(LongNumber A, LongNumber B);
LongNumber LongMin(LongNumber A, LongNumber B);
LongNumber GCD(LongNumber A, LongNumber B);
LongNumber LCM(LongNumber A, LongNumber B);
LongNumber BarrettReduction(LongNumber x, LongNumber n, LongNumber mu);
LongNumber BarrettReduction(LongNumber x, LongNumber n);
LongNumber LongModPowerBarrett(LongNumber A, LongNumber B, LongNumber N);
LongNumber LongAddMod(LongNumber A, LongNumber B, LongNumber N);
LongNumber LongSubMod(LongNumber A, LongNumber B, LongNumber N);
LongNumber LongMulMod(LongNumber A, LongNumber B, LongNumber N);
LongNumber LongSquareMulMod(LongNumber A, LongNumber N);

#endif 