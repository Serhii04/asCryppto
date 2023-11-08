import numpy
import random
import math

import generator as gn


__SMALL_PRIMES__ = [2, 3, 5, 7, 11, 13, 17, 19, 23]

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

    # print(f"x = {x}, s = {s}, d = {d}, pow = {pow(x, d, p)}")

    temp_x = pow(x, d, p)
    if temp_x == 1 or temp_x == p - 1:
        return True
    
    for r in range(1, s):
        temp_x = pow(temp_x, 2, p)
        # print(temp_x)

        if temp_x == p - 1:
            return True
        
        if temp_x == 1:
            return False
        
    return False


def Miller_Rabin_test_once(p: int) -> bool:
    x = random.randint(a=2, b=(p - 1))

    if gcd(x, p) > 1:
        # print(f"gcd({x}, {p}) > 1 ({gcd(x, p)})")
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
            # print("flssss")
            return False
    
    return Miller_Rabin_test(p=p, k=int(math.log(p)))

def get_prime_number_in_interval(start: int, end: int) -> int:
    m_0 = start
    if start % 2 == 0:
        m_0 += 1

    # for p in range(m_0, end, 2):
    p = m_0
    while True:
        if is_prime(p):
            return p

        p += 2
        
def get_prime_number_of_lenght(l: int) -> int:
    p = 0
    B = 1

    gen = gn.BuildInGenerator()
    for i in range(l-1):
        b = (gen.next())[0]
        
        if b:
            p += B
        
        B *= 2

    p += B  # because we need number that have l or more bits

    return get_prime_number_in_interval(start=p, end=2 * p - 2)

def GenerateKeyPair(l: int=256):
    p = get_prime_number_of_lenght(l)
    q = get_prime_number_of_lenght(l)

    return p, q

class User:
    def __init__(self, p: int=None, q: int=None):
        if p is None and q is None:
            p, q = GenerateKeyPair()

        if p is None or q is None:
            raise ValueError(F"None value is gieven")

        self.set_key(p=p, q=q)
    
    def set_key(self, p: int, q: int):
        self.n = p * q

        phi = (p - 1) * (q - 1)

        self.e = random.randint(2, phi - 1)
        
        while gcd(self.e, phi) != 1:
            self.e = random.randint(2, phi - 1)

        self.d = pow(self.e, -1, phi)

    def open_key(self):
        return self.n, self.e
    
    def secret_key(self):
        return self.d
    
    def send_key(self, k: int, n1: int, e1: int):
        k1 = pow(k, e1, n1)
        S = pow(k, self.d, self.n)
        S1 = pow(S, e1, n1)

        return k1, S1
    
    def receive_key(self, k1, S1, e, n):
        k = pow(k1, self.d, self.n)
        S = pow(S1, self.d, self.n)
    
        return k == pow(S, e, n)
    
    def __str__(self):
        return f"n = {self.n},\n e = {self.e},\n d = {self.d}"

def Encrypt(message: int, user: User):
    n, e = user.open_key()

    if message < 0 or message > n - 1:
        raise ValueError(f"Message should be smaller than n value: M = {message}, n = {n}")
    
    return pow(message, e, n)

def Decrypt(message: int, user: User):
    n, e = user.open_key()
    d = user.secret_key()

    if message < 0 or message > n - 1:
        raise ValueError(f"Message should be smaller than n value: M = {message}, n = {n}")
    
    return pow(message, d, n)

def Sign(message: int, user: User):
    n, e = user.open_key()
    d = user.secret_key()

    if message < 0 or message > n - 1:
        raise ValueError(f"Message should be smaller than n value: M = {message}, n = {n}")
    
    return pow(message, d, n)

def Verify(message: int, signed_message: int, user: User):
    n, e = user.open_key()
    
    return pow(signed_message, e, n) == message

def SendKey(sender: User, receiver: User, k: int):
    n, e = sender.open_key()
    d = sender.secret_key()

    n1, e1 = receiver.open_key()
    
    k1 = pow(k, e1, n1)
    S = pow(k, d, n)
    print(f"S  = {S}")
    S1 = pow(S, e1, n1)

    return k1, S1

def ReceiveKey(sender: User, receiver: User, k1: int, S1: int):
    n, e = sender.open_key()

    n1, e1 = receiver.open_key()
    d1 = receiver.secret_key()

    k = pow(k1, d1, n1)
    S = pow(S1, d1, n1)

    ps = pow(S, e, n)
    if k == pow(S, e, n):
        return k

    print(f"PS = {ps}")
    print(f"tk = {k}")
    return None

    