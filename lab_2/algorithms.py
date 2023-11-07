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
    if start % 2 == 0:
        start += 1

    for p in range(start, end, 2):
        print(p)
        if is_prime(p):
            return p
        
# def get_prime_number_with_lenght(l: int) -> int:
#     p = 0
#     B = 1

#     gen = gn.BuildInGenerator()
#     for i in range(l):
#         b = (gen.next())[0]
        
#         if b:
#             p += B
        
#         B *= 2

#     return p


def main():
    print(18, is_prime(p=18))
    print(17, is_prime(p=17))
    print(5783, is_prime(p=5783))
    print(5782, is_prime(p=5782))
    print(5789, is_prime(p=5789))

if __name__ == "__main__":
    main()