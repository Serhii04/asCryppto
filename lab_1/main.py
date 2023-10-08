
import byte_gen
import byte_gen_test


def main():
    build_in_gen = byte_gen.BuildInGenerator();
    lehmer_low = byte_gen.LehmerLowGenerator(65537, 119, 4444444);
    lehmer_high = byte_gen.LehmerHighGenerator(65537, 119, 4444444);
    l_20 = byte_gen.L20Generator(1);
    l_89 = byte_gen.L89Generator(429496295);
    geffe = byte_gen.GeffeGenerator(34354672, 34656, 274563);
    wolfram = byte_gen.WolframGenerator(32456);
    baba_luda = byte_gen.LibrarianGenerator("Some string about warm love of Ron Uisli and his rat. Rat, rat, rat. How I like you my llittle liker of looking of sleeping ron.");
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

    # for(int i = 0; i < 100; ++i){
    #     auto get_rez = blum_blum_shuba_byte.next_byte();
    #     std::cout << "get: " << get_rez << std::endl;
    # }

    k = 1
    for gen in gens:
        print(f"\n{k:2d}) {gen.about()}")
 
        # rv_size = 1000000;
        rv_size = 1000;
        rv = [] 

        for i in range(0, rv_size):
            rv.append(gen.next_byte())
            # print(f"{i}) {rv[-1]}")

        alphas = [0.01, 0.05, 0.1];
        for alpha in alphas:
            print(f"alpha = {alpha}")
            print(f"equality       :><: {byte_gen_test.signs_equality(rv, alpha)}")
            print(f"independence   :><: {byte_gen_test.independence_of_signs(rv, alpha)}")
            print(f"bsu r = 10^1   :><: {byte_gen_test.binary_sequence_uniformity(rv, alpha, 10)}")
            print(f"bsu r = 10^2   :><: {byte_gen_test.binary_sequence_uniformity(rv, alpha, 100)}")
            print(f"bsu r = 10^3   :><: {byte_gen_test.binary_sequence_uniformity(rv, alpha, 1000)}")
            print(f"bsu r = 10^5   :><: {byte_gen_test.binary_sequence_uniformity(rv, alpha, 10000)}")

        k += 1;

    return 0;

if __name__ == "__main__":
    main()