#pragma once

#include <stdlib.h>     /* rand */
#include <vector>
#include <iostream>
#include <stdexcept>
#include <bit>
// #include <string>

#include "../crom1/long_number.h"


class Generator{
protected:
    std::string gen_name = "Abstract Generator";
public:
    unsigned short int next_byte(){
        int curent_id = 0;
        unsigned short int res = 0;
        
        while(curent_id < 8){
            std::vector<bool> generated_v = next();

            for(auto b: generated_v){
                res = res | (b << curent_id);
                
                curent_id += 1;
            }
        }

        return res;
    }
    virtual std::vector<bool> next() = 0;
    std::string about(){
        return "Generator: " + gen_name;
    }
};

class BuildInGenerator: public Generator
{
public:
    BuildInGenerator(){
        gen_name = "BuildInGenerator";
    }
    std::vector<bool> next(){
        return std::vector<bool>{bool(rand() % 2)};
    }
};

class LehmerLowGenerator: public Generator
{
private:
    unsigned int a;
    unsigned int c;
    unsigned int x_c;

public:
    LehmerLowGenerator(unsigned int a, unsigned int c, unsigned int x_0): a(a), c(c), x_c(x_0){
        gen_name = "LehmerLowGenerator";
    }
    std::vector<bool> next(){
        unsigned int x_n = (a * x_c + c);
        x_c = x_n;

        unsigned int temp_x = get_lowest(x_c);
        std::vector<bool> res(8);
        for(int i = 7; i >= 0; --i){
            res[i] = temp_x & 1;
            temp_x = (temp_x >> 1);
        }

        return res;
    }
    unsigned int get_lowest(unsigned int x){
        return x & 0xFF;
    }
};

class LehmerHighGenerator: public Generator
{
private:
    unsigned int a;
    unsigned int c;
    unsigned int x_c;

public:
    LehmerHighGenerator(unsigned int a, unsigned int c, unsigned int x_0): a(a), c(c), x_c(x_0){
        gen_name = "LehmerHighGenerator";
    }
    std::vector<bool> next(){
        unsigned int x_n = (a * x_c + c);
        x_c = x_n;

        unsigned int temp_x = get_highest(x_c);
        std::vector<bool> res(8);
        for(int i = 7; i >= 0; --i){
            res[i] = temp_x & 1;
            temp_x = (temp_x >> 1);
        }

        return res;
    }
    unsigned int get_highest(unsigned int x){
        return (x >> 24) & 0xFF;
    }

};

class L20Generator: public Generator
{
private:
    unsigned int a;
public:
    L20Generator(unsigned int a): a(a){
        gen_name = "L20Generator";
    }
    std::vector<bool> next(){
        // for(int i = 0; i < 32; ++i){
        //     if(i == 12 || i == 23 || i == 27 || i == 29){
        //         std::cout << "|" << ((a >> 31-i) & 1) << "|" << " ";
        //     }
        //     else{
        //         std::cout << ((a >> 31-i) & 1) << " ";
        //     }
        // }

        // bool res = ((a >> 3) & 1) ^ ((a >> 5) & 1) ^ ((a >> 9) & 1) ^ ((a >> 20) & 1);
        // bool res = ((a >> 2) & 1) ^ ((a >> 4) & 1) ^ ((a >> 8) & 1) ^ ((a >> 19) & 1);
        bool res = ((a >> 2) & 1) ^ ((a >> 4) & 1) ^ ((a >> 8) & 1) ^ ((a >> 19) & 1);
        // std::cout << "[ " << ((a >> 2) & 1) << ((a >> 4) & 1) << ((a >> 8) & 1) << ((a >> 19) & 1) << "]";
        
        a = (a << 1) | res;

        return std::vector<bool>{res};
    }
};

class L89Generator: public Generator
{
private:
    std::vector<bool> vals;
public:
    L89Generator(std::vector<bool> vals): vals(vals){
        if(vals.size() != 89){
            throw std::invalid_argument("Error: invalid inital vector size " + std::to_string(vals.size()) + ".");
        }

        gen_name = "L89Generator";
    }
    L89Generator(unsigned int a){
        vals = std::vector<bool>(89);

        for(int i = 0; i < 32; ++i){
            vals[i] = a & 1;
            a = (a >> 1);
        }

        gen_name = "L89Generator";
    }
    std::vector<bool> next(){
        bool res = vals[0] ^ vals[1];
        
        for(int i = 1; i < vals.size(); ++i){
            vals[i - 1] = vals[i];
        }

        vals[89] = res;

        return std::vector<bool>{res};
    }
};



class GeffeGenerator: public Generator
{
private:
    unsigned int a_11;
    unsigned int a_9;
    unsigned int a_10;
public:
    GeffeGenerator(unsigned int a_11, unsigned int a_9, unsigned int a_10): a_11(a_11), a_9(a_9), a_10(a_10){
        l_9();
        l_9();
        l_10();

        gen_name = "GeffeGenerator";
    }
    std::vector<bool> next(){
        bool x = l_11();
        bool y = l_9();
        bool s = l_10();

        return std::vector<bool>{s && x ^ (true ^ s) && y};
    }
    bool l_11(){
        bool res = ((a_11 >> 10) & 1) ^ ((a_11 >> 8) & 1);

        a_11 = (a_11 << 1) | res;

        return res;
    }
    bool l_9(){
        bool res = ((a_9 >> 8) & 1) ^ ((a_9 >> 7) & 1) ^ ((a_9 >> 5) & 1) ^ ((a_9 >> 4) & 1);

        a_9 = (a_9 << 1) | res;

        return res;
    }
    bool l_10(){
        bool res = ((a_10 >> 9) & 1) ^ ((a_10 >> 6) & 1);

        a_10 = (a_10 << 1) | res;

        return res;
    }
        
};

class WolframGenerator: public Generator
{
private:
    unsigned int r;
public:
    WolframGenerator(unsigned int r): r(r){
        gen_name = "WolframGenerator";
    }
    std::vector<bool> next(){
        // r = (r <<< 1) ^ (r | (r >> 1))
        r = ((r << 1) | (r >> 31)) ^ (r | ((r >> 1) | (r << 31)));

        if(r % 2){
            return std::vector<bool>{true};
        }
        return std::vector<bool>{false};
    }
};

class LibrarianGenerator: public Generator
{
private:
    std::string trash_text;
public:
    LibrarianGenerator(std::string trash_text):trash_text(trash_text){
        gen_name = "LibrarianGenerator";
    }
    std::vector<bool> next(){
        std::vector<bool> res(0);
        for(auto c: trash_text){
            for(int i = 0; i < 8; ++i){
                res.push_back((c >> i) & 1);
            }
        }

        return res;
    }
};

class BlumMikaliGenerator: public Generator
{
private:
    LongNumber p = LongNumber("cea42b987c44fa642d80ad9f51f10457690def10c83d0bc1bcee12fc3b6093e3");
    LongNumber a = LongNumber("5b88c41246790891c095e2878880342e88c79974303bd0400b090fe38a688356");
    LongNumber comp_p = LongDivMod(LongSub(p, LongNumber("1")), LongNumber("2"));
public:
    LongNumber T_0;
    BlumMikaliGenerator(std::string T_0_str): T_0(LongNumber(T_0_str)){
        gen_name = "BlumMikaliGenerator";
    }
    std::vector<bool> next(){
        T_0 = LongModPowerBarrett(a, T_0, p);

        if(LongCmp(comp_p, T_0) == 1){
            return std::vector<bool>{true};
        }

        return std::vector<bool>{false};
    }
};

class BlumMikaliByteGenerator: public Generator
{
private:
    LongNumber p = LongNumber("cea42b987c44fa642d80ad9f51f10457690def10c83d0bc1bcee12fc3b6093e3");
    LongNumber a = LongNumber("5b88c41246790891c095e2878880342e88c79974303bd0400b090fe38a688356");
    LongNumber q = LongNumber("675215cc3e227d3216c056cfa8f8822bb486f788641e85e0de77097e1db049f1");
    LongNumber T_0;
    LongNumber comp_p = LongDivMod(LongSub(p, LongNumber("1")), LongNumber("2"));
public:
    BlumMikaliByteGenerator(std::string T_0_str): T_0(LongNumber(T_0_str)){
        gen_name = "BlumMikaliByteGenerator";
    }
    std::vector<bool> next(){
        T_0 =  LongModPowerBarrett(a, T_0, p);

        LongNumber temp = LongDivMod(LongMulOneDigit(T_0, 128), q);

        std::vector<bool> res(8);
        for(int i = 7; i >= 0; --i){
            res[i] = temp.at_bit(i);
        }

        return res;
    }
};

class BlumBlumShubaGenerator: public Generator
{
private:
    LongNumber p = LongNumber("d5bbb96d30086ec484eba3d7f9caeb07");
    LongNumber q = LongNumber("425d2b9bfdb25b9cf6c416cc6e37b59c1f");
    LongNumber n = LongMul(p, q);
    LongNumber r;
public:
    BlumBlumShubaGenerator(std::string r_str): r(LongNumber(r_str)){
        gen_name = "BlumBlumShubaGenerator";
    }
    std::vector<bool> next(){
        r = LongMulMod(r, r, n);
        r.smolarize();
        n.smolarize();
        
        if(r.at_bit(0)){
            return std::vector<bool>{true};
        }

        return std::vector<bool>{false};
    }
};

class BlumBlumShubaByteGenerator: public Generator
{
private:
    LongNumber p = LongNumber("d5bbb96d30086ec484eba3d7f9caeb07");
    LongNumber q = LongNumber("425d2b9bfdb25b9cf6c416cc6e37b59c1f");
    LongNumber n = LongMul(p, q);
    LongNumber r;
public:
    BlumBlumShubaByteGenerator(std::string r_str): r(LongNumber(r_str)){
        gen_name = "BlumBlumShubaByteGenerator";
    }
    std::vector<bool> next(){
        r = LongMulMod(r, r, n);
        r.smolarize();
        n.smolarize();
        
        std::vector<bool> res(8);
        for(int i = 0; i <8; ++i){
            res[i] = r.at_bit(i);
        }

        return res;
    }
};


