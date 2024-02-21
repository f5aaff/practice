#!/usr/bin/env python3

import os
import sys
import binascii

from Crypto.Cipher import AES
import Crypto.Util.Counter

nonce = 'd99795161dc142b732e6eb7785090742'

# Encrypts a given plaintext with the given key and nonce using AES-CTR. Expects key and
# plaintext as a raw byte strings.
def encrypt(key, nonce, plaintext):
    ctr = Crypto.Util.Counter.new(128, initial_value=int(nonce, 16))
    aes = AES.new(key, AES.MODE_CTR, counter=ctr)
    return aes.encrypt(plaintext)

if __name__ == '__main__':
    # Example:
    key = binascii.unhexlify('aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa')
    plaintext = b'Today we learn how not to use AES-CTR'
    ciphertext = encrypt(key, nonce, plaintext)
    print(binascii.hexlify(ciphertext))
    plaintext_decrypted = encrypt(key, nonce, ciphertext)
    print(plaintext_decrypted)
