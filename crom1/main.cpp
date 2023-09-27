#include <iostream>

#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>

#include "long_number_tests.cpp"
#include "long_number.h"
#include "measurance.cpp"


using namespace std;

// int main(){
//     measure();

//     return 0;
// }

int main(){
    string s_1 = "baaab9165cc458e199cb89f51b135f7091a5abb0874df3e8cb4543a5eb93b0441e9ca4c2b0fb3d30875cbf29abd5b1acf389";
    string s_2 = "76931fac9dab2b36c248b87d6ae33f9a62d7183a5d5789e4b2d6b441e2411dc709e111c7e1e7acb6f8cac0bb2fc4c8bc2ae3";
    string s_3 = "84b35ae882809dd4cfe7abc5c616786746596596576596598778607596596508750850876087508767587658765876576567";
    string s_4 = "190"; // 400
    string s_5 = "1901901";


    LongNumber a(s_1), b(s_2), c(s_3), n(s_4), d(s_5);

    std::cout << std::endl << "Приклад обчислення gcd" << std::endl;
    std::cout << GCD(a, b).to_hex_string() << std::endl;

    std::cout << std::endl << "Приклад обчислення lcm" << std::endl;
    std::cout << LCM(a, b).to_hex_string() << std::endl;

    std::cout << std::endl << "Приклад обчислення модуля числа" << std::endl;
    std::cout << BarrettReduction(a, b).to_hex_string() << std::endl;

    std::cout << std::endl << "Приклад суми за модулем" << std::endl;
    std::cout << LongAddMod(a, b, c).to_hex_string() << std::endl;

    std::cout << std::endl << "Приклад різниці за модулем" << std::endl;
    std::cout << LongSubMod(a, b, c).to_hex_string() << std::endl;

    std::cout << std::endl << "Приклад множення за модулем" << std::endl;
    std::cout << LongMulMod(a, n, c).to_hex_string() << std::endl;
    
    std::cout << std::endl << "Приклад степені за модулем" << std::endl;
    std::cout << LongModPowerBarrett(a, n, c).to_hex_string() << std::endl;

    std::cout << std::endl << "Приклад a^phi(n) = 1 mod n" << std::endl;
    // phi(400) = 160 = "a0"
    std::cout << LongModPowerBarrett(d, LongNumber("a0"), n).to_hex_string() << std::endl;

    std::cout << std::endl;
    
    return 0;
}


// int main(){
//     string s_1 = "76931fac9dab2b36c248b87d6ae33f9a62d7183a5d5789e4b2d6b441e2411dc709e111c7e1e7acb6f8cac0bb2fc4c8bc2ae3";
//     string s_2 = "baaab9165cc458e199cb89f51b135f7091a5abb0874df3e8cb4543a5eb93b0441e9ca4c2b0fb3d30875cbf29abd5b1acf389";
//     string s_3 = "84b35ae882809dd4cfe7abc5c61baa52e053b4c3643f204ef259d2e98042a948aac5e884cb3ec7db925643fd34fdd467e2cc";
//     string s_4 = "a40";

//     LongNumber a(s_1), b(s_2), c(s_3), n(s_4);

//     std::cout << std::endl << "Приклад додавання та множення: (a+b)c = c(a+b) = ac+bc." << std::endl;
//     std::cout << LongMul(LongAdd(a, b), c).to_hex_string() << std::endl;
//     std::cout << LongMul(c, LongAdd(a, b)).to_hex_string() << std::endl;
//     std::cout << LongAdd(LongMul(a, c), LongMul(b, c)).to_hex_string() << std::endl;

//     std::cout << std::endl << "Ще один приклад множення: na = a + a + a + ... + a." << std::endl;
//     std::cout << LongMul(n, a).to_hex_string() << std::endl;
//     LongNumber temp("0");
//     for(LongNumber i = LongNumber(n.to_hex_string()); i.to_hex_string() != "0"; i = LongSub(i, LongNumber("1"))){
//         temp = LongAdd(temp, a);
//         temp.smolarize();
//     }
//     std::cout << temp.to_hex_string() << std::endl;

//     std::cout << std::endl << "Приклад Віднімання." << std::endl;
//     // std::cout << LongSub(a, b).to_hex_string() << std::endl;
//     std::cout << LongSub(b, a).to_hex_string() << std::endl;

//     std::cout << std::endl << "Приклад для функції ділення за модулем" << std::endl;
//     std::cout << LongDivMod(b, a).to_hex_string() << std::endl;

//     std::cout << std::endl << "Приклад для функції частки від ділення за модулем" << std::endl;
//     std::cout << LongDivFraction(b, a).to_hex_string() << std::endl;

//     std::cout << std::endl << "Приклад для функції піднесення в степінь віконним методом." << std::endl;
//     std::cout << LongPowerWindow(LongNumber("aaabc"), LongNumber("15")).to_hex_string() << std::endl;


//     return 0;
// }