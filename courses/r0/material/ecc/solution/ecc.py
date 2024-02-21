#!/usr/bin/env python3

import collections
import random
import math

Point = collections.namedtuple("Point", ["x", "y"])

def inv(n, q):
    """div on PN modulo a/b mod q as a * inv(b, q) mod q
    >>> assert n * inv(n, q) % q == 1
    """
    # n*inv % q = 1 => n*inv = q*m + 1 => n*inv + q*-m = 1
    # => egcd(n, q) = (inv, -m, 1) => inv = egcd(n, q)[0] (mod q)
    return egcd(n, q)[0] % q

def egcd(a, b):
    """extended GCD
    returns: (s, t, gcd) as a*s + b*t == gcd
    >>> s, t, gcd = egcd(a, b)
    >>> assert a % gcd == 0 and b % gcd == 0
    >>> assert a * s + b * t == gcd
    """
    s0, s1, t0, t1 = 1, 0, 0, 1
    while b > 0:
        q, r = divmod(a, b)
        a, b = b, r
        s0, s1, t0, t1 = s1, s0 - q * s1, t1, t0 - q * t1
        pass
    return s0, t0, a

def sqrt_naive(n, q):
    """sqrt on PN modulo: returns two numbers or exception if not exist
    >>> assert (sqrt(n, q)[0] ** 2) % q == n
    >>> assert (sqrt(n, q)[1] ** 2) % q == n
    """
    assert n < q
    for i in range(0, q):
        if (i * i) % q == n:
            return (i, -i % q)
        pass
    raise Exception("not found")

def sqrt_random(n, q):
    """sqrtmod for bigint (randomized)
    - algorithm 3.34 of http://www.cacr.math.uwaterloo.ca/hac/about/chap3.pdf
    """
    # b: some non-quadratic-residue
    b = 0 
    while b == 0 or jacobi(b, q) != -1:
        b = random.randint(1, q - 1)
        pass
    # q = t * 2^s + 1, t is odd
    t, s = q - 1, 0 
    while t & 1 == 0:
        t, s = t >> 1, s + 1
        pass
    assert q == t * pow(2, s) + 1 and t % 2 == 1
    ni = inv(n, q)
    c = pow(b, t, q)
    r = pow(n, (t + 1) // 2, q)
    for i in range(1, s):
        d = pow(pow(r, 2, q) * ni % q, pow(2, s - i - 1, q), q)
        if d == q - 1: r = r * c % q
        c = pow(c, 2, q)
        pass
    return (r, q - r)

def jacobi(a, q):
    """quick jacobi symbol
    - algorithm 2.149 of http://www.cacr.math.uwaterloo.ca/hac/about/chap2.pdf
    """
    if a == 0: return 0
    if a == 1: return 1
    a1, e = a, 0
    while a1 & 1 == 0:
        a1, e = a1 >> 1, e + 1
        pass
    m8 = q % 8
    s = -1 if m8 == 3 or m8 == 5 else 1 # m8 = 0,2,4,6 and 1,7
    if q % 4 == 3 and a1 % 4 == 3: s = -s
    return s if a1 == 1 else s * jacobi(q % a1, a1)

sqrt = sqrt_naive

class EC(object):
    """System of Elliptic Curve"""
    def __init__(self, a, b, q):
        """elliptic curve as: (y**2 = x**3 + a * x + b) mod q
        - a, b: params of curve formula
        - q: prime number
        """
        assert q > 2 
        assert (4 * ( (a % q) ** 3) + 27 * ((b % q) ** 2)) % q != 0
        self.a = a % q
        self.b = b % q
        self.q = q
        # just as unique ZERO value representation for "add": (not on curve)
        self.zero = Point(None, None)
        pass

    def is_valid(self, p):
        if p == self.zero: return True
        l = (p.y ** 2) % self.q
        r = ((p.x ** 3) + self.a * p.x + self.b) % self.q
        return l == r

    def at(self, x):
        """find points on curve at x
        - x: int < q
        - returns: ((x, y), (x,-y)) or not found exception
        >>> a, ma = ec.at(x)
        >>> assert a.x == ma.x and a.x == x
        >>> assert a.x == ma.x and a.x == x
        >>> assert ec.neg(a) == ma
        >>> assert ec.is_valid(a) and ec.is_valid(ma)
        """
        assert x < self.q
        ysq = (x ** 3 + self.a * x + self.b) % self.q
        y, my = sqrt(ysq, self.q)
        return Point(x, y), Point(x, my)

    def neg(self, p):
        """negate p
        >>> assert ec.is_valid(ec.neg(p))
        """
        return Point(p.x, -p.y % self.q)

    def add(self, p1, p2):
        """<add> of elliptic curve: negate of 3rd cross point of (p1,p2) line
        >>> d = ec.add(a, b)
        >>> assert ec.is_valid(d)
        >>> assert ec.add(d, ec.neg(b)) == a
        >>> assert ec.add(a, ec.neg(a)) == ec.zero
        >>> assert ec.add(a, b) == ec.add(b, a)
        >>> assert ec.add(a, ec.add(b, c)) == ec.add(ec.add(a, b), c)
        """
        if p1 == self.zero: 
            return p2
        if p2 == self.zero: 
            return p1
        if p1.x == p2.x and p1.y == -p2.y % self.q:
            # p1 + -p1 == 0
            return self.zero
        if p1.x == p2.x and p1.y == p2.y:
            # p1 + p1: use tangent line of p1 as (p1,p1) line
            l = (3 * p1.x * p1.x + self.a) * inv(2 * p1.y, self.q) % self.q
            pass
        else:
            l = (p2.y - p1.y) * inv(p2.x - p1.x, self.q) % self.q
            pass
        x = (l * l - p1.x - p2.x) % self.q
        y = (l * (p1.x - x) - p1.y) % self.q
        return Point(x, y)

    def mul(self, p, n):
        """n times <mul> of elliptic curve
        >>> m = ec.mul(p, n)
        >>> assert ec.is_valid(m)
        >>> assert ec.mul(p, 0) == ec.zero
        """
        r = self.zero
        m2 = p
        # O(log2(n)) add
        while 0 < n:
            if n & 1 == 1:
                r = self.add(r, m2)
                pass
            n, m2 = n >> 1, self.add(m2, m2)
            pass
        # [ref] O(n) add
        #for i in range(n):
        #    r = self.add(r, p)
        #    pass
        return r

    def order(self, g):
        """order of point g
        >>> o = ec.order(g)
        >>> assert ec.is_valid(a) and ec.mul(a, o) == ec.zero
        >>> assert o <= ec.q
        """
        assert self.is_valid(g)
        if g == self.zero:
            return 1
        for i in range(1, self.q + 1 + 2 * int(math.ceil(math.sqrt(self.q)))):
            if self.mul(g, i) == self.zero:
                return i
            pass
        raise Exception("Invalid order")
    pass

