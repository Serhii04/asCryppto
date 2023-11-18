import random
import math
from sympy.ntheory import jacobi_symbol

__FLOOD__MODE__ = False

__SMALL_PRIMES__ = [
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
	419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
	547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
]

def gcd(a: int, b: int) -> int:
    while b != 0:
        temp = b
        b = a % b
        a = temp
    
    return a

def is_strong_pseudoprime(x: int, p: int) -> bool:
    """Say if p is strong pseudoprime by base x"""
    d = p - 1
    s = 0
    
    while d % 2 == 0:
        d = d // 2
        s += 1

    temp_x = pow(x, d, p)
    if temp_x == 1 or temp_x == p - 1:
        return True
    
    for r in range(1, s):
        temp_x = pow(temp_x, 2, p)

        if temp_x == p - 1:
            return True
        
        if temp_x == 1:
            return False
        
    return False

def Miller_Rabin_test_once(p: int) -> bool:
    x = random.randint(a=2, b=(p - 1))

    if gcd(x, p) > 1:
        return False
    
    if not is_strong_pseudoprime(p=p, x=x):
        return False

    return True
    
def Miller_Rabin_test(p: int, k: int) -> bool:
    for i in range(k):
        if not Miller_Rabin_test_once(p=p):
            return False
    
    return True

def is_prime(p: int) -> bool:
    for prime in __SMALL_PRIMES__:
        if p > prime and p % prime == 0:
            return False
    
    return Miller_Rabin_test(p=p, k=int(math.log(p)))

def get_random_prime_in_interval(start: int, end: int) -> int:
    """Return prime with a form p = 4k+3"""
    p = random.randint(a=start, b=end)
    
    p = p + 3 - (p % 4)  # for apropriate form 4k + 3
    while not is_prime(p):
        p += 4

    return p

def get_prime_number_blum_part_in_interval(start: int, end: int=None) -> int:
    """Returns prime number p = 4k+3"""
    p = start + 3 - (start % 4)  # for apropriate form 4k + 3
    while not is_prime(p):
        p += 4

    return p
        
def get_prime_number_blum_part_of_lenght(l: int) -> int:
    p = 0
    B = 1

    for i in range(l):
        b = (random.randbytes(n=1))[0]
        
        if b:
            p += B
        
        B *= 2

    # p += B  # because we need number that have l or more bits

    return get_prime_number_blum_part_in_interval(start=p, end=2 * p - 2)

# ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def format_message(message: int, n: int):
    l = math.ceil(n.bit_length() / 8)
    
    r = random.randint(0, pow(2, 64) - 1)

    x = 255 * pow(2, 8 * (l - 2)) + message * pow(2, 64) + r

    return x

def is_blum_number(n: int) -> bool:
    return (n - 3) % 4 == 0

def GenerateKeyPair(l: int=256) -> (int, int):
    p = get_prime_number_blum_part_of_lenght(l)
    q = get_prime_number_blum_part_of_lenght(l)

    if p == q:
        q = get_prime_number_blum_part_in_interval(start=q + 1, end=2 * q - 2)

    if not is_blum_number(p) or not is_blum_number(q):
        raise ValueError("no blum number found")

    return p, q

class User:
    def __init__(self, p: int=None, q: int=None, b: int=0):
        if p is None and q is None:
            p, q = GenerateKeyPair()

        if p is None or q is None:
            raise ValueError(F"None value is given")

        self.set_key(p=p, q=q, b=b)
    
    def set_key(self, p: int, q: int, b: int=0) -> None:
        self.n = p * q
        self.p = p
        self.q = q
        self.b = b

    def set_key_server(self, n: int, b: int=0) -> None:
        self.n = n
        self.p = None
        self.q = None
        self.b = b

    def open_key(self) -> (int, int) or int:
        return self.n, self.b
    
    def secret_key(self) -> (int, int):
        return self.p, self.q
    
    def __str__(self) -> str:
        s = ""
        
        if self.p is not None:
            s += f"p = {hex(self.p)},\n"
        
        if self.q is not None:
            s += f"q = {hex(self.q)},\n"
        
        if self.b != 0:
            s += f"b = {hex(self.b)},\n"

        s += f"n = {hex(self.n)}"

        return s

def get_four_square_roots(y: int, p: int, q: int) -> [int, ...]:
    n = p * q
    
    s1 = pow(y, (p + 1) // 4, p)
    s2 = pow(y, (q + 1) // 4, q)

    u = pow(p, -1, q)
    v = pow(q, -1, p)

    y_sqrt = []
    for pm1 in [1, -1]:
        for pm2 in [1, -1]:
            y_sqrt.append((pm1 * u * p * s2 + pm2 * v * q * s1) % n)
    
    return y_sqrt

def Sign(message: int, user: User) -> int:
    n, b = user.open_key()
    p, q = user.secret_key()

    while True:
        x = format_message(message=message, n=n)
        while jacobi_symbol(m=x, n=p) != 1 or jacobi_symbol(m=x, n=q) != 1:
            x = format_message(message=message, n=n)

        x_sqrts = get_four_square_roots(y=x, p=p, q=q)

        rch = random.choice(x_sqrts)  # rch^2 = x (mod pq)

        if pow(rch, 2, n) == x % n:
            return rch

def Verify(message: int, sign: int, user: User) -> bool:
    n, b = user.open_key()

    x_ = pow(sign, 2, n)

    some_form_mess = format_message(message=message, n=n)
    
    if (x_ >> 64) == (some_form_mess >> 64):
        return True
    
    return False

def Encrypt_extended(message: int, user: User) -> int:
    n, b = user.open_key()
    
    x = format_message(message, n)
    
    if math.ceil(message.bit_length() / 8) > math.ceil(n.bit_length() / 8) - 10:
        print("Message is big")

    y = (x * (x + b)) % n

    c1 = ((x + b * pow(2, -1, n)) % n) % 2
    c2 = jacobi_symbol(m=(x + b * pow(2, -1, n)), n=n)
    if c2 != 1:
        c2 = 0

    return y, c1, c2

def Decrypt_extended(y: int, c1: int, c2: int, receiver: User) -> int:
    n, b = receiver.open_key()
    p, q = receiver.secret_key()
    
    right_sqrt_parts = get_four_square_roots(y=(y + pow(b, 2) * pow(4, -1, n)), p=p, q=q)

    for rp_i in right_sqrt_parts:
        y_i = (rp_i - b * pow(2, -1, n)) % n

        cc1 = ((y_i + b * pow(2, -1, n)) % n) % 2
        cc2 = jacobi_symbol(m=(y_i + b * pow(2, -1, n)), n=n)
        if cc2 != 1:
            cc2 = 0

        if cc1 == c1 and cc2 == c2:
            l = math.ceil(n.bit_length() / 8)

            return (y_i - 255 * pow(2, 8 * (l - 2))) >> 64


#ZNP
def znp_atack(count: int, modulus: str) -> None:
    for i in range(count):
        t = get_random_prime_in_interval(3, 2 ** 2048 - 1)
        y = t ** 2 % int(modulus, 16)
        print(f"Y: {hex(y)[2:].upper()}\nt: {str(t)}\n")
    
def calculate_p_q(n: str, t: int, z: str) -> None:
    n = int(n, 16)
    z = int(z, 16)
    if t == z and t == n - z:
        raise("t == z == n - z")

    p = gcd(n, t + z)
    q = n // p

    print(f"P: {hex(p)[2:].upper()}")
    print(f"Q: {hex(q)[2:].upper()}")

m = "B69BEEFBCDDD8EDDA32384885080A1B4DA3FEBC55E1DEE0525D247B2C927C4A23F2B5E03FDEABA4014E35738D1971F06F23FC66F348C86E6CA208942C328FC6ECEC78C655601C2A356E80551E43028875FE5678A508D6CA9A24F637DAE40475A3E49C42BA62CE8A41CEDFDCF418FB42703D3CD21FF09AC97077130AB799BA971AF49438740D8FA81A1FEED7E128CE62C3933CE0FD322AF969CCBD3F0085474BD4A19CE43C37DF16B46FFA439B95B5F667352C97BD4636556C800EFBA66E0FD4F948E62CB689153377D06E36297D902E1D345E6CB5FABD1D6542471EF38554D5049C20734E76FD1753B5C402C791F2121EFE55C9017A6FF230E475B0FAB40BA11"
#znp_atack(2, m)

n_1 = "B69BEEFBCDDD8EDDA32384885080A1B4DA3FEBC55E1DEE0525D247B2C927C4A23F2B5E03FDEABA4014E35738D1971F06F23FC66F348C86E6CA208942C328FC6ECEC78C655601C2A356E80551E43028875FE5678A508D6CA9A24F637DAE40475A3E49C42BA62CE8A41CEDFDCF418FB42703D3CD21FF09AC97077130AB799BA971AF49438740D8FA81A1FEED7E128CE62C3933CE0FD322AF969CCBD3F0085474BD4A19CE43C37DF16B46FFA439B95B5F667352C97BD4636556C800EFBA66E0FD4F948E62CB689153377D06E36297D902E1D345E6CB5FABD1D6542471EF38554D5049C20734E76FD1753B5C402C791F2121EFE55C9017A6FF230E475B0FAB40BA11"
#root
z_1 = "7854799DA983E1C7C25C64CDD7560FC8A9CB7C4C0486BB968A18545AA96327737E18A5206EF3A110203BE74BF985E55977E0A6294201DEF81BC2912DF253987C4F11F60FA393CA3CA05469FFDFDC243CE8D8972AC2E1F488171BCF7EB56EF1DC3A937410E8D01D21F093474ACDF750C3E9D3DA62560A5FECCB435A8D34EBE1295DEC0B8FAE65A8E8837E422FEE1B8D2A65E9A4D7C7A825278ACB2964082A874BA8408D5C791469DA9CA64EFC95AD771C975AF3782578F609ED081BBAAFA75AA9F8D93AECA1CD60EE4F67DF8ABDA2B7ADDE1CB9B9847CAC95E813B2FC17B30703DA906A562AC9A8D5B602F720BC475E9596C95DF8F3C8A196F7AB2E421375E156"
t_1 = 4211105416061048602572707884097930176304504511582736292077891429826519675829637547746237664442842793260262706929299274293087848019013385098895743930422397620418006401696437631948507897184979318987517934048390988501540934273087076300198127298765316669101412861396171495667503569019099567310239036068477123471194124914024807780916258357970111311279408460044508397109823837561863428327376203664209826872554604829670852846093826975503277355890982470952157061992224514359771989356968334632566263734580015021009963514142939443025836063121190958515528462455448845038921070514381987189558983285880114361209195553662375563759
#calculate_p_q(n_1, t_1, z_1)
