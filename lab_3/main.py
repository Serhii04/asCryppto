import random

from algorithms import *

def encrypt_decrypt_example():
    # M = random.randint(pow(2, 64), pow(2, 301))
    A = User()

    print("A:")
    print(A)
    print("")

    M = 0x1c52b6d7d64cc3b91b8485c8159495ebb341c8e63b5041bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
    print(f"M  = {hex(M)}")

    C, C1, C2 = Encrypt(message=M, user=A)
    print(f"C  = {hex(C)}")

    DC = Decrypt(c1=C1, c2=C2, y=C, p=A.p, q = A.q)
    print(f"DC = {hex(DC)}")
    print(f"M  = {hex(M)}")

def verification_example():
    A = User()

    p = 0xfffffffc0000000000000000000000000000000000000000000000000000023f
    q = 0xfffffffffffffffffffffffffffffffff000000000000000000000000000002f
    A.set_key(p=p, q=q)

    print("A:")
    print(A)
    print("")

    # M = 0x1c52b6d7d64cc3b91b8485c8159495eb2d4733611638a7b341c8e63b5041bbad4b83b2abc019
    M = random.randint(pow(2, 64), pow(2, 301))
    print(f"M  = {hex(M)}")
    S = Sign(message=M, user=A)
    print(f"S  = {hex(S)}")

    sign_is_correct = Verify(message=M, sign=S, user=A)
    print(f"sign_is_correct = {sign_is_correct}")



# def main3():
#     A = User()

#     A.set_key_server(n=0xCD845B043FE28EA28ADA650F405B0F860FEACDFA7009B597B4DC41A9945EA025)
    
#     M = 0x1c52b6d7d64cc3b91b8485c8159495eb2
#     print(f"M  = {hex(M)}")

#     C, C1, C2 = Encrypt(message=M, user=A)
#     print(f"C  = {hex(C)}")

#     DC = Decrypt(c1=C1, c2=C2, y=C, p=A.p, q = A.q)
#     print(f"DC = {C1}, {C2}, {hex(DC)}")
#     print(f"M  = {hex(M)}")

# def main4():
#     from collections import defaultdict
#     vals = defaultdict(int)
#     for i in range(100):
#         a, b = GenerateKeyPair()

#         vals[a] += 1
#         vals[b] += 1

#     for key in vals:
#         print(f"{vals[key]} n umbers of {key}")

if __name__ == "__main__":
    # encrypt_decrypt_example()
    verification_example()


