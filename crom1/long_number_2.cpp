#include "long_number.h"

std::string LongNumber::to_string() const{
    return to_hex_string();
}

void LongNumber::resize(int size){
    std::vector<base_t> *numb = new std::vector<base_t>;
    numb->resize(size);

    for(int i = 0; i < numb->size(); ++i){
        numb->at(i) = (base_t)0;
    }

    int min_size = std::min(size, this->size());
    for(int i = 0; i < min_size; ++i){
        numb->at(i) = number->at(i);
    }

    number = numb;
}

int LongNumber::size() const{
    return number->size();
}

unsigned long int get_mask_1(int n){  // fill first n with 1
    unsigned long int mask = 1;
    if(n < 1){
        mask = 0;
        return mask;
    }

    if(n > 64){
        mask = -1;
        return mask;
    }
    n -=1;

    for(int i = 0; i < n; ++i){
        mask = mask << 1;
        mask = mask | 1; 
    }
    return mask;
}

LongNumber::LongNumber(int size = 1){
    this->number = new std::vector<base_t>;
    this->number->resize(size);
    
    for(int i = 0; i < this->size(); ++i){
        this->number->at(i) = (base_t)0;
    }
}

void LongNumber::print() const {
    std::cout << str() << std::endl;
}

std::string LongNumber::str() const {
    std::string out = "";
    unsigned long long temp = 0;
    for(int i = 0; i < this->number->size(); ++i){
        out = out + std::to_string(this->number->at(i)) + ", ";
    }
    return out;
}

void LongNumber::set(unsigned long long number){
    unsigned long long mask = get_mask_1(num_size);
    for(int i = 0; i < size(); ++i){
        this->number->at(i) = number & mask;
        number = number >> num_size;
    }

}

LongNumber LongAdd(LongNumber A, LongNumber B){
    int max_size = std::max(A.size(), B.size());
    unsigned long long mask = get_mask_1(num_size);
    A.resize(max_size);
    B.resize(max_size);


    LongNumber C = LongNumber(max_size);

    base_t carry = 0;
    uint64_t temp = 0;
    for(int i = 0; i < max_size; ++i){
        temp = uint64_t(A.number->at(i)) + uint64_t(B.number->at(i)) + uint64_t(carry);
        C.number->at(i) = temp & mask;
        carry = temp >> num_size;
    }
    return C;
}

LongNumber::LongNumber(std::vector<uint64_t> number){
    set(number);
}

LongNumber::LongNumber(std::string number){
    set_by_hex(number);
}

void LongNumber::set(std::vector<uint64_t> number){
    delete this->number;
    this->number = new std::vector<base_t>;
    this->number->resize(number.size());
    
    for(int i = 0; i < this->size(); ++i){
        this->number->at(i) = (base_t)number.at(i);
    }
}

void LongNumber::set(LongNumber number){
    this->number->resize(number.number->size());
    for(int i = 0; i < number.number->size(); ++i){
        this->number->at(i) = number.number->at(i);
    }
}

int LongCmp(LongNumber A, LongNumber B){
    int max_size = std::max(A.size(), B.size());
    A.resize(max_size);
    B.resize(max_size);

    int i = A.size() - 1;
    while(i > -1 && A.number->at(i) == B.number->at(i)){
        i = i-1;
    }

    if (i == -1){
        return 0;
    }else{
        if(A.number->at(i) > B.number->at(i)){
            return 1;
        }else{
            return -1;
        }
    }
}

LongNumber LongSub(LongNumber A, LongNumber B){
    if(LongCmp(A, B) == -1){
        std::cerr << "A leq B where A: " << A.to_hex_string() << " and B is: " << B.to_hex_string() << std::endl;
        return LongNumber("0");
    }
    int max_size = std::max(A.size(), B.size());
    A.resize(max_size);
    B.resize(max_size);
    LongNumber C = LongNumber(max_size);
    
    int64_t borrow = 0;
    int64_t temp = 0;
    for(int i = 0; i < max_size; ++i){
        temp = int64_t(A.number->at(i)) - int64_t(B.number->at(i)) - int64_t(borrow);
        
        if(temp >= 0){
            C.number->at(i) = base_t(temp);
            borrow = 0;
        }else{
            C.number->at(i) = base_t((int64_t(1) << (num_size)) + temp);
            borrow = 1;
        }
    }

    return C;
}

std::string LongNumber::to_hex_string() const{
    std::string rez = "";
    unsigned long mask = get_mask_1(4);

    uint16_t temp = 0;
    for(int i = size() - 1; i > -1; --i){
        for(int j = num_size - 4; j > -1; j -= 4){
            temp = (number->at(i) >> j) & mask;
            rez += HEX[temp];
        }
    };

    rez.erase(0, rez.find_first_not_of('0'));
    if(rez == ""){
        rez = "0";
    }

    return rez;
}

int LongNumber::lovest_bit() const{
    return number->at(0) & 1;
}

uint64_t hex_to_uint64_t(std::string s){
    if(isdigit(s[0])){
        return uint64_t(stoi(s));
    }else if(s == "a"){
        return uint64_t(10);
    }else if(s == "b"){
        return uint64_t(11);
    }else if(s == "c"){
        return uint64_t(12);
    }else if(s == "d"){
        return uint64_t(13);
    }else if(s == "e"){
        return uint64_t(14);
    }else if(s == "f"){
        return uint64_t(15);
    }

    if(s == ""){
        std::cerr << "error: empty string" << std::endl;
    }

    std::cerr << "error: unnown symbol: " << s << ";" << std::endl;

    throw "ERROR: unnown symbol: " + s;
}

int hex_size_to_64(std::string s){
    if(s == ""){
        return 0;
    }

    if(s.size() % 8 == 0){
        return s.size()/8;
    }
    
    return s.size()/8 + 1;
}

std::string to_8_div_lenght(std::string s){
    int l = s.size() % 8;
    if(l == 0){
        return s;
    }

    l = 8 - l;
    for(int i = 0; i < l; ++i){
        s = "0" + s;
    }

    return s;
}

uint64_t get_number_at_8_hex(std::string hex){
    uint64_t number = 0;
    uint64_t temp = 0;
    for(int i = 0; i < 8; ++i){
        temp = hex_to_uint64_t(hex.substr(i, 1));
        number |= (temp << (7-i)*4);
    }

    return number;
}

LongNumber LongNumber::set_by_hex(std::string number){
    std::vector<uint64_t> *v = new std::vector<uint64_t>;
    v->resize(hex_size_to_64(number));
    number = to_8_div_lenght(number);

    std::string temp_str = "";
    for(int i = 0; i < v->size(); ++i){
        for(int j = 0; j < 8; ++j){
            temp_str = number.substr(number.size() - 8 - i*8, 8);
        }
        int numb = get_number_at_8_hex(temp_str);
        v->at(i) = numb;
    }

    set(*v);

    return *this;
}

LongNumber LongMulOneDigit(LongNumber A, unsigned long long b){
    uint64_t mask = get_mask_1(num_size);
    uint64_t carry = 0;
    uint64_t temp = 0;
    LongNumber C = LongNumber(1);
    C.resize(A.size() + 1);
    for(int i = 0; i < A.size(); ++i){
        temp = A.number->at(i) * b + carry;
        C.number->at(i) = temp & mask;
        carry = temp >> num_size;
    }
    C.number->at(A.size()) = carry;

    return C;
}

LongNumber LongLeftShift(LongNumber A){
    LongNumber rez = 0;
    rez.resize(A.size() + 1);
    base_t cary = 0;
    for(int j = 0; j < A.size(); ++j){
        rez.number->at(j) = (A.number->at(j) << 1);
        rez.number->at(j) = rez.number->at(j) | cary;
        cary = (A.number->at(j) >> num_size-1) & 1;
    }

    return rez;
}

LongNumber LongRightShift(LongNumber A){
    LongNumber rez = 0;
    rez.resize(A.size());
    base_t cary = 0;
    for(int j = A.size()-1; j > -1; --j){
        rez.number->at(j) = (A.number->at(j) >> 1);
        rez.number->at(j) = rez.number->at(j) | cary;
        cary = (A.number->at(j) & 1) << (num_size-1);
    }

    return rez;
}

LongNumber LongRightShift(LongNumber A, int n){
    LongNumber rez;
    rez.set(A);
    
    for(int i = 0; i < n; ++i){
        rez = LongRightShift(rez);
    }

    return rez;
}

LongNumber LongShiftDigitsToHigh(LongNumber A, int l){  // left shift
    if(l > num_size * A.size()){
        std::cerr << "error: shift number is grather than size of number (shift number is: ";
        std::cerr << l << " while size is: " << A.size() * num_size << ")" << std::endl;
        return LongNumber(0);
    }

    for(int i = 0; i < l; ++i){
        A = LongLeftShift(A);
    }

    return A;
}

LongNumber LongLeftShift_expandable(LongNumber A){
    LongNumber rez = 0;
    rez.resize(A.size());
    // std::cout << std::to_string((A.higest_bit_id() + 1) % 32 == 0) << std::endl;
    base_t cary = 0;
    for(int j = 0; j < A.size(); ++j){
        rez.number->at(j) = (A.number->at(j) << 1);
        rez.number->at(j) = rez.number->at(j) | cary;
        cary = (A.number->at(j) >> num_size-1) & 1;
    }

    if((A.higest_bit_id() + 1) % 32 == 0){
        rez.resize(A.size() + 1);
        rez.number->at(A.size()) |= cary;
    }
    
    rez.smolarize();
    return rez;
}

int LongNumber::higest_bit_id() const{
    for(int i = size()-1; i > -1; --i){
        for(int j = num_size - 1; j > -1; --j){
            if(((number->at(i) >> j) & 1) == 1){
                return ((i * num_size) + j);
            }
        }
    }

    return -1;
}

LongNumber LongShiftDigitsToHigh_expandable(LongNumber A, int l){  // left shift with different size changing
    // if(l > num_size * A.size()){
    //     A.resize((l/32) + 1);
    // }

    for(int i = 0; i < l; ++i){
        A = LongLeftShift_expandable(A);
    }

    return A;
}

LongNumber LongNumber::smolarize(){
    while(number->size() != 0 && number->at(number->size()-1) == 0){
        resize(number->size()-1);
    }

    if(size() == 0){
        resize(1);
    }

    return *this;
}

LongNumber LongMul(LongNumber A, LongNumber B){
    LongNumber C("0");
    A.smolarize();
    B.smolarize();
    if(A.to_hex_string() == "0" || B.to_hex_string() == "0"){
        return C;
    }
    // std::cout << "A: " << A.to_hex_string() << "; B: " << B.to_hex_string() << std::endl;
    int max_size = std::max(A.size(), B.size());
    if(LongCmp(A, B) == -1){
        C = B;
        B = A;
        A = C;
    }

    C = LongNumber(2*max_size);
    
    LongNumber temp = LongNumber(1);
    for(int i = 0; i < B.size(); ++i){
        temp = LongMulOneDigit(A, B.number->at(i));
        temp = LongShiftDigitsToHigh_expandable(temp, i*num_size);
        C = LongAdd(C, temp); // багаторозрядне додавання!
        // std::cout << "c: " << C.to_hex_string() << "; temp: " << temp.to_hex_string() << std::endl;
        // std::cout << "B at i: " << B.number->at(i) << "; i: " << i << std::endl;
    }
    
    return C;
}

int BitLength(LongNumber A){
    for(int i = A.size() - 1; i > -1; --i){
        if(A.number->at(i) != 0){
            return (i+1) * num_size;
        }
    }

    return 0;
}

LongNumber get_2_in_power_n(int power){
    LongNumber rez;
    rez.set(1);
    rez.resize((power / num_size) + 1);
    rez = LongShiftDigitsToHigh(rez, power);

    return rez;
}

LongNumber LongDivMod(LongNumber A, LongNumber B){
    if(B.to_hex_string() == "0"){
        return LongNumber("0");
    }

    LongNumber R, Q, C;
    int k = B.higest_bit_id() + 1;
    R.set_by_hex(A.to_hex_string());
    
    int t = 0;
    LongNumber temp;
    while(LongCmp(R, B) != -1){  // багаторозрядне порівняння!
        t = R.higest_bit_id() + 1;
        C = LongShiftDigitsToHigh_expandable(B, t - k);
        while (LongCmp(R, C) == -1){  // багаторозрядне порівняння! вийшло забагато?
            t = t - 1; // тоді повертаємось на біт назад
            C = LongShiftDigitsToHigh_expandable(B, t - k);
        }
        
        R = LongSub(R, C);
        temp = get_2_in_power_n(t - k);
        Q = LongAdd(Q, temp); // встановити в Q біт із номером (t – k)
    }

    return Q;
}

LongNumber LongDivFraction(LongNumber A, LongNumber B){
    if(B.to_hex_string() == "0"){
        return LongNumber("0");
    }

    LongNumber R, Q, C;
    int k = B.higest_bit_id() + 1;
    R.set_by_hex(A.to_hex_string());
    
    int t = 0;
    LongNumber temp;
    while(LongCmp(R, B) != -1){  // багаторозрядне порівняння!
        t = R.higest_bit_id() + 1;
        C = LongShiftDigitsToHigh_expandable(B, t - k);
        while (LongCmp(R, C) == -1){  // багаторозрядне порівняння! вийшло забагато?
            t = t - 1; // тоді повертаємось на біт назад
            C = LongShiftDigitsToHigh_expandable(B, t - k);
        }
        
        R = LongSub(R, C);
        temp = get_2_in_power_n(t - k);
        Q = LongAdd(Q, temp); // встановити в Q біт із номером (t – k)
    }

    return R;
}

LongNumber LongPower1(LongNumber A, LongNumber B){
    if(B.to_hex_string() == "0"){
        return LongNumber("1");
    }else if(A.to_hex_string() == "0"){
        return LongNumber("0");
    }else if(A.to_hex_string() == "1"){
        return LongNumber("1");
    }

    LongNumber C = LongNumber("1");
    for(int i = 0; i < B.size(); ++i){
        for(int j = 0; j < 8; ++j){
            if((B.number->at(i) >> j) & 1 == 1){
                C = LongMul(C, A);
                C.smolarize();
            }
            A = LongMul(A, A);
            A.smolarize();
            A = LongNumber(A.to_hex_string());
            // std::cout << "i: " << i << "j: " << j << "C: " << C.to_hex_string() << ":" << std::to_string(C.size()) << "A: " << A.to_hex_string() << ":" << std::to_string(A.size()) << std::endl;
        }
    }

    return C;
}

LongNumber LongPower2 (LongNumber A, LongNumber B){
    if(B.to_hex_string() == "0"){
        return LongNumber("1");
    }else if(A.to_hex_string() == "0"){
        return LongNumber("0");
    }else if(A.to_hex_string() == "1"){
        return LongNumber("1");
    }

    LongNumber C = LongNumber("1");
    for(int i = B.size() - 1; i >= 0 ; --i){
        for(int j = 31; j >= 0; --j){
            if(((B.number->at(i) >> j) & 1) == 1){
                C = LongMul(C, A);
                C.smolarize();
            }

            if((i != 0) || (j != 0)){
                C = LongMul(C, C);
                C.smolarize();
            }
        }
    }

    return C;
}

LongNumber LongPowerWindow(LongNumber A, LongNumber B){
    LongNumber C("1"), temp("0");

    std::vector<LongNumber> D; // D[] – таблиця степенів А
    D.resize(255);
    D.at(0) = LongNumber("1");
    D.at(1) = A;

    for(unsigned long long i = 2; i < 255; ++i){ // передобчислення
        temp = LongMul(D.at(i-1), A);
        temp.smolarize();
        D.at(i) = temp;
    }

    base_t mask = 255, temp_mask = 255;
    for(int i = B.size()-1; i > -1; --i){
        for(int j = 0; j < 4; ++j){
            mask = (temp_mask << 8*j);
            int d_id = (B.number->at(i) & mask) >> (8*j);
            C = LongMul(C, D.at(d_id)); // багаторозрядне множення!
            C.smolarize();
            if(i != 0){ // на останньому кроці до квадратів не підносимо
                for(int k = 1; k < 9; ++k){ // підносимо до квадрату t разів
                    C = LongMul(C, C); // багаторозрядне множення!
                    C.smolarize();
                }
            }
        }
    }

    return C;
}

LongNumber LongSquare(LongNumber A){
    return LongMul(A, A);
}

LongNumber LongMin(LongNumber A, LongNumber B){
    if(LongCmp(A, B) == 1){
        return B;
    }

    return A;
}

LongNumber EuclidsBinaryAlgorithm(LongNumber A, LongNumber B){
    LongNumber D("1");
    
    while ((A.lovest_bit() == 0) & (B.lovest_bit() == 0)){ // виокремлення загальної парної частини
        A = LongRightShift(A);
        B = LongRightShift(B);
        D = LongLeftShift_expandable(D);
    }
    
    while (A.lovest_bit() == 0){
        A = LongRightShift(A);
    }
    
    LongNumber temp("0");
    while (B.to_hex_string() != "0"){
        while (B.lovest_bit() == 0){
            B = LongRightShift(B);
        }
        
        // std::cout << A.to_hex_string() << " : " << B.to_hex_string() << std::endl;
        
        temp.set(A);
        A = LongMin(A, B);
        if(LongCmp(temp, B) == 1){
            // std::cout << "A greather B" << std::endl;
            B = LongSub(temp, B);
        }else{
            B = LongSub(B, temp);
        }
        // std::cout << A.to_hex_string() << " : " << B.to_hex_string() << std::endl;
    }

    D = LongMul(D, A);
    D.smolarize();
    return D;
}


LongNumber GCD(LongNumber A, LongNumber B){
    return EuclidsBinaryAlgorithm(A, B);
}


LongNumber LCM(LongNumber A, LongNumber B){
    LongNumber gcd = EuclidsBinaryAlgorithm(A, B);
    LongNumber sub = LongDivMod(B, gcd);
    return LongMul(A, sub);
}

LongNumber BarrettReduction(LongNumber x, LongNumber n, LongNumber mu){
    // Процедура BarrettReduction (x, n, mu)
    // Вхід: багаторозрядні числа x, n, передобчислене значення
    // Вихід: багаторозрядне число r = x mod n

    int k = n.size();
    LongNumber q("0"), r("0");
    q = LongRightShift(x, num_size*(k - 1)); // відкидання останніх k-1 цифри
    q = LongMul(q, mu);
    q = LongRightShift(q, num_size*(k + 1));
    // q.smolarize();
    // std::cout << x.to_hex_string() << " : " << r.to_hex_string() << " : " << n.to_hex_string() << " : " << q.to_hex_string() << std::endl;
    r = LongSub(x, LongMul(q, n));
    // std::cout << r.to_hex_string() << std::endl;
    while (LongCmp(r, n) != -1){ // Барретт гарантує, що цикл виконується
        // std::cout << r.to_hex_string() << " : " << n.to_hex_string() << std::endl;
        r = LongSub(r, n); // не більше двох разів
    }

    return r;
}

LongNumber CalcMu(LongNumber n){
    LongNumber mu("100000000"), power("0");
    int k = 2 * n.size();
    power.set(k);

    mu = LongDivMod(LongPowerWindow(mu, power), n);
    // std::cout << "mu: " << mu.to_hex_string() << std::endl;
    return mu;
}

LongNumber BarrettReduction(LongNumber x, LongNumber n){
    return BarrettReduction(x, n, CalcMu(n));
}

int LongNumber::at_bit(int i){
    if(i < 0){
        std::cerr << "ERROR: Out of range, while try to get bit with id " << i << "." << std::endl;
        // throw "ERROR: Out of range, while try to get bit with id " + i + '.';
        return 0;
    }

    if(i / num_size > size()){
        std::cerr << "ERROR: Out of range, while try to get bit with id " << i << "." << std::endl;
        // throw "ERROR: Out of range, while try to get bit with id " + i + '.';
        return 0; 
    }
    
    return ((number->at(i / num_size) >> (i % num_size)) & 1);
}

LongNumber LongModPowerBarrett(LongNumber A, LongNumber B, LongNumber N){
    LongNumber C("1");
    LongNumber mu = LongDivMod(LongShiftDigitsToHigh_expandable(LongNumber("1"), 2 * N.size() * num_size), N); // єдине ділення!
    int b_size = B.size() * num_size;
    for(int i = 0; i < b_size; ++i){
        if(B.at_bit(i) == 1){
            C = BarrettReduction(LongMul(C, A), N, mu);
            C.smolarize();
        }
        A = BarrettReduction (LongMul(A, A), N, mu);
        A.smolarize();
    }

    return C;
}

LongNumber LongAddMod(LongNumber A, LongNumber B, LongNumber N){
    return BarrettReduction(LongAdd(A, B), N);
}

LongNumber LongSubMod(LongNumber A, LongNumber B, LongNumber N){
    return BarrettReduction(LongSub(A, B), N);
}

LongNumber LongMulMod(LongNumber A, LongNumber B, LongNumber N){
    return BarrettReduction(LongMul(A, B), N);
}

LongNumber LongSquareMulMod(LongNumber A, LongNumber N){
    return BarrettReduction(LongSquare(A), N);
}

