import random

from algorithms import User, Encrypt, Decrypt, Sign, Verify, SendKey, ReceiveKey

def abonent_example():
    A = User()
    n, e = A.open_key()
    d = A.secret_key()
    
    print(f"n = {hex(n)}")
    print(f"e = {hex(e)}")
    print(f"d = {hex(d)}")

    M = random.randint(pow(2, 400), pow(2, 500))
    print(f"M = {hex(M)}")

    C = Encrypt(message=M, user=A)
    print(f"C = {hex(C)}")
    DC = Decrypt(message=C, user=A)
    print(f"DC = {hex(DC)}")
    print(f"M  = {hex(M)}")

    M_sign = Sign(message=M, user=A)
    print(f"M_sign = {hex(M_sign)}")
    is_corect = Verify(message=M, signed_message=M_sign, user=A)
    print(f"is_corect = {is_corect}")

def sort_users(A: User, B: User):
    n1, e1 = A.open_key()
    n2, e2 = B.open_key()

    if n1 > n2:
        return B, A
    
    return A, B

def key_excange_example():
    A = User()
    B = User()

    A, B = sort_users(A, B)

    k_max = min((A.open_key())[0], (B.open_key())[0]) - 1
    k = random.randint(1, k_max)

    k1, S1 = SendKey(sender=A, receiver=B, k=k)
    received_key = ReceiveKey(sender=A, receiver=B, k1=k1, S1=S1)
    print(f"k  = {k}")
    print(f"rk = {received_key}")


def main():
    abonent_example()

    print("")

    key_excange_example()

if __name__ == "__main__":
    main()

