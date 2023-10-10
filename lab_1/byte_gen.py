import random

class Generator:
    gen_name = "Abstract Generator"

    def next_byte(self):
        curent_id = 0
        res = 0
        
        while curent_id < 8:
            generated_v = self.next()

            for b in generated_v:
                res = res | (b << curent_id);
                
                curent_id += 1;

        return res

    def next(self):
        pass

    def about(self):
        return "Generator: " + self.gen_name

class BuildInGenerator(Generator):
    def __init__(self):
        self.gen_name = "BuildInGenerator";

    def next(self):
        return [random.getrandbits(1)]

class LehmerLowGenerator(Generator):
    def __init__(self, a, c, x_0):
        self.a = a
        self.c = c
        self.x_c = x_0
        self.m = pow(2, 32)
        
        self.gen_name = "LehmerLowGenerator";

    def next(self):
        x_n = (self.a * self.x_c + self.c) % self.m
        self.x_c = x_n;

        temp_x = self.get_lowest(self.x_c);
        res = [0 for i in range(8)]
        
        for i in range(7, -1, -1):
            res[i] = temp_x & 1
            temp_x = (temp_x >> 1)

        return res;

    def get_lowest(self, x):
        return x & 0xFF

class LehmerHighGenerator(Generator):
    def __init__(self, a, c, x_0):
        self.a = a
        self.c = c
        self.x_c = x_0
        self.m = pow(2, 32)
        
        self.gen_name = "LehmerHighGenerator"

    def next(self):
        x_n = (self.a * self.x_c + self.c) % self.m
        self.x_c = x_n

        temp_x = self.get_highest(self.x_c);
        res = [0 for i in range(8)];
        
        for i in range(7, -1, -1):
            res[i] = temp_x & 1;
            temp_x = (temp_x >> 1);

        return res;

    def get_highest(self, x):
        return (x >> 24) & 0xFF;


class L20Generator(Generator):
    def __init__(self, a):
        self.a = a
        self.gen_name = "L20Generator";
        self.m = pow(2, 20)

    def next(self):
        res = ((self.a >> 2) & 1) ^ ((self.a >> 4) & 1) ^ ((self.a >> 8) & 1) ^ ((self.a >> 19) & 1);
        
        self.a = ((self.a << 1) | res) % self.m;

        return [res];

class L89Generator(Generator):
    def __init__(self, a):
        self.vals = [0 for i in range(89)];

        for i in range(32):
            self.vals[i] = a & 1;
            a = (a >> 1);

        self.gen_name = "L89Generator"
    
    def next(self):
        res = self.vals[0] ^ self.vals[1];
        
        for i in range(1, 89):
            self.vals[i - 1] = self.vals[i];

        self.vals[89-1] = res;

        return [res];

class GeffeGenerator(Generator):
    def __init__(self, a_11, a_9, a_10):
        self.a_11 = a_11
        self.a_9 = a_9
        self.a_10 = a_10

        self.m_11 = pow(2, 11)
        self.m_9 = pow(2, 9)
        self.m_10 = pow(2, 10)
        
        self.l_9();
        self.l_9();
        self.l_10();

        self.gen_name = "GeffeGenerator";

    def next(self):
        x = self.l_11();
        y = self.l_9();
        s = self.l_10();

        return [s and x ^ (True ^ s) and y]

    def l_11(self):
        res = ((self.a_11 >> 10) & 1) ^ ((self.a_11 >> 8) & 1);

        self.a_11 = ((self.a_11 << 1) | res) % self.m_11

        return res;

    def l_9(self):
        res = ((self.a_9 >> 8) & 1) ^ ((self.a_9 >> 7) & 1) ^ ((self.a_9 >> 5) & 1) ^ ((self.a_9 >> 4) & 1);

        self.a_9 = ((self.a_9 << 1) | res) % self.m_9

        return res;

    def l_10(self):
        res = ((self.a_10 >> 9) & 1) ^ ((self.a_10 >> 6) & 1);

        self.a_10 = ((self.a_10 << 1) | res) % self.m_10

        return res;


class WolframGenerator(Generator):
    def __init__(self, r):
        self.r = r
        self.gen_name = "WolframGenerator";
        self.m = pow(2, 32)
    
    def next(self):
        # r = (r <<< 1) ^ (r | (r >>> 1))
        self.r = (((self.r << 1) | (self.r >> 31)) ^ (self.r | ((self.r >> 1) | (self.r << 31)))) % self.m

        if self.r % 2:
            return [True];

        return [False]

class LibrarianGenerator(Generator):
    trash_text = ""
    def __init__(self, trash_text):
        self.trash_text = trash_text
        self.gen_name = "LibrarianGenerator"
        self.id = 0

    def next(self):
        res = []
        
        c = ord(self.trash_text[self.id])
        self.id += 1
        for i in range(0, 8):
            res.append((c >> i) & 1);
        
        if self.id >= len(self.trash_text):
            print("Text is small. need improvements")
            self.trash_text = input("Please, type new text: ")
            self.id = 0

        return res;

class BlumMikaliGenerator(Generator):
    def __init__(self, T_0_str):
        self.T_0 = int(T_0_str, 16)
        self.gen_name = "BlumMikaliGenerator";
    
        self.p = 0xcea42b987c44fa642d80ad9f51f10457690def10c83d0bc1bcee12fc3b6093e3
        self.a = 0x5b88c41246790891c095e2878880342e88c79974303bd0400b090fe38a688356
        self.comp_p = (self.p - 1) // 2

        self.T_0 = 0

    def next(self):
        self.T_0 = pow(self.a, self.T_0, self.p)

        if self.comp_p > self.T_0:
            return [True];

        return [False];

class BlumMikaliByteGenerator(Generator):
    p = 0xcea42b987c44fa642d80ad9f51f10457690def10c83d0bc1bcee12fc3b6093e3
    a = 0x5b88c41246790891c095e2878880342e88c79974303bd0400b090fe38a688356
    q = 0x675215cc3e227d3216c056cfa8f8822bb486f788641e85e0de77097e1db049f1
    def __init__(self, T_0_str):
        self.T_0 = int(T_0_str, 16)
        self.gen_name = "BlumMikaliByteGenerator";

    def next(self):
        self.T_0 =  pow(self.a, self.T_0, self.p)

        temp = (self.T_0 * 128) % self.q
        res = [0 for i in range(8)]
        
        for i in range(7, -1, -1):
            res[i] = (temp >> i) & 1

        return res;

class BlumBlumShubaGenerator(Generator):
    p = 0xd5bbb96d30086ec484eba3d7f9caeb07
    q = 0x425d2b9bfdb25b9cf6c416cc6e37b59c1f
    n = p * q

    def __init__(self, r_str):
        self.r = int(r_str, 16)
        self.gen_name = "BlumBlumShubaGenerator";

    def next(self):
        self.r = (self.r * self.r) % self.n

        if self.r & 1:
            return [True]

        return [False];

class BlumBlumShubaByteGenerator(Generator):
    p = 0xd5bbb96d30086ec484eba3d7f9caeb07
    q = 0x425d2b9bfdb25b9cf6c416cc6e37b59c1f
    n = p * q

    def __init__(self, r_str):
        self.r = int(r_str, 16)
        self.gen_name = "BlumBlumShubaByteGenerator";

    def next(self):
        self.r = (self.r * self.r) % self.n
        
        res = [0 for i in range(8)];
        for i in range(8):
            res[i] = (self.r >> i) & 1 

        return res;


