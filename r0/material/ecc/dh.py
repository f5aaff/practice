#!/usr/bin/env python3

import ecc

class DH(object):
    """Elliptic Curve Diffie Hellman (Key Agreement)
    - ec: elliptic curve
    - g: a point on ec
    """
    def __init__(self, ec, g):
        """
        EXERCISE 3
        """
        pass

    def gen(self, priv):
        """generate pub key"""
        assert 0 < priv and priv < self.n
        """
        EXERCISE 3
        """
        pass

    def secret(self, priv, pub):
        """calc shared secret key for the pair
        - priv: my private key as int
        - pub: partner pub key as a point on ec
        - returns: shared secret as a point on ec
        """
        assert self.ec.is_valid(pub)
        assert self.ec.mul(pub, self.n) == self.ec.zero
        """
        EXERCISE 3
        """
        pass
