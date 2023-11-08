import random

import algorithms as alg



def abonent_example():
    A = alg.User()
    if alg.__FLOOD__MODE__:
        print("A:")
        print(A)

    n, e = A.open_key()
    d = A.secret_key()

    if not alg.__FLOOD__MODE__:
        print("A:")
        print(f"n = {hex(n)}")
        print(f"e = {hex(e)}")
        print(f"d = {hex(d)}")
    
    print("")

    print("Encrypting example")
    M = random.randint(pow(2, 400), pow(2, 500))
    print(f"M = {hex(M)}")

    C = alg.Encrypt(message=M, user=A)
    print(f"C = {hex(C)}")
    DC = alg.Decrypt(message=C, user=A)
    print(f"DC = {hex(DC)}")
    print(f"M  = {hex(M)}")

    M_sign = alg.Sign(message=M, user=A)
    print(f"M_sign = {hex(M_sign)}")
    is_corect = alg.Verify(message=M, signed_message=M_sign, user=A)
    print(f"is_corect = {is_corect}")

def sort_users(A: alg.User, B: alg.User):
    n1, e1 = A.open_key()
    n2, e2 = B.open_key()

    if n1 > n2:
        print("A and B are swaped because n1 must be > n")
        return B, A
    
    return A, B

def key_excange_example():
    A = alg.User()
    B = alg.User()

    if alg.__FLOOD__MODE__:
        print("A:")
        print(A)
        print("\nB:")
        print(B)
    
    if not alg.__FLOOD__MODE__:
        print("A:")
        n, e = A.open_key()
        d = A.secret_key()
        print(f"n = {hex(n)}")
        print(f"e = {hex(e)}")
        print(f"d = {hex(d)}")
        print("B:")
        n, e = B.open_key()
        d = B.secret_key()
        print(f"n = {hex(n)}")
        print(f"e = {hex(e)}")
        print(f"d = {hex(d)}")

    A, B = sort_users(A, B)

    print("\nExchange example:")
    k_max = min((A.open_key())[0], (B.open_key())[0]) - 1
    k = random.randint(1, k_max)

    k1, S1 = alg.SendKey(sender=A, receiver=B, k=k)
    received_key = alg.ReceiveKey(sender=A, receiver=B, k1=k1, S1=S1)
    print(f"k  = {k}")
    print(f"rk = {received_key}")


def main():
    abonent_example()

    print("")

    key_excange_example()

if __name__ == "__main__":
    main()

