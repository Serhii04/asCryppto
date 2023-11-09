import random

import algorithms as alg

def main():
    # print(alg.get_prime_number_blum_in_interval(start=12123, end=12345432))

    M = 2134556543
    A = alg.User()

    C, C1, C2 = alg.Encrypt(message=M, user=A)

    DC = alg.Decrypt(c1=C1, c2=C2, y=C, p=A.p, q = A.q)
    print(f"DC = {hex(DC)}")
    print(f"M  = {hex(M)}")

if __name__ == "__main__":
    main()