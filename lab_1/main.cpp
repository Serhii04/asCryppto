#include <iostream>

#include "byte_gen.h"

using namespace std;

// int main(){
//     // unsigned n = 4567;
//     // std::cout << n << std::endl;
//     // std::cout << ((n >> 1) | (n << 31)) << std::endl;
//     // std::cout << n + 2 << std::endl;

//     LongNumber p = LongNumber("cea42b987c44fa642d80ad9f51f10457690def10c83d0bc1bcee12fc3b6093e3");
//     LongNumber a = LongNumber("5b88c41246790891c095e2878880342e88c79974303bd0400b090fe38a688356");
//     LongNumber comp_p = LongDivMod(LongSub(p, LongNumber("1")), LongNumber("2"));
//     LongNumber T_0 = LongNumber("7d657c8f14f7389ad035a31fb6425b44a88470f4666b42ed20960d0ba4baf0db");
//     std::cout << LongCmp(comp_p, T_0) << std::endl;
// }

int main() {
    BuildInGenerator build_in_gen = BuildInGenerator();
    LehmerLowGenerator lehmer_low = LehmerLowGenerator(65537, 119, 4444444);
    LehmerHighGenerator lehmer_high = LehmerHighGenerator(65537, 119, 4444444);
    L20Generator l_20 = L20Generator(1);
    L89Generator l_89 = L89Generator(429496295);
    GeffeGenerator geffe = GeffeGenerator(34354672, 34656, 274563);
    WolframGenerator wolfram = WolframGenerator(32456);
    LibrarianGenerator baba_luda = LibrarianGenerator("Some string about warm love of Ron Uisli and his rat. Rat, rat, rat. How I like you my llittle liker of looking of sleeping ron.");
    BlumMikaliGenerator blum_mika = BlumMikaliGenerator("12323eac7823");
    BlumMikaliByteGenerator blum_mika_byte = BlumMikaliByteGenerator("12323eac7823");

    for(int i = 0; i < 100; ++i){
        for(auto b: blum_mika_byte.next()){
            std::cout << b << " ";
        }

        // std::cout << std::endl;
    }

    return 0;
}

