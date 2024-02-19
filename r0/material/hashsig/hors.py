#!/usr/bin/env python3

# we started implemented the post-quantum signature scheme HORS, described in 
# https://www.cs.bu.edu/~reyzin/papers/one-time-sigs.pdf (Figure 1)
# 
# however, we didn't have time to finish, and the verification remains
# to be done; can you write it in such a way that it returns True upon
# signatures generated by HORS_Sign(), and False otherwise?

import hashlib
import secrets

# using parameters (l, k, t) = (80, 20, 256), as suggested in the paper

L=80
K=20
T=256
LOGT=8

def HORS_KeyGen():
    sk = []
    pk = []
    for i in range(T):
        # generate a random string as a secret key element
        k = secrets.token_bytes(int(L/8))
        sk.append(k) 
        
        # hash the secret key element to make if part of the pubkey
        h = hashlib.blake2b(k).digest()
        pk.append(h)

    return sk, pk

def HORS_Sign(sk, m):
    h = hashlib.blake2b(m).digest()
    sig = []

    for i in range(K):
        sig.append(sk[ h[i] ])

    return sig

def HORS_Verify(pk, m, sig):
    # IF (SIGNATURE INVALID): return False
    # return True
    pass

if __name__ == "__main__":
    # example
    sk, pk = HORS_KeyGen()
    m = b"hello"
    print("SK (first 3 elements): ", sk[:3])
    print("\nPK (first 3 elements): ", pk[:3])
    sig = HORS_Sign(sk, m)
    print("\nsig: ", sig)
    HORS_Verify(pk, m, sig)
    
