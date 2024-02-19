#!/usr/bin/env python3

import ecc
import dh

def test_add():
    """
    Test for EXERCISE 1
    """
    a, b, p = 1, 18, 19
    ec = ecc.EC(a,b,p)
    P, _ = ec.at(7)
    Q, _ = ec.at(13)
    R = ec.add(P,Q)
    assert(R == ecc.Point(8,14))

def test_mul():
    """
    Test for EXERCISE 2
    """
    a, b, p = -3, 0, 137
    ec = ecc.EC(a,b,p)
    n = 15
    P, _ = ec.at(8)
    nP = ec.mul(P,n)
    assert(nP == ecc.Point(93,132))

def test_order():
    """
    Test for EXERCISE 2
    """
    a, b, p = -3, 0, 137
    ec = ecc.EC(a,b,p)
    P, _ = ec.at(0)
    Q, _ = ec.at(14)
    R, _ = ec.at(42)
    assert(ec.order(P) == 2)
    assert(ec.order(Q) == 73)
    assert(ec.order(R) == 146)

def test_dh():
    """
    Test for EXERCISE 3
    """
    a, b, p = -3, 0, 137
    ec = ecc.EC(a,b,p)
    P, _ = ec.at(1)
    dhk = dh.DH(ec,P)
    p = 14
    q = 42
    P = dhk.gen(p)
    Q = dhk.gen(q)
    pQ = dhk.secret(p,Q)
    qP = dhk.secret(q,P)
    assert(pQ == qP)

if __name__ == '__main__':
    test_add() 
    #test_mul()
    #test_order()
    #test_dh()
