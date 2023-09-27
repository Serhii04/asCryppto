#include <iostream>
#include <stdexcept>
#include <string>
#include "long_number.h"
// #include "only_linux_colors.cpp"

bool test(bool rez, std::string sucsess_info, std::string fail_info){
    if(rez){
        std::cout << "GREEN" << sucsess_info << "RESET"  << std::endl;
    }else{
        std::cout << "BOLDRED" << fail_info << "RESET" << std::endl;
    }

    return rez;
}

bool test(bool rez, std::string fail_info){
    if(!rez){
        std::cout << "BOLDRED" << fail_info << "RESET" << std::endl;
    }

    return rez;
}

bool test_initiation_and_setup(){
    std::cout << "Testing initiation..." << std::endl;
    bool is_correct = true;
    
    LongNumber ln1;
    ln1 = LongNumber(3);
    is_correct = is_correct & test(
        ln1.str() == "0, 0, 0, ",
        "Must be: '0, 0, 0, ' while get: '" +  ln1.str() + "'"
    );

    ln1.set(45);
    is_correct = is_correct & test(
        ln1.str() == "45, 0, 0, ",
        "Must be: '45, 0, 0, ' while get: '" +  ln1.str() + "'"
    );

    ln1.set(4895786784);
    is_correct = is_correct & test(
        ln1.str() == "600819488, 1, 0, ",
        "Must be: '600819488, 1, 0, ' while get: '" +  ln1.str() + "'"
    );

    ln1.set(4294967295);
    is_correct = is_correct & test(
        ln1.str() == "4294967295, 0, 0, ",
        "Must be: '4294967295, 0, 0, ' while get: '" +  ln1.str() + "'"
    );

    ln1.set(4294967296);
    is_correct = is_correct & test(
        ln1.str() == "0, 1, 0, ",
        "Must be: '0, 1, 0, ' while get: '" +  ln1.str() + "'"
    );

    return is_correct;
}

bool test_get_mask_1(){
    std::cout << "Testing get_mask_1..." << std::endl;
    bool is_correct = true;
    unsigned long long a = 0;

    a = get_mask_1(0);
    is_correct = is_correct & test(
        a == 0,
        "Must be 0 while have: " + std::to_string(a)
    );

    a = get_mask_1(1);
    is_correct = is_correct & test(
        a == 1,
        "Must be 1 while have: " + std::to_string(a)
    );

    a = get_mask_1(2);
    is_correct = is_correct & test(
        a == 3,
        "Must be 3 while have: " + std::to_string(a)
    );

    a = get_mask_1(32);
    is_correct = is_correct & test(
        a == 4294967295,
        "Must be 4294967295 while have: " + std::to_string(a)
    );

    a = get_mask_1(63);
    is_correct = is_correct & test(
        a == 9223372036854775807,
        "Must be 9223372036854775807 while have: " + std::to_string(a)
    );

    a = get_mask_1(64);
    is_correct = is_correct & test(
        a == 18446744073709551615ULL,
        "Must be 18446744073709551615 while have: " + std::to_string(a)
    );

    a = get_mask_1(65);
    is_correct = is_correct & test(
        a == 18446744073709551615ULL,
        "Must be 18446744073709551615 while have: " + std::to_string(a)
    );

    a = get_mask_1(66);
    is_correct = is_correct & test(
        a == 18446744073709551615ULL,
        "Must be 18446744073709551615 while have: " + std::to_string(a)
    );
    
    return is_correct;
}

bool test_LongAdd(){
    std::cout << "Testing LongAdd..." << std::endl;
    bool is_correct = true;
    
    LongNumber ln1, ln2, ln3;

    ln3 = LongAdd(ln1, ln2);
    is_correct = is_correct & test(
        ln3.str() == "0, ",
        "Must be: '0, ' while get: '" +  ln3.str() + "'"
    );
    
    ln1.set(567);
    ln2.set(345);
    ln3 = LongAdd(ln1, ln2);
    
    is_correct = is_correct & test(
        ln3.str() == "912, ",
        "Must be: '912, ' while get: '" +  ln3.str() + "'"
    );
    
    ln1.set(4294967290);
    ln2.set(4294967290);
    ln3 = LongAdd(ln1, ln2);
    
    is_correct = is_correct & test(
        ln3.str() == "4294967284, ",
        "Must be: '4294967284, ' while get: '" +  ln3.str() + "'"
    );


    ln1 = LongNumber(3);
    ln2 = LongNumber(3);
    
    ln3 = LongAdd(ln1, ln2);
    is_correct = is_correct & test(
        ln3.str() == "0, 0, 0, ",
        "Must be: '0, 0, 0, ' while get: '" +  ln3.str() + "'"
    );
    
    ln1.set(567);
    ln2.set(345);
    ln3 = LongAdd(ln1, ln2);
    is_correct = is_correct & test(
        ln3.str() == "912, 0, 0, ",
        "Must be: '912, 0, 0, ' while get: '" +  ln3.str() + "'"
    );
    
    ln1.set(4294967290);
    ln2.set(4294967290);
    ln3 = LongAdd(ln1, ln2);
    is_correct = is_correct & test(
        ln3.str() == "4294967284, 1, 0, ",
        "Must be: '4294967284, 1, 0, ' while get: '" +  ln3.str() + "'"
    );

    std::string rez;

    ln1.set_by_hex("fca76c68fd68cabcbbbf452");
    ln2.set_by_hex("ceffdd88c4a8a289dd8899ffdd88c4a8a289de21dd8899ffdd88c4a892c4a8a289da8a27a4");
    rez = LongAdd(ln1, ln2).to_hex_string();
    is_correct &=  test(
        rez == "ceffdd88c4a8a289dd8899ffdd88c4a8a289de21dd8899ffdd988f1f59547f2f35a6461bf6",
        "Must be: 'ceffdd88c4a8a289dd8899ffdd88c4a8a289de21dd8899ffdd988f1f59547f2f35a6461bf6' while get: '" +  rez
    );

    ln1.set_by_hex("ceffdd88c4a8a289dd8899ffdd88c4a8a289de21dd8899ffdd988f1f59547f2f35a6461bf6");
    ln2.set_by_hex("ceffdd88c4a8a289dd8899ffdd88c4a8a289de21dd8899ffdd988f1f59547f2f35a6461bf6");
    rez = LongAdd(ln1, ln2).to_hex_string();
    is_correct &=  test(
        rez == "19dffbb1189514513bb1133ffbb1189514513bc43bb1133ffbb311e3eb2a8fe5e6b4c8c37ec",
        "Must be: '19dffbb1189514513bb1133ffbb1189514513bc43bb1133ffbb311e3eb2a8fe5e6b4c8c37ec' while get: '" +  rez
    );

    ln1.set_by_hex("37de4ed7a4c2135e8");
    ln2.set_by_hex("37de5bdfc572764e92d10");
    rez = LongAdd(ln1, ln2).to_hex_string();
    is_correct &=  test(
        rez == "37de93be144a1b10a62f8",
        "Must be: '37de93be144a1b10a62f8' while get: '" +  rez
    );

    ln1.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    rez = LongAdd(ln1, ln2).to_hex_string();
    is_correct &=  test(
        rez == "1ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe",
        "Must be: '1ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe' while get: '" +  rez
    );

    ln1.set_by_hex("0");
    ln2.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    rez = LongAdd(ln1, ln2).to_hex_string();
    is_correct &=  test(
        rez == "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
        "Must be: 'fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff' while get: '" +  rez
    );



    return is_correct;
}

bool test_resize(){
    std::cout << "Testing resize..." << std::endl;
    bool is_correct = true;

    LongNumber ln1;

    ln1.resize(3);
    is_correct = is_correct & test(
        ln1.str() == "0, 0, 0, ",
        "Must be: '0, 0, 0, ' while get: '" +  ln1.str() + "'"
    );

    ln1.set(4294967306);
    ln1.resize(1);
    is_correct = is_correct & test(
        ln1.str() == "10, ",
        "Must be: '10, ' while get: '" +  ln1.str() + "'"
    );

    ln1.resize(4);
    is_correct = is_correct & test(
        ln1.str() == "10, 0, 0, 0, ",
        "Must be: '10, 0, 0, 0, ' while get: '" +  ln1.str() + "'"
    );

    ln1.resize(4);
    is_correct = is_correct & test(
        ln1.str() == "10, 0, 0, 0, ",
        "Must be: '10, 0, 0, 0, ' while get: '" +  ln1.str() + "'"
    );

    return is_correct;
}

bool test_initiation_with_integer_vector(){
    std::cout << "Testing initiation with integer vector..." << std::endl;
    bool is_correct = true;
    std::vector<uint64_t> n = {};

    LongNumber ln1;

    ln1 = LongNumber(n);
    is_correct = is_correct & test(
        ln1.str() == "",
        "Must be: '' while get: '" +  ln1.str() + "'"
    );

    n = {1, 5, 74};
    ln1 = LongNumber(n);
    is_correct = is_correct & test(
        ln1.str() == "1, 5, 74, ",
        "Must be: '1, 5, 74, ' while get: '" +  ln1.str() + "'"
    );

    n = {0, 5, 74, 0, 0, 3456276, 0};
    ln1 = LongNumber(n);
    is_correct = is_correct & test(
        ln1.str() == "0, 5, 74, 0, 0, 3456276, 0, ",
        "Must be: '0, 5, 74, 0, 0, 3456276, 0, ' while get: '" +  ln1.str() + "'"
    );

    return is_correct;
}

bool test_LongSub(){
    std::cout << "Testing LongSub..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2, ln3;

    ln1.set({1, 2, 5, 6});
    ln2.set({1, 2, 5, 6});
    ln3 = LongSub(ln1, ln2);
    is_correct &= test(
        ln3.str() == "0, 0, 0, 0, ",
        "Must be: '0, 0, 0, 0, ' while get: '" +  ln3.str() + "'"
    );

    ln1.set({1, 2, 5, 6});
    ln2.set({0, 0, 0, 2});
    ln3 = LongSub(ln1, ln2);
    is_correct &= test(
        ln3.str() == "1, 2, 5, 4, ",
        "Must be: '1, 2, 5, 4, ' while get: '" +  ln3.str() + "'"
    );

    ln1.set({1, 2, 5, 6});
    ln2.set({0, 2, 0, 2});
    ln3 = LongSub(ln1, ln2);
    is_correct &= test(
        ln3.str() == "1, 0, 5, 4, ",
        "Must be: '1, 0, 5, 4, ' while get: '" +  ln3.str() + "'"
    );

    ln1.set({1, 2, 5, 6});
    ln2.set({2, 0, 0, 0});
    ln3 = LongSub(ln1, ln2);
    is_correct &= test(
        ln3.str() == "4294967295, 1, 5, 6, ",
        "Must be: '4294967295, 1, 5, 6, ' while get: '" +  ln3.str() + "'"
    );

    std::string rez = "";

    ln1.set_by_hex("9");
    ln2.set_by_hex("0");
    rez = LongSub(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "9",
        "Must be: '9' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("9");
    rez = LongSub(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffff");
    rez = LongSub(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000000",
        "Must be: 'ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff0");
    rez = LongSub(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "f",
        "Must be: 'f' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffff");
    ln2.set_by_hex("0");
    rez = LongSub(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "fffffffff",
        "Must be: 'fffffffff' while get: '" + rez + "'"
    );

    return is_correct;
}


bool test_to_hex_string(){
    std::cout << "Testing to_hex_string..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;

    ln1.set({0});
    is_correct &= test(
        ln1.to_hex_string() == "0",
        "Must be: '0' while get: '" +  ln1.to_hex_string() + "'"
    );

    ln1.set({8});
    is_correct &= test(
        ln1.to_hex_string() == "8",
        "Must be: '8' while get: '" +  ln1.to_hex_string() + "'"
    );

    ln1.set({14});
    is_correct &= test(
        ln1.to_hex_string() == "e",
        "Must be: 'e' while get: '" +  ln1.to_hex_string() + "'"
    );

    ln1.set({15});
    is_correct &= test(
        ln1.to_hex_string() == "f",
        "Must be: 'f' while get: '" +  ln1.to_hex_string() + "'"
    );

    ln1.set({25});
    is_correct &= test(
        ln1.to_hex_string() == "19",
        "Must be: '19' while get: '" +  ln1.to_hex_string() + "'"
    );

    ln1.set({255});
    is_correct &= test(
        ln1.to_hex_string() == "ff",
        "Must be: 'ff' while get: '" +  ln1.to_hex_string() + "'"
    );

    ln1.set({4294967295});
    is_correct &= test(
        ln1.to_hex_string() == "ffffffff",
        "Must be: 'ffffffff' while get: '" +  ln1.to_hex_string() + "'"
    );
    
    ln1.set({4294967295,4294967295});
    is_correct &= test(
        ln1.to_hex_string() == "ffffffffffffffff",
        "Must be: 'ffffffffffffffff' while get: '" +  ln1.to_hex_string() + "'"
    );

    return is_correct;
}

bool test_hex_to_uint64_t(){
    std::cout << "Testing hex_to_uint64_t..." << std::endl;
    bool is_correct = true;
    uint16_t rez = 0;
    
    rez = hex_to_uint64_t("0"); 
    is_correct &= test(
        rez == 0,
        "Must be: 0 while get: " + rez
    );

    rez = hex_to_uint64_t("4"); 
    is_correct &= test(
        rez == 4,
        "Must be: 4 while get: " + rez
    );

    rez = hex_to_uint64_t("f"); 
    is_correct &= test(
        rez == 15,
        "Must be: 15 while get: " + rez
    );


    return is_correct;
}


bool test_set_by_hex(){
    std::cout << "Testing set_by_hex..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    std::string rez = "";
    
    ln1.set_by_hex("0");
    rez = ln1.str(); 
    is_correct &= test(
        rez == "0, ",
        "Must be: '0, ' while get: '" + rez + "'"
    );

    ln1.set_by_hex("5");
    rez = ln1.str(); 
    is_correct &= test(
        rez == "5, ",
        "Must be: '5, ' while get: " + rez + "'"
    );

    ln1.set_by_hex("e");
    rez = ln1.str(); 
    is_correct &= test(
        rez == "14, ",
        "Must be: '14, ' while get: " + rez + "'"
    );

    ln1.set_by_hex("f");
    rez = ln1.str(); 
    is_correct &= test(
        rez == "15, ",
        "Must be: '15, ' while get: " + rez + "'"
    );

    ln1.set_by_hex("ff");
    rez = ln1.str(); 
    is_correct &= test(
        rez == "255, ",
        "Must be: '255, ' while get: " + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    rez = ln1.str(); 
    is_correct &= test(
        rez == "4294967295, ",
        "Must be: '4294967295, ' while get: " + rez + "'"
    );

    ln1.set_by_hex("fffffffff");
    rez = ln1.str(); 
    is_correct &= test(
        rez == "4294967295, 15, ",
        "Must be: '4294967295, 15, ' while get: " + rez + "'"
    );

    return is_correct;
}

bool test_hex_size_to_64(){
    std::cout << "Testing hex_size_to_64..." << std::endl;
    bool is_correct = true;
    int rez = 0;

    rez = hex_size_to_64("");
    is_correct &= test(
        rez == 0,
        "Must be: 0 while get: " + std::to_string(rez)
    );

    rez = hex_size_to_64("f");
    is_correct &= test(
        rez == 1,
        "Must be: 1 while get: " + std::to_string(rez)
    );
    
    rez = hex_size_to_64("fffffff");
    is_correct &= test(
        rez == 1,
        "Must be: 1 while get: " + std::to_string(rez)
    );

    rez = hex_size_to_64("ffffffff");
    is_correct &= test(
        rez == 1,
        "Must be: 1 while get: " + std::to_string(rez)
    );

    rez = hex_size_to_64("fffffffff");
    is_correct &= test(
        rez == 2,
        "Must be: 2 while get: " + std::to_string(rez)
    );
    
    rez = hex_size_to_64("fffffffffff");
    is_correct &= test(
        rez == 2,
        "Must be: 2 while get: " + std::to_string(rez)
    );

    return is_correct;
}



bool test_to_8_div_lenght(){
    std::cout << "Testing to_8_div_lenght..." << std::endl;
    bool is_correct = true;
    std::string rez = "";

    rez = to_8_div_lenght("ffff");
    is_correct &= test(
        rez == "0000ffff",
        "Must be: '0000ffff' while get: " + rez
    );

    rez = to_8_div_lenght("");
    is_correct &= test(
        rez == "",
        "Must be: '' while get: " + rez
    );

    rez = to_8_div_lenght("ffffffff");
    is_correct &= test(
        rez == "ffffffff",
        "Must be: 'ffffffff' while get: " + rez
    );

    rez = to_8_div_lenght("eeeeeeeeffffffff");
    is_correct &= test(
        rez == "eeeeeeeeffffffff",
        "Must be: 'eeeeeeeeffffffff' while get: " + rez
    );

    rez = to_8_div_lenght("22eeeeeeeeffffffff");
    is_correct &= test(
        rez == "00000022eeeeeeeeffffffff",
        "Must be: '00000022eeeeeeeeffffffff' while get: " + rez
    );

    

    return is_correct;
}

bool test_get_number_at_8_hex(){
    std::cout << "Testing get_number_at_8_hex..." << std::endl;
    bool is_correct = true;
    uint64_t rez = 0;

    rez = get_number_at_8_hex("0000000f");
    is_correct &= test(
        rez == 15,
        "Must be: 15 while get: " + std::to_string(rez)
    );

    rez = get_number_at_8_hex("00000003");
    is_correct &= test(
        rez == 3,
        "Must be: 3 while get: " + std::to_string(rez)
    );

    rez = get_number_at_8_hex("00000000");
    is_correct &= test(
        rez == 0,
        "Must be: 0 while get: " + std::to_string(rez)
    );

    rez = get_number_at_8_hex("000000cb");
    is_correct &= test(
        rez == 203,
        "Must be: 203 while get: " + std::to_string(rez)
    );

    rez = get_number_at_8_hex("345feacb");
    is_correct &= test(
        rez == 878701259,
        "Must be: 878701259 while get: " + std::to_string(rez)
    );

    rez = get_number_at_8_hex("ffffffff");
    is_correct &= test(
        rez == 4294967295,
        "Must be: 4294967295 while get: " + std::to_string(rez)
    );


    return is_correct;
}

bool test_set_by_hex_get_by_hex(){
    std::cout << "Testing set_by_hex and then _get_by_hex..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    std::string rez = "";
    
    ln1.set_by_hex("0");
    rez = ln1.to_hex_string(); 
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("f673eca");
    rez = ln1.to_hex_string(); 
    is_correct &= test(
        rez == "f673eca",
        "Must be: 'f673eca' while get: '" + rez + "'"
    );

    ln1.set_by_hex("f657843987427872938472837512374817234981732873eca");
    rez = ln1.to_hex_string(); 
    is_correct &= test(
        rez == "f657843987427872938472837512374817234981732873eca",
        "Must be: 'f657843987427872938472837512374817234981732873eca' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
        "Must be: 'ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LongMulOneDigit(){
    std::cout << "Testing LongMulOneDigit..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    std::string rez = "";
    
    ln1.set_by_hex("ffad35faa345c");
    ln1 = LongMulOneDigit(ln1, 5);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "4fe620de5305cc",
        "U1, Must be: '4fe620de5305cc' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffad35faa345c");
    ln1 = LongMulOneDigit(ln1, 34574);  // 34574 = 0x870E
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "86e252f01fceb6108",
        "U2, Must be: '86e252f01fceb6108' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffad35faa345c");
    ln1 = LongMulOneDigit(ln1, 0);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "0",
        "U3, Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("cfcfad35faa345cfad35faa345c");
    ln1 = LongMulOneDigit(ln1, 255);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "ceffdd88c4a8a289dd88c4a8a27a4",
        "U4, Must be: 'ceffdd88c4a8a289dd88c4a8a27a4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("cfcfad35faa345cfad35cfcfad35faa345cfadcfad35cfcfad35faa335faa345cfaa345c");
    ln1 = LongMulOneDigit(ln1, 255);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "ceffdd88c4a8a289dd8899ffdd88c4a8a289de21dd8899ffdd88c4a892c4a8a289da8a27a4",
        "U5, Must be: 'ceffdd88c4a8a289dd8899ffdd88c4a8a289de21dd8899ffdd88c4a892c4a8a289da8a27a4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("cfcfad35faa345cfad35cfcfad35faa345cfadcfad35cfcfad35faa335faa345cfaa345c");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "cfcfad352ad39899b2928a0000002ad39899b32c6766220000002ad388c4a8a299af91163055cba4",
        "U6, Must be: 'cfcfad352ad39899b2928a0000002ad39899b32c6766220000002ad388c4a8a299af91163055cba4' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("ffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 15);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "efffffffffffffffffffffffffffffff1",
        "U7, Must be: 'efffffffffffffffffffffffffffffff1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 15);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "effffffffffffffffffffffffffffffff1",
        "U8, Must be: 'effffffffffffffffffffffffffffffff1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967294);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffd00000002",
        "U9, Must be: 'fffffffd00000002' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffe00000001",
        "U10, Must be: 'fffffffe00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffef00000001",
        "U11, Must be: 'fffffffef00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffeffffffff00000001",
        "U12, Must be: 'fffffffeffffffff00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffeffffffffffffffffffffffff00000001",
        "U12, Must be: 'fffffffeffffffffffffffffffffffff00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001",
        "U12, Must be: 'fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001",
        "U11, Must be: 'fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001",
        "U11, Must be: 'fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001",
        "U11, Must be: 'fffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 4294967295);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffefffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001",
        "U11, Must be: 'fffffffefffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 0);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "0",
        "U11, Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln1 = LongMulOneDigit(ln1, 1);
    rez = ln1.to_hex_string();
    is_correct &= test(
        rez == "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
        "U11, Must be: 'fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff' while get: '" + rez + "'"
    );

    return is_correct;
}


bool test_LongCmp(){
    std::cout << "Testing LongCmp..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    int rez = 0;
    
    ln1.set_by_hex("ffad35faa345c");
    ln2.set_by_hex("ffad35faa3453");
    rez = LongCmp(ln1, ln2);
    is_correct &= test(
        rez == 1,
        "Must be: 1 while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("ffad35faa3453");
    ln2.set_by_hex("ffad35faa3453");
    rez = LongCmp(ln1, ln2);
    is_correct &= test(
        rez == 0,
        "Must be: 0 while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("ffad35faa3453");
    ln2.set_by_hex("ffad35faa345c");
    rez = LongCmp(ln1, ln2);
    is_correct &= test(
        rez == -1,
        "Must be: -1 while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("fffad35faa3453");
    ln2.set_by_hex("ffad35faa345c");
    rez = LongCmp(ln1, ln2);
    is_correct &= test(
        rez == 1,
        "Must be: 1 while get: '" + std::to_string(rez)
    );


    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffff");
    rez = LongCmp(ln1, ln2);
    is_correct &= test(
        rez == 1,
        "Must be: 1 while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("fffffffff");
    ln2.set_by_hex("cccccccc1");
    rez = LongCmp(ln1, ln2);
    is_correct &= test(
        rez == 1,
        "Must be: 1 while get: '" + std::to_string(rez)
    );

    return is_correct;
}

bool test_LongLeftShift(){
    std::cout << "Testing LongLeftShift..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    std::string rez = "";
    
    ln1.set_by_hex("ffad35faa345c");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "1ff5a6bf5468b8",
        "Must be: '1ff5a6bf5468b8' while get: '" + rez + "'"
    );

    ln1.set_by_hex("0");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "2",
        "Must be: '2' while get: '" + rez + "'"
    );

    ln1.set_by_hex("2");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("100000000");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "200000000",
        "Must be: '200000000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("10000000000");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "20000000000",
        "Must be: '20000000000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("11111111111");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "22222222222",
        "Must be: '22222222222' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1ff5a6bf5468b");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "3feb4d7ea8d16",
        "Must be: '3feb4d7ea8d16' while get: '" + rez + "'"
    );

    ln1.set_by_hex("3feb4d7ea8d16");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "7fd69afd51a2c",
        "Must be: '7fd69afd51a2c' while get: '" + rez + "'"
    );

    ln1.set_by_hex("11111111111111111111111111111111111111111111111111111111111111111111111111111111");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "22222222222222222222222222222222222222222222222222222222222222222222222222222222",
        "Must be: '22222222222222222222222222222222222222222222222222222222222222222222222222222222' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fa8241fab45782400");
    rez = LongLeftShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "1f50483f568af04800",
        "Must be: '1f50483f568af04800' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LongShiftDigitsToHigh(){
    std::cout << "Testing LongShiftDigitsToHigh..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    std::string rez = "";

    ln1.set_by_hex("ffad35faa345c");
    rez = LongShiftDigitsToHigh(ln1, 0).to_hex_string();
    is_correct &= test(
        rez == "ffad35faa345c",
        "Must be: 'ffad35faa345c' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("ffad35faa345c");
    rez = LongShiftDigitsToHigh(ln1, 1).to_hex_string();
    is_correct &= test(
        rez == "1ff5a6bf5468b8",
        "Must be: '1ff5a6bf5468b8' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1ff5a6bf5468b");
    rez = LongShiftDigitsToHigh(ln1, 2).to_hex_string();
    is_correct &= test(
        rez == "7fd69afd51a2c",
        "Must be: '7fd69afd51a2c' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1ff5a6bf5468b");
    rez = LongShiftDigitsToHigh(ln1, 5).to_hex_string();
    is_correct &= test(
        rez == "3feb4d7ea8d160",
        "Must be: '3feb4d7ea8d160' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("1");
    rez = LongShiftDigitsToHigh(ln1, 32).to_hex_string();
    is_correct &= test(
        rez == "100000000",
        "Must be: '100000000' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LongShiftDigitsToHigh_expandable(){
    std::cout << "Testing LongShiftDigitsToHigh_expandable..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    std::string rez = "";

    ln1.set_by_hex("ffad35faa345c");
    rez = LongShiftDigitsToHigh_expandable(ln1, 0).to_hex_string();
    is_correct &= test(
        rez == "ffad35faa345c",
        "Must be: 'ffad35faa345c' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("ffad35faa345c");
    rez = LongShiftDigitsToHigh_expandable(ln1, 1).to_hex_string();
    is_correct &= test(
        rez == "1ff5a6bf5468b8",
        "Must be: '1ff5a6bf5468b8' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1ff5a6bf5468b");
    rez = LongShiftDigitsToHigh_expandable(ln1, 2).to_hex_string();
    is_correct &= test(
        rez == "7fd69afd51a2c",
        "Must be: '7fd69afd51a2c' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1ff5a6bf5468b");
    rez = LongShiftDigitsToHigh_expandable(ln1, 5).to_hex_string();
    is_correct &= test(
        rez == "3feb4d7ea8d160",
        "Must be: '3feb4d7ea8d160' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("1");
    rez = LongShiftDigitsToHigh_expandable(ln1, 32).to_hex_string();
    is_correct &= test(
        rez == "100000000",
        "Must be: '100000000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    rez = LongShiftDigitsToHigh_expandable(ln1, 32).to_hex_string();
    is_correct &= test(
        rez == "ffffffff00000000",
        "Must be: 'ffffffff00000000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    rez = LongShiftDigitsToHigh_expandable(ln1, 31).to_hex_string();
    is_correct &= test(
        rez == "7fffffff80000000",
        "Must be: '7fffffff80000000' while get: '" + rez + "'"
    );

    return is_correct;
}


bool test_LongMul(){
    std::cout << "Testing LongMul..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("2");
    ln2.set_by_hex("2");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("2");
    ln2.set_by_hex("0");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("0");
    ln2.set_by_hex("4");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("f");
    ln2.set_by_hex("f");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "e1",
        "Must be: 'e1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("f34c");
    ln2.set_by_hex("f");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "e4174",
        "Must be: 'e4174' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fc5638adc");
    ln2.set_by_hex("fc563adc");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "f8b9dec6764e92d10",
        "Must be: 'f8b9dec6764e92d10' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffad35fa");
    ln2.set_by_hex("ffad35fa");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "ff5a86ba0b457824",
        "Must be: 'ff5a86ba0b457824' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffad35fa0");
    ln2.set_by_hex("ffad35fa0");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "ff5a86ba0b45782400",
        "Must be: 'ff5a86ba0b45782400' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adfc5638adc");
    ln2.set_by_hex("fc56fc563adc");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "37de86b600a1d8d0f64e92d10",
        "Must be: '37de86b600a1d8d0f64e92d10' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("ffad35faa345c");
    ln2.set_by_hex("ffad35faa345c");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "ff5a86bb51675dc3addce58110",
        "Must be: 'ff5a86bb51675dc3addce58110' while get: '" + rez + "'"
    );

    ln1.set_by_hex("f");
    ln2.set_by_hex("f");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "e1",
        "Must be: 'e1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    ln2.set_by_hex("ffffffff");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "fffffffe00000001",
        "Must be: 'fffffffe00000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffff");
    ln2.set_by_hex("ffffffffffffffff");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "fffffffffffffffe0000000000000001",
        "Must be: 'fffffffffffffffe0000000000000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffffffffffffffffffff");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "fffffffffffffffffffffffe000000000000000000000001",
        "Must be: 'fffffffffffffffffffffffe000000000000000000000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffffffffffffffffffffffffffff");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "fffffffffffffffffffffffffffffffe00000000000000000000000000000001",
        "Must be: 'fffffffffffffffffffffffffffffffe00000000000000000000000000000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("51");
    ln2.set_by_hex("51");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "19a1",
        "Must be: '19a1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &=  test(
        rez == "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
        "Must be: 'fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001' while get: '" +  rez
    );

    ln1.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    rez = LongMul(ln1, ln2).to_hex_string();
    is_correct &=  test(
        rez == "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
        "Must be: 'ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001' while get: '" +  rez
    );

    return is_correct;
}

bool test_LongDivMod(){
    std::cout << "Testing LongDivMod..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("2");
    ln2.set_by_hex("2");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adfc5638adc");
    ln2.set_by_hex("fc56fc563adc");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "3",
        "Must be: '3' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    ln2.set_by_hex("ffff");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "10001",
        "Must be: '10001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffff");
    ln2.set_by_hex("ffff");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "100010",
        "Must be: '100010' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffff");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1000000010000000100000001",
        "Must be: '1000000010000000100000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffff");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001",
        "Must be: '1000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001000000010000000100000001' while get: '" + rez + "'"
    );

    ln1.set_by_hex("18327612360132492813412834612983761298374623741023874621378461872346f127834612f38746f3287c6148273c641c87236f178c2638c7f14623cf87416c2");
    ln2.set_by_hex("345fcaae1de0f5f2faaaaa43cd3c4c34fc3458374623741023adfcbcfda87462137fccaddac34215235345f345ccdfc34acd5fc345fc334645fccdafc345fc");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "7645eea",
        "Must be: '7645eea' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    ln2.set_by_hex("ffffffffffffffffffffffffffffffffffffffffffffffff");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "10000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000",
        "Must be: '10000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010000000000000000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adfc5638adc");
    ln2.set_by_hex("0");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("cccccccc1");
    ln2.set_by_hex("222");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "6006005",
        "Must be: '6006005' while get: '" + rez + "'"
    );

    ln1.set_by_hex("cccccccc1");
    ln2.set_by_hex("2");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "666666660",
        "Must be: '666666660' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("cccccccc1");
    ln2.set_by_hex("1");
    rez = LongDivMod(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "cccccccc1",
        "Must be: 'cccccccc1' while get: '" + rez + "'"
    );

    return is_correct;
}


bool test_LongDivFraction(){
    std::cout << "Testing LongDivFraction..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("3");
    ln2.set_by_hex("2");
    rez = LongDivFraction(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adfc5638adc");
    ln2.set_by_hex("fc56fc563adc");
    rez = LongDivFraction(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "95dad060da48",
        "Must be: '95dad060da48' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LongPower1(){
    std::cout << "Testing LongPower1..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("3");
    ln2.set_by_hex("2");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "9",
        "Must be: '9' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1");
    ln2.set_by_hex("1");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("0");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("6");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "81bf1",
        "Must be: '81bf1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("2");
    ln2.set_by_hex("f");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "8000",
        "Must be: '8000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adf");
    ln2.set_by_hex("f");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "a592261b63e41518d995e1e14d21956f5831ac1947d030aa2573e38d281a05bbf1f",
        "Must be: 'a592261b63e41518d995e1e14d21956f5831ac1947d030aa2573e38d281a05bbf1f' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adfc5638adc");
    ln2.set_by_hex("f");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "a59442b0a308403d62d8e5ea644191ccbb021e933867c0cd0ed5f80727b19b3e616a5d375f968e981740988bce00692f7390a930c9c0c304397a7e4285facb5a12a1cb5acfcccb09f5831e658946fd04de4ddd1f30754f6af21c0000000",
        "Must be: 'a59442b0a308403d62d8e5ea644191ccbb021e933867c0cd0ed5f80727b19b3e616a5d375f968e981740988bce00692f7390a930c9c0c304397a7e4285facb5a12a1cb5acfcccb09f5831e658946fd04de4ddd1f30754f6af21c0000000' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LongPower2(){
    std::cout << "Testing LongPower2..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("3");
    ln2.set_by_hex("2");
    rez = LongPower2(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "9",
        "Must be: '9' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1");
    ln2.set_by_hex("1");
    rez = LongPower2(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("0");
    rez = LongPower2(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("6");
    rez = LongPower2(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "81bf1",
        "Must be: '81bf1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("2");
    ln2.set_by_hex("f");
    rez = LongPower2(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "8000",
        "Must be: '8000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adf");
    ln2.set_by_hex("f");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "a592261b63e41518d995e1e14d21956f5831ac1947d030aa2573e38d281a05bbf1f",
        "Must be: 'a592261b63e41518d995e1e14d21956f5831ac1947d030aa2573e38d281a05bbf1f' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adfc5638adc");
    ln2.set_by_hex("f");
    rez = LongPower1(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "a59442b0a308403d62d8e5ea644191ccbb021e933867c0cd0ed5f80727b19b3e616a5d375f968e981740988bce00692f7390a930c9c0c304397a7e4285facb5a12a1cb5acfcccb09f5831e658946fd04de4ddd1f30754f6af21c0000000",
        "Must be: 'a59442b0a308403d62d8e5ea644191ccbb021e933867c0cd0ed5f80727b19b3e616a5d375f968e981740988bce00692f7390a930c9c0c304397a7e4285facb5a12a1cb5acfcccb09f5831e658946fd04de4ddd1f30754f6af21c0000000' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_get_2_in_power_n(){
    std::cout << "Testing get_2_in_power_n..." << std::endl;
    bool is_correct = true;
    std::string rez = "";

    rez = get_2_in_power_n(32).to_hex_string();
    is_correct &= test(
        rez == "100000000",
        "Must be: '100000000' while get: '" + rez + "'"
    );

    rez = get_2_in_power_n(0).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    rez = get_2_in_power_n(1).to_hex_string();
    is_correct &= test(
        rez == "2",
        "Must be: '2' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_higest_bit_id(){
    std::cout << "Testing higest_bit_id..." << std::endl;
    bool is_correct = true;
    int rez = 0;
    LongNumber ln1;

    ln1.set_by_hex("0");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == -1,
        "Must be: '-1' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("1");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("2");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("3");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("ff");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 7,
        "Must be: '7' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("ff34245");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 27,
        "Must be: '27' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("ff3424544444444");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 59,
        "Must be: '59' while get: '" + std::to_string(rez)
    );

    return is_correct;
}

bool test_smolarize(){
    std::cout << "Testing smolarize..." << std::endl;
    bool is_correct = true;
    int rez = 0;
    LongNumber ln1;

    ln1.set_by_hex("3");
    ln1.resize(32);
    ln1.smolarize();
    rez = ln1.size();
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("1");
    ln1.resize(64);
    ln1.smolarize();
    rez = ln1.size();
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("fffffffff3");
    ln1.resize(32);
    ln1.smolarize();
    rez = ln1.size();
    is_correct &= test(
        rez == 2,
        "Must be: '2' while get: '" + std::to_string(rez)
    );


    ln1.set_by_hex("ff");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 7,
        "Must be: '7' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("ff34245");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 27,
        "Must be: '27' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("ff3424544444444");
    rez = ln1.higest_bit_id();
    is_correct &= test(
        rez == 59,
        "Must be: '59' while get: '" + std::to_string(rez)
    );

    return is_correct;
}

bool test_LongPowerWindow(){
    std::cout << "Testing LongPowerWindow..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("3");
    ln2.set_by_hex("2");
    rez = LongPowerWindow(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "9",
        "Must be: '9' while get: '" + rez + "'"
    );

    ln1.set_by_hex("1");
    ln2.set_by_hex("1");
    rez = LongPowerWindow(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("0");
    rez = LongPowerWindow(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("6");
    rez = LongPowerWindow(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "81bf1",
        "Must be: '81bf1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("2");
    ln2.set_by_hex("f");
    rez = LongPowerWindow(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "8000",
        "Must be: '8000' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adf");
    ln2.set_by_hex("f");
    rez = LongPowerWindow(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "a592261b63e41518d995e1e14d21956f5831ac1947d030aa2573e38d281a05bbf1f",
        "Must be: 'a592261b63e41518d995e1e14d21956f5831ac1947d030aa2573e38d281a05bbf1f' while get: '" + rez + "'"
    );

    ln1.set_by_hex("38adfc5638adc");
    ln2.set_by_hex("f");
    rez = LongPowerWindow(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "a59442b0a308403d62d8e5ea644191ccbb021e933867c0cd0ed5f80727b19b3e616a5d375f968e981740988bce00692f7390a930c9c0c304397a7e4285facb5a12a1cb5acfcccb09f5831e658946fd04de4ddd1f30754f6af21c0000000",
        "Must be: 'a59442b0a308403d62d8e5ea644191ccbb021e933867c0cd0ed5f80727b19b3e616a5d375f968e981740988bce00692f7390a930c9c0c304397a7e4285facb5a12a1cb5acfcccb09f5831e658946fd04de4ddd1f30754f6af21c0000000' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LongSquare(){
    std::cout << "Testing LongSquare..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("1");
    rez = LongSquare(ln1).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("9");
    rez = LongSquare(ln1).to_hex_string();
    is_correct &= test(
        rez == "51",
        "Must be: '51' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("935cde378f34c87ad");
    rez = LongSquare(ln1).to_hex_string();
    is_correct &= test(
        rez == "54d3c8e44749f49b87a4a860a3449feae9",
        "Must be: '54d3c8e44749f49b87a4a860a3449feae9' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_Longnumber__lovest_bit(){
    std::cout << "Testing lovest_bit..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    int rez = 0;

    ln1.set_by_hex("1");
    rez = ln1.lovest_bit();
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez)
    );
    
    ln1.set_by_hex("4");
    rez = ln1.lovest_bit();
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("23467461169234519512304c62474");
    rez = ln1.lovest_bit();
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez)
    );

    ln1.set_by_hex("cadfcdfcbcdabdacbd89c7ad9767ac57dac2a4c87a69c73");
    rez = ln1.lovest_bit();
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez)
    );

    return is_correct;
}

bool test_LongRightShift(){
    std::cout << "Testing LongRightShift..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    std::string rez = "";

    ln1.set_by_hex("1");
    rez = LongRightShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );
    
    ln1.set_by_hex("0");
    rez = LongRightShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "0",
        "Must be: '0' while get: '" + rez + "'"
    );

    ln1.set_by_hex("2");
    rez = LongRightShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("729a76a9692a52d");
    rez = LongRightShift(ln1).to_hex_string();
    is_correct &= test(
        rez == "394d3b54b495296",
        "Must be: '394d3b54b495296' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LongMin(){
    std::cout << "Testing LongMin..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("1");
    ln2.set_by_hex("4");
    rez = LongMin(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("4");
    ln2.set_by_hex("4");
    rez = LongMin(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("7923460149827461827340");
    ln2.set_by_hex("4");
    rez = LongMin(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("218764198263948176234786");
    ln2.set_by_hex("89702983749123417203");
    rez = LongMin(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "89702983749123417203",
        "Must be: '89702983749123417203' while get: '" + rez + "'"
    );

    ln1.set_by_hex("218764198263948176234786");
    ln2.set_by_hex("8970277879812793871928739873791827983749123417203");
    rez = LongMin(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "218764198263948176234786",
        "Must be: '218764198263948176234786' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_EuclidsBinaryAlgorithm(){
    std::cout << "Testing EuclidsBinaryAlgorithm..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("1");
    ln2.set_by_hex("4");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("4");
    ln2.set_by_hex("4");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("9");
    ln2.set_by_hex("15");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "3",
        "Must be: '3' while get: '" + rez + "'"
    );

    ln1.set_by_hex("77fc89f2f06c1bc98f0d86eb367c5e63c4cb5daca8f89ad4bbca5a6b012fcf11b9629753dd51e6b4a51ffafa90e22db49b29498c289db1d499");
    ln2.set_by_hex("782364178624234976194612394612836412351746917846912384623423");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "782364178624234976194612394612836412351746917846912384623423",
        "Must be: '782364178624234976194612394612836412351746917846912384623423' while get: '" + rez + "'"
    );

    ln1.set_by_hex("77fc89f2f06c1bc98f0d86eb367c5e63c4cb5daca8f89ad4bbca5a6b012fcf11b9629753dd51e6b4a51ffafa90e22db49b29498c289db1d499");
    ln2.set_by_hex("7823641786242d45334976194612394612836412351746917846912384623423");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("39e81cb93ca8");
    ln2.set_by_hex("1e89f9155d2bda");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "434da",
        "Must be: '434da' while get: '" + rez + "'"
    );

    ln1.set_by_hex("ffffffff");
    ln2.set_by_hex("cccccccc");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "33333333",
        "Must be: '33333333' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffff");
    ln2.set_by_hex("ccccccccc");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "333333333",
        "Must be: '333333333' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffff");
    ln2.set_by_hex("cccccccc1");
    rez = EuclidsBinaryAlgorithm(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_LCM(){
    std::cout << "Testing LCM..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("1");
    ln2.set_by_hex("4");
    rez = LCM(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("4");
    ln2.set_by_hex("4");
    rez = LCM(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("4");
    ln2.set_by_hex("1");
    rez = LCM(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "4",
        "Must be: '4' while get: '" + rez + "'"
    );

    ln1.set_by_hex("fffffffff");
    ln2.set_by_hex("cccccccc1");
    rez = LCM(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "cccccccc033333333f",
        "Must be: 'cccccccc033333333f' while get: '" + rez + "'"
    );

    return is_correct;
}

bool test_BarrettReduction(){
    std::cout << "Testing BarrettReduction..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2;
    std::string rez = "";

    ln1.set_by_hex("3");
    ln2.set_by_hex("4");
    rez = BarrettReduction(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "3",
        "Must be: '3' while get: '" + rez + "'"
    );

    ln1.set_by_hex("3");
    ln2.set_by_hex("5541");
    rez = BarrettReduction(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "3",
        "Must be: '3' while get: '" + rez + "'"
    );

    ln1.set_by_hex("4");
    ln2.set_by_hex("3");
    rez = BarrettReduction(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("cccccccc1");
    ln2.set_by_hex("222");
    rez = BarrettReduction(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "217",
        "Must be: '217' while get: '" + rez + "'"
    );

    ln1.set_by_hex("cc794823cc79482371049823741876508293147cccccc1710498237cc79482371049823741876508293147cccccc141876508293147cccccc1");
    ln2.set_by_hex("2272389146878236597263956243872651987324628756358743698726987346926349716487662");
    rez = BarrettReduction(ln1, ln2).to_hex_string();
    is_correct &= test(
        rez == "1c14fdee09dd00c1376d66920cad9bd6e140d3807e7c955925dfea999cb7c29f55d68aa5a16625d",
        "Must be: '1c14fdee09dd00c1376d66920cad9bd6e140d3807e7c955925dfea999cb7c29f55d68aa5a16625d' while get: '" + rez + "'"
    );

    return is_correct;
}


bool test_at_bit(){
    std::cout << "Testing LongNumber.at_bit()..." << std::endl;
    bool is_correct = true;
    LongNumber ln1;
    int rez = 0;

    ln1.set_by_hex("3");
    rez = ln1.at_bit(-2);
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("3");
    rez = ln1.at_bit(-1);
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("3");
    rez = ln1.at_bit(0);
    is_correct &= test(
        rez == 1,
        "Must be: '0' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("4");
    rez = ln1.at_bit(0);
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("4");
    rez = ln1.at_bit(2);
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("4");
    rez = ln1.at_bit(7);
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("4");
    rez = ln1.at_bit(12);
    is_correct &= test(
        rez == 0,
        "Must be: '0' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("fffffffffffffffffffffffff");
    rez = ln1.at_bit(12);
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez) + "'"
    );

    ln1.set_by_hex("fffffffffffffffffffffffff");
    rez = ln1.at_bit(70);
    is_correct &= test(
        rez == 1,
        "Must be: '1' while get: '" + std::to_string(rez) + "'"
    );

    return is_correct;
}

bool test_LongModPowerBarrett(){
    std::cout << "Testing LongModPowerBarrett..." << std::endl;
    bool is_correct = true;
    LongNumber ln1, ln2, lnn;
    std::string rez = "";

    ln1.set_by_hex("2");
    ln2.set_by_hex("4");
    lnn.set_by_hex("3");
    rez = LongModPowerBarrett(ln1, ln2, lnn).to_hex_string();
    is_correct &= test(
        rez == "1",
        "Must be: '1' while get: '" + rez + "'"
    );

    ln1.set_by_hex("456745");
    ln2.set_by_hex("7");
    lnn.set_by_hex("567843548659570806785863653");
    rez = LongModPowerBarrett(ln1, ln2, lnn).to_hex_string();
    is_correct &= test(
        rez == "3777f0df8755bbb6d3784556278",
        "Must be: '3777f0df8755bbb6d3784556278' while get: '" + rez + "'"
    );

    ln1.set_by_hex("456745345");
    ln2.set_by_hex("45");
    lnn.set_by_hex("567843548659570806785863653");
    rez = LongModPowerBarrett(ln1, ln2, lnn).to_hex_string();
    is_correct &= test(
        rez == "2f6e0d732d96887e6529a06814c",
        "Must be: '2f6e0d732d96887e6529a06814c' while get: '" + rez + "'"
    );

    return is_correct;
}

void test_all(){
    std::cout << "Testing started..." << std::endl;
    bool all_is_passed = true;
    
    // all_is_passed &= test(test_initiation_and_setup(), "Initialisation is OK", "Initialisation is failed");
    // all_is_passed &= test(test_get_mask_1(), "get_mask_1 is OK", "get_mask_1 is failed");
    // all_is_passed &= test(test_resize(), "resize is OK", "resize is failed");
    // all_is_passed &= test(test_LongAdd(), "LongAdd is OK", "LongAdd is failed");
    // all_is_passed &= test(test_initiation_with_integer_vector(), "Initialisation with integer vector is OK", "Initialisation with integer vector is failed");
    // all_is_passed &= test(test_LongSub(), "LongSub is OK", "LongSub is failed");
    // all_is_passed &= test(test_to_hex_string(), "to_hex_string is OK", "to_hex_string is failed");
    // all_is_passed &= test(test_hex_to_uint64_t(), "hex_to_uint64_t is OK", "hex_to_uint64_t is failed");
    // all_is_passed &= test(test_hex_size_to_64(), "hex_size_to_64 is OK", "hex_size_to_64 is failed");
    // all_is_passed &= test(test_to_8_div_lenght(), "to_8_div_lenght is OK", "to_8_div_lenght is failed");
    // all_is_passed &= test(test_get_number_at_8_hex(), "get_number_at_8_hex is OK", "get_number_at_8_hex is failed");
    // all_is_passed &= test(test_set_by_hex(), "set_by_hex is OK", "set_by_hex is failed");
    // all_is_passed &= test(test_set_by_hex_get_by_hex(), "set_by_hex_get_by_hex is OK", "set_by_hex_get_by_hex is failed");
    // all_is_passed &= test(test_LongMulOneDigit(), "LongMulOneDigit is OK", "LongMulOneDigit is failed");
    // all_is_passed &= test(test_LongCmp(), "LongCmp is OK", "LongCmp is failed");
    // all_is_passed &= test(test_get_2_in_power_n(), "get_2_in_power_n is OK", "get_2_in_power_n is failed");
    // all_is_passed &= test(test_LongLeftShift(), "LongLeftShift is OK", "LongLeftShift is failed");
    // all_is_passed &= test(test_higest_bit_id(), "higest_bit_id is OK", "higest_bit_id is failed");
    // all_is_passed &= test(test_LongShiftDigitsToHigh(), "LongShiftDigitsToHigh is OK", "LongShiftDigitsToHigh is failed");
    // all_is_passed &= test(test_LongShiftDigitsToHigh_expandable(), "LongShiftDigitsToHigh_expandable is OK", "LongShiftDigitsToHigh_expandable is failed");
    // all_is_passed &= test(test_LongMul(), "LongMul is OK", "LongMul is failed");
    // all_is_passed &= test(test_LongDivMod(), "LongDivMod is OK", "LongDivMod is failed");
    // all_is_passed &= test(test_LongDivFraction(), "LongDivFraction is OK", "LongDivFraction is failed");
    // all_is_passed &= test(test_smolarize(), "smolarize is OK", "smolarize is failed");
    // all_is_passed &= test(test_LongPower1(), "LongPower1 is OK", "LongPower1 is failed");
    // all_is_passed &= test(test_LongPower2(), "LongPower2 is OK", "LongPower2 is failed");
    // all_is_passed &= test(test_LongPowerWindow(), "LongPowerWindow is OK", "LongPowerWindow is failed");
    // all_is_passed &= test(test_LongSquare(), "LongSquare is OK", "LongSquare is failed");


    // all_is_passed &= test(test_Longnumber__lovest_bit(), "lovest_bit is OK", "lovest_bit is failed");
    // all_is_passed &= test(test_LongRightShift(), "LongRightShift is OK", "LongRightShift is failed");
    // all_is_passed &= test(test_LongMin(), "LongMin is OK", "LongMin is failed");
    // all_is_passed &= test(test_EuclidsBinaryAlgorithm(), "EuclidsBinaryAlgorithm is OK", "EuclidsBinaryAlgorithm is failed");
    // all_is_passed &= test(test_LCM(), "LCM is OK", "LCM is failed");
    // all_is_passed &= test(test_BarrettReduction(), "BarrettReduction is OK", "BarrettReduction is failed");
    // all_is_passed &= test(test_at_bit(), "at_bit is OK", "at_bit is failed");
    all_is_passed &= test(test_LongModPowerBarrett(), "LongModPowerBarrett is OK", "LongModPowerBarrett is failed");
    
    
    // all_is_passed &= test(test_resize(), "resize is OK", "resize is failed");
    // all_is_passed &= test(test_resize(), "resize is OK", "resize is failed");
    // all_is_passed &= test(test_resize(), "resize is OK", "resize is failed");
    // all_is_passed &= test(test_resize(), "resize is OK", "resize is failed");
    // all_is_passed &= test(test_resize(), "resize is OK", "resize is failed");


    if(all_is_passed){
        std::cout << "GREEN" << "Tests passed successfully." << "RESET" << std::endl << std::endl;
    }else{
        std::cout << "BOLDRED" << "Tests Failed." << "RESET" << std::endl;
    }
}