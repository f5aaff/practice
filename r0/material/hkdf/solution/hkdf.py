#!/usr/bin/env python3

import math
from sha256 import hexdigest, DIGESTSIZE
from hmac import hmac_sha256

def extract(salt: bytes, ikm: bytes) -> bytes: 
    if len(salt) == 0:
        salt = bytes([0x00] * DIGESTSIZE)
    return hmac_sha256(salt, ikm)

def expand(prk: bytes, info: bytes, l: int) -> bytes:
    t = b''
    okm = b''
    for i in range(math.ceil(l / DIGESTSIZE)):
        t = hmac_sha256(prk, t + info + bytes([1+i]))
        okm += t
    return okm[:l]

def hkdf(salt: bytes, ikm: bytes, info: bytes, l: int) -> bytes:
    prk = extract(salt, ikm)
    return expand(prk, info, l)

if __name__ == '__main__':
    # RFC5869, test case 1
    ikm = bytes([0x0b] * 22)
    salt = bytes([i for i in range(13)])
    info = bytes([0xf0 + i for i in range(10)])
    l = 42
    assert('3cb25f25faacd57a90434f64d0362f2a2d2d0a90cf1a5a4c5db02d56ecc4c5bf34007208d5b887185865' == hexdigest(hkdf(salt, ikm, info, l)))

    # RFC5869, test case 2
    ikm = bytes([i for i in range(80)])
    salt = bytes([0x60 + i for i in range(80)])
    info = bytes([0xb0 + i for i in range(80)])
    l = 82
    assert('b11e398dc80327a1c8e7f78c596a49344f012eda2d4efad8a050cc4c19afa97c59045a99cac7827271cb41c65e590e09da3275600c2f09b8367793a9aca3db71cc30c58179ec3e87c14c01d5c1f3434f1d87' == hexdigest(hkdf(salt, ikm, info, l)))

    # RFC5869, test case 3
    ikm = bytes([0x0b] * 22)
    salt = b''
    info = b''
    l = 42
    assert('8da4e775a563c18f715f802a063c5a31b8a11f5c5ee1879ec3454e5f3c738d2d9d201395faa4b61a96c8' == hexdigest(hkdf(salt, ikm, info, l)))

    print('ok')
