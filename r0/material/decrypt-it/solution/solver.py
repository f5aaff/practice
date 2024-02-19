#!/usr/bin/env python

import os
import sys
import hashlib
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

"""
trick: python's mutable default arguments, cf.
http://stackoverflow.com/questions/101268/hidden-features-of-python#113198

what happens: 
* the first xor modifies the default output list to PID^salt_init; 

* this value gets prepended to the result of the subsequent xor between
  ent1 and ent2.

* then an 8-byte key is generated from the 32-byte state

* these 8 bytes depend only on the first 8 bytes of the state, which
  consist of the PID (first 7 bytes) followed by a random byte

* actual entropy of the key is thus only 23 bits: 15 bits (max pid is
  32768) + 8 bits, which can be bruteforced

"""

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


class PRNG2(object):

    def __init__(self, apid, abyte):
        self.key = b'\x00'*8
        self.iv = b'\x00'*8
        salt_init = b'\x8a\x37\xb1\x0f\xaa\x91\x7e\x01'

        pid = b'%07d' % apid
        salt = xor(salt_init, pid, [])

        ent3 = b''.join([salt, abyte, os.urandom(24)])

        self.state = ent3
        self.__update()

    def __update(self):
        mask = encrypt(self.key, self.iv, self.state[:32])
        self.state = xor(mask, self.state, [])

    def get_bytes(self, nbbytes):
        randbytes = self.state[:nbbytes]
        self.__update()
        return randbytes

def solve(ciphertext):
    iv = b'\x00' * 8
    
    # bruteforce PID
    # to take a shortcut, use (say) range(32769)[1300:]:
    for pid in range(32769)[1300:]:
        print('searching PID %d' % pid)
        for abyte in range(256):
            prng = PRNG2(pid, bytes([abyte]))
            key = prng.get_bytes(8)
            plaintext = decrypt(key, iv, ciphertext)
            if plaintext[:8] == b'the flag':
                print('key: ', key.hex())
                print('plaintext: ', plaintext)
                return

if __name__ == '__main__':

    c = 'b137691a2d51246574951d6512dc7592655f7aca45b87d7e'
    ciphertext = bytes.fromhex(c)
    solve(ciphertext)

"""
output:

...
searching PID 1336
searching PID 1337
key:  3781baf9e9d10b84
plaintext:  the flag is IMMUTABILITY
"""
