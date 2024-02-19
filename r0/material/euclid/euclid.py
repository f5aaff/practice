#!/usr/bin/env python3

def invert(a, n):
    """
    EXERCISE: Implement t = a^{-1} mod n using the Extended Euclidean Algorithm
    """

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
