#include <iostream>

#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>

using namespace std;

string get_random_hex_string(int size){
    string s = "";

    for(int i = 0; i < size; ++i){
        s += HEX[rand()%16];
    }

    return s;
}

string get_random_random_hex_string(int max_size){
    int size = rand() % max_size;
    string s = "";

    for(int i = 0; i < size; ++i){
        s += HEX[rand()%16];
    }

    return s;
}

int measure(){
    int size_of_numbers = 100;
    int numbers_vector_size = 10;
    std::vector<LongNumber> numbers;

    LongNumber n_mod(get_random_hex_string(size_of_numbers));
    LongNumber mu = CalcMu(n_mod);


    LongNumber temp("0");
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 2; ++i){
        LongModPowerBarrett(get_random_hex_string(size_of_numbers), std::string("3"), n_mod);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    
    cout << duration.count() << " microseconds, ";
    cout << (duration.count() / (numbers_vector_size*numbers_vector_size));
    cout << " microseconds per one function." << endl;

    return duration.count();
}