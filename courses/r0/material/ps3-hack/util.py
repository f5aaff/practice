#!/usr/bin/env python3

# Compute t = a^{-1} mod n using the Extended Euclidean Algorithm
def invert(a, n):
    t, new_t = 0, 1
    r, new_r = n, a
    while new_r > 0:
        q = r // new_r
        t, new_t = new_t, t - q * new_t
        r, new_r = new_r, r - q * new_r
    if r > 1:
        raise Exception('Value not invertible')
    if t < 0:
        t = t + n
    return t
