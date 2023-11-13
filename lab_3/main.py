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


def server_encryption_example(A: User, S: User, M):
    print("\nEncryption:")
    C, c1, c2 = Encrypt_extended(message=M, user=S)

    print(f"C = {hex(C)}")
    print(f"c1, c2 = {c1}, {c2}")

    DC = Decrypt_extended(y=C, c1=c1, c2=c2, receiver=A) # if encrypted with User A
    print(f"DC = {hex(DC)}\nM  = {hex(M)}")

def server_decryption_example(A: User, S: User, C, c1, c2):
    print("\nDecryption:")
    DC = Decrypt_extended(y=C, c1=c1, c2=c2, receiver=A)
    print(f"DC = {hex(DC)}")

def server_signing_example(A: User, M: int):
    print("\nSigning:")
    sign_ = Sign(message=M, user=A)
    print(f"M = {hex(M)}")
    print(f"S = {hex(sign_)}")

    is_signer = Verify(message=M, sign=sign_, user=A)
    print(f"is_signer = {is_signer}")

def server_verification_example(A: User, sign: int, M: int):
    print("\nVerification:")
    is_signer = Verify(message=M, sign=sign, user=A)
    print(f"is_signer = {is_signer}")

if __name__ == "__main__":
    # Creation of User A
    p = 0x10000000000000000000000000000000000000007
    q = 0x200000000000000000000000000000000000000000bf
    b = 0x196e3afd550e9a849848139d317e6770ba6983cdf6aabdd5a7
    n = 0x2000000000000000000000000000000000000000e0bf0000000000000000000000000000000000000539
    A = User()
    A.set_key(p=p, q=q, b=b)
    print(f"A:\n{A}\n")

    # Creation of User on server
    server_Modulus = 0xBF4C64FD957501B1CCA9D6BA5176B7085E7B1C9529B43220C4D76AFC0DA57EAEDFF4723E41ADD5F276569D6104004E30F71EE9F193FD1E05773D601D669BD6FC03D370EA9D3245BA0B6701
    server_b = 0x2B6DB53370A1AB8650A092F0375C2BAA1B9F919A92CE762C5D3C55AF18CDF7B99DC964F9041BB61874135FB3641EEFB64D1837B1E07CDF55A70EBCEB11FF9306DEDAA6F269F9E5BD2BABB0
    S = User()
    S.set_key_server(n=server_Modulus, b=server_b)
    print(f"S:\n{S}\n")

    # EXAMPLES:

    # # Encryption
    # M = 0x222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222
    # server_encryption_example(A=A, S=S, M=M)

    # Decryption
    # C = 0x36407dd82cebf44e11ab1d53e59abee0eb56bd067c27295445f3bd2b7651f9e53c7bdda8f599ab2
    # c1 = 0
    # c2 = 1
    # server_decryption_example(A=A, S=S, C=C, c1=c1, c2=c2)

    # Signing
    M = 0x22222222222222222222222222222222222222222222222222
    server_signing_example(A=A, M=M)

    # # Verification
    # M = 0x222222222222222222222222222222
    # sign = 0x58A685EB2AF53E4663449BAC3C729959657B7F88E0A088DECE
    # server_verification_example(A=S, sign=sign, M=M)



