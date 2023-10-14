import io

import byte_gen
from byte_gen_test import signs_equality as se
from byte_gen_test import independence_of_signs as ios
from byte_gen_test import binary_sequence_uniformity as bsu
from byte_gen_test import chi_2_quantile as ch2
from my_timer import My_Timer


def bp(b):
    if b:
        return "True "
    
    return "False"

def main(rv_size=1000000):
    build_in_gen = byte_gen.BuildInGenerator();
    lehmer_low = byte_gen.LehmerLowGenerator(65537, 119, 4444444);
    lehmer_high = byte_gen.LehmerHighGenerator(65537, 119, 4444444);
    l_20 = byte_gen.L20Generator(1);
    l_89 = byte_gen.L89Generator(429496295);
    geffe = byte_gen.GeffeGenerator(34354672, 34656, 274563);
    wolfram = byte_gen.WolframGenerator(32456);
    
    trash_text = "Some string about warm love of Ron Uisli and his rat. Rat, rat, rat. How I like you my llittle liker of looking of sleeping ron."
    with io.open("lab_1/alice.txt", "r", encoding='utf-8') as f:
        trash_text = f.read()

    baba_luda = byte_gen.LibrarianGenerator(trash_text);
    blum_mika = byte_gen.BlumMikaliGenerator("12323eac7823");
    blum_mika_byte = byte_gen.BlumMikaliByteGenerator("12323eac7823");
    blum_blum_shuba = byte_gen.BlumBlumShubaGenerator("12323eac7823");
    blum_blum_shuba_byte = byte_gen.BlumBlumShubaByteGenerator("12323eac7823");

    gens = [
        build_in_gen,
        lehmer_low,
        lehmer_high,
        l_20,
        l_89,
        geffe,
        wolfram,
        baba_luda,
        blum_mika,
        blum_mika_byte,
        blum_blum_shuba,
        blum_blum_shuba_byte,
    ]

    timer_ = My_Timer()
    k = 1
    for gen in gens:
        print(f"\n{k:2d}) {gen.about()}")

        rv = [] 

        for i in range(0, rv_size):
            next = gen.next_byte()
            rv.append(next)
        
        print("alphas | equality | independence | bsu 10^1 | bsu 10^2 | bsu 10^3 | bsu 10^4")
        for a in [0.01, 0.05, 0.1]:
            print(f"{a:0.2f}   | {bp(se(rv, a))}    | {bp(ios(rv, a))}        | {bp(bsu(rv, a,10))}    | {bp(bsu(rv, a,100))}    | {bp(bsu(rv, a,1000))}    | {bp(bsu(rv, a,10000))}")

        print(f"Spend: {timer_.point(): 0.2f} s.")
        k += 1

    return 0;

if __name__ == "__main__":
    main(1000)

