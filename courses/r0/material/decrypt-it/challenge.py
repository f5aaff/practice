#!/usr/bin/env python

import os
import sys
import hashlib
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend


def encrypt(key, iv, plaintext):
    assert len(key) == 8 
    assert len(iv) == 8 
    assert (len(plaintext) % 8) == 0
    cipher = Cipher(algorithms.CAST5(key), modes.CBC(iv), backend=default_backend())
    enc = cipher.encryptor()
    return enc.update(plaintext) + enc.finalize()

def decrypt(key, iv, ciphertext):
    assert len(key) == 8 
    assert len(iv) == 8 
    assert (len(ciphertext) % 8) == 0
    cipher = Cipher(algorithms.CAST5(key), modes.CBC(iv), backend=default_backend())
    dec = cipher.decryptor()
    return dec.update(ciphertext) + dec.finalize()

def xor(in1, in2, out=[]):
    out.append(bytes([_i1 ^ _i2 for _i1, _i2 in zip(in1,in2)]))
    return b''.join(out)

class PRNG(object):

    def __init__(self):
        self.key = b'\x00'*8
        self.iv = b'\x00'*8
        salt_init = b'\x8a\x37\xb1\x0f\xaa\x91\x7e\x01'

        pid = b'%07d' % os.getpid()
        salt = xor(salt_init, pid)

        ent1 = hashlib.sha256(salt).digest()
        ent2 = os.urandom(32)
        ent3 = xor(ent1, ent2)

        # initialize 32B state 
        self.state = ent3
        self.__update()

    def __update(self):
        mask = encrypt(self.key, self.iv, self.state[:32])
        self.state = xor(mask, self.state, [])

    def get_bytes(self, nbbytes):
        randbytes = self.state[:nbbytes]
        self.__update()
        return randbytes


def main():
    prng = PRNG()
    key = prng.get_bytes(8)
    print("key:",key.hex())
    iv = b'\x00' * 8
    plaintext = open('plaintext').read().rstrip('\n')
    ciphertext = encrypt(key, iv, bytes(plaintext, 'utf-8'))
    print(ciphertext.hex())


if __name__ == '__main__':
    main()
