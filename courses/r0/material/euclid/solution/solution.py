#!/usr/bin/env python3

def invert(a, n):
    """
    Computes t = a^{-1} mod n using the Extended Euclidean Algorithm
    """
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

def test_invert():
    a = 7
    t = 98
    n = 137
    assert(t == invert(a,n))
    a = 7
    t = 882283
    n = 1543995
    assert(t == invert(a,n))
    a = 7
    t = 2300875338
    n = 3 * 2**30 + 1
    assert(t == invert(a,n))

if __name__  == '__main__':
    test_invert()
    print('ok')
