#!/usr/bin/env python3

# our team implemented the proof of factorization knowkedge in the paper
# proofs.pdf (Theorem1), a zero-knowledge proof that the prover knows
# the factors p and q of N=pq; the verifier checking the proof must be
# convinced (returning true) without having access to the factors, and a
# valid proof should be impossible to forge without the prime factors (as
# the paper demonstrates)

# your task: create a proof of factorization knowledge of the number
# CHALLENGE_N below

CHALLENGE_N = 8230275019648071635976621698648611597104088707798353808582210367936241810321357560733873829473259428860371610131123775877962208302583873890253393828866133

import secrets

def prover(p, q):
    N = p*q
    phi = (p-1)*(q-1)
    M = pow(N, -1, phi)
    x = secrets.randbelow(N)
    y = pow(x, M, N)
    print("Proof created for ", N)
    return (N,x,y)

def verifier(proof):
    (N,x,y) = proof
    if pow(y,N,N) == x:
        print("Valid proof of factorization knowledge for ", N)
        return True
    print("Invalid proof")
    return False


if __name__ == "__main__":
    # example
    # p = 87920896289820519685067635021628469007019663145303772183616841098707415560303
    # q = 90247437994415005138189630748900624515162806286986669443993813007560238526463
    # proof = prover(p, q)
    # verifier(proof)
     
    # forgery of a proof for CHALLENGE_N
    y = secrets.randbelow(CHALLENGE_N)
    x = pow(y,CHALLENGE_N,CHALLENGE_N)
    proof = (CHALLENGE_N,x,y)
    verifier(proof)

    
