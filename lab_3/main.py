import random

from algorithms import *

def server_encryption_example(S: User, M):
    print("\nEncryption:")
    C, c1, c2 = Encrypt_extended(message=M, user=S)

    print(f"C = {hex(C)}")
    print(f"c1, c2 = {c1}, {c2}")

    return C, c1, c2

def server_decryption_example(A: User, C, c1, c2):
    print("\nDecryption:")
    DC = Decrypt_extended(y=C, c1=c1, c2=c2, receiver=A)
    print(f"DC = {hex(DC)}")

    return DC

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
    print(f"sign = {hex(sign)}")
    print(f"sign is correct: {is_signer}")

if __name__ == "__main__":
    # Creation of User A
    p = 0xe000d2a4419b4d74cc2cdd5ae91353990318e5dc55b3413bc39a1fd9fa2683
    q = 0x74fd4c7ff8d93cddb1b01b422eb9bfebb5a6b3eec43e09d6463f97af921f83
    b = 0x65239AE0179883F44EA353D66526BB90EE30B9697AD1230504BC33CC210FDE31
    n = 0x665e0332d2bf5a8efa55471bc90d7864b184496373d3320b5c67e710a7eced878d1e583077d639157ee03523cf8fcb83ea0fa143f7291cc6fef459619209
    A = User()
    A.set_key(p=p, q=q, b=b)
    print(f"A:\n{A}\n")

    # Creation of User on server
    server_Modulus = 0xADB788A04FD1BBAEC54762A1D24DA98DD3E5881C978B87D516DF2AEF000DB4E27F8EB5FAF23CB7486AFAAE2B0C95D7C2C211
    server_b = 0x55E607FA2380F8872F79580EAEB1E22CFC7FC91554F4962266C2FD782542EE8A4CC59788AFFCEE68CF1D2C851C6E7574A749
    S = User()
    S.set_key_server(n=server_Modulus, b=server_b)
    print(f"S:\n{S}\n")

    # EXAMPLES:

    # Encryption
    M = 0x2222222222222222222222
    server_encryption_example(S=S, M=M)

    # # Decryption
    # C = 0x61F427F52A9C87465C1F003357FD294161BA27E33486E2D61CADAEBB8B521CCE77121222F71F65B30E8095C513B9B6945B5E50E6A65CB429DB92E028515F
    # c1 = 0
    # c2 = 1
    # server_decryption_example(A=A, C=C, c1=c1, c2=c2)

    # # Signing
    # M = 0x22222222222222222222222222222222222222222222222222
    # server_signing_example(A=A, M=M)

    # # Verification
    # M = 0x222222222222222222222222222222
    # sign = 0x2FFC3E8E661F24606BB12C3E9280BC616083F7AA744ED2581CC0972FFB83AAB475829F9B3CC03F82EE46A4EC27BDEC5B1C45
    # server_verification_example(A=S, sign=sign, M=M)

