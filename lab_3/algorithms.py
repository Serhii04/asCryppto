import random
import math

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

def get_prime_number_blum_part_in_interval(start: int, end: int=None) -> int:
    if end is None:
        end = 2 * start - 2

    m_0 = start + 3 - (start % 4)

    # for p in range(m_0, end, 2):
    p = m_0
    while True:
        if is_prime(p):
            if __FLOOD__MODE__:
                print(f"Number {p} is prime")
            
            if not is_blum_number(p):
                raise ValueError("error p is not blum prime")

            return p
        
        if __FLOOD__MODE__:
            print(f"Number {p} isn't prime")

        p += 4
        
def get_prime_number_blum_part_of_lenght(l: int) -> int:
    p = 0
    B = 1

    for i in range(l-1):
        b = (random.randbytes(n=1))[0]
        
        if b:
            p += B
        
        B *= 2

    p += B  # because we need number that have l or more bits

    return get_prime_number_blum_part_in_interval(start=p, end=2 * p - 2)

# ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def format_message(message: int, n: int):
    l = n.bit_length() // 8 + (n % 8 > 0)

    # if message.bit_length() // 8 >= l - 10:
    #     raise ValueError("Very long message")
    
    r = random.randint(0, pow(2, 64) - 1)

    x = 255 * pow(2, 8 * (l - 8)) + message * pow(2, 64) + r

    return x

def Jacobi_symbol(a, n):
    return _Jacobi_symbol(n=a, k=n) 

def _Jacobi_symbol(n, k):
    """wikipedias_jacobi"""
    assert(k > 0 and k % 2 == 1)
    
    n = n % k
    t = 1
    while n != 0:
        while n % 2 == 0:
            n = n / 2
            r = k % 8
            if r == 3 or r == 5:
                t = -t
        
        n, k = k, n
        if n % 4 == 3 and k % 4 == 3:
            t = -t
        
        n = n % k
    
    if k == 1:
        return t
    else:
        return 0

def __Jacobi_symbol_mine(a: int, n: int) -> int:
    """Mathmatical funtion to find Jacobi symbol value. It says

    Args:
        a (int): a is natural number.
        n (int): n is natural number that isn't divides by 2.

    Returns:
        int: Jacobi symbol value.
    """

    if n <= 0:
        raise ValueError("ERROR in Jacobi_symbol: n must be natural number.")
    
    if n % 2 == 0:
        raise ValueError("ERROR in Jacobi_symbol: n must be odd.")
    
    a = a % n
    
    rez = 1

    while a != 0:
        while a % 2 == 0:
            if ((n*n - 1) / 8) % 2 == 1: 
                rez *= -1
            a = a // 2

        if a == 1:
            return rez
        
        if a == -1:
            if ((n - 1) / 2) % 2 == 1: 
                rez *= -1
            return rez        

        if ((a - 1) * (n - 1) // 4) % 2 == 1: 
            rez *= -1

        a, n = n % a, a

    return 0

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
    def __init__(self, p: int=None, q: int=None):
        if p is None and q is None:
            p, q = GenerateKeyPair()

        if p is None or q is None:
            raise ValueError(F"None value is gieven")

        self.set_key(p=p, q=q)
    
    def set_key(self, p: int, q: int) -> None:
        self.n = p * q
        self.p = p
        self.q = q


    def set_key_server(self, n: int) -> None:
        self.n = n

    def open_key(self) -> int:
        return self.n
    
    def secret_key(self) -> (int, int):
        return self.p, self.q
    
    def __str__(self) -> str:
        return f"p = {hex(self.p)},\nq = {hex(self.q)},\nn = {hex(self.n)}"

def calc_aditional_bits(x: int, n: int) -> (int, int):
    c1 = x % 2
    c2 = 0
    if Jacobi_symbol(a=x, n=n) == 1:
        c2 = 1
    
    return c1, c2

def Encrypt(message: int, user: User) -> int:
    n = user.open_key()
    x = message

    if x < math.sqrt(n):
        print("Message is small")
    
    if x > n:
        print("Message is big")

    y = pow(x, 2, n)

    c1, c2 = calc_aditional_bits(x=x, n=n)

    return y, c1, c2

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

def Decrypt(y: int, c1: int, c2: int, p: int, q: int) -> int:
    n = p * q

    y_sqrt = get_four_square_roots(y=y, p=p, q=q)

    if __FLOOD__MODE__:
        for y_i in y_sqrt:
            print(f"yi = {hex(y_i)}")

    for y_i in y_sqrt:
        cc1, cc2 = calc_aditional_bits(x=y_i, n=n)

        if cc1 == c1 and cc2 == c2:
            return y_i

def Sign(message: int, user: User) -> int:
    n = user.open_key()
    p, q = user.secret_key()

    x = format_message(message=message, n=n)
    while Jacobi_symbol(a=x, n=p) != 1 or Jacobi_symbol(a=x, n=q) != 1:
        x = format_message(message=message, n=n)

    x_sqrt = get_four_square_roots(y=x, p=p, q=q)
    rch = random.choice(x_sqrt)  # rch^2 = x (mod pq)

    return rch

def Verify(message: int, sign: int, user: User) -> bool:
    n = user.open_key()

    x_ = pow(sign, 2, n)

    some_form_mess = format_message(message=message, n=n)
    if (x_ >> 64) == (some_form_mess >> 64):
        return True
    
    return False

# def SendKey() -> (int, int):
#     pass

# def ReceiveKey() -> int:
#     pass




