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


def server_encryption_example(A: User, S: User, message: int):
    return Encrypt_extended(message=message, user=A)

if __name__ == "__main__":
    p = 0xfffffffc0000000000000000000000000000000000000000000000000000023f
    q = 0xfffffffffffffffffffffffffffffffff000000000000000000000000000002f
    b = 0x196e3afd550e9a849848139d317e6770ba6983cdf6aabdd5a7
    A = User()
    A.set_key(p=p, q=q, b=b)

    server_Modulus = 0xF2DEADB4AFA077EC3BDB59FEA0DBB5DF2765CF98D559DBC199
    server_b = 0x196e3afd550e9a849848139d317e6770ba6983cdf6aabdd5a7
    S = User()
    S.set_key_server(n=server_Modulus, b=server_b)

    print("A:")
    print(A)
    print("")

    print("S:")
    print(S)
    print("")


    M = 0x222222222222222222222222222222222222222222222222222222222222222222222222
    C, c1, c2 = server_encryption_example(A=A, S=S, message=M)

    print(f" C = {hex(C)}")
    print(f" c1, c2 = {c1}, {c2}")



