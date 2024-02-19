#!/usr/bin/env python3

"""
The key here is to notice that the nonce d99795161dc142b732e6eb7785090742 of our
challenge ciphertext was already used to encrypt a message from the logs:

$ grep d99795161dc142b732e6eb7785090742 encrypted.log
d99795161dc142b732e6eb7785090742;b16c8dffb5e4fe9890eb387850f23c2e78c277c4347d2e3e8a25c76a6d3930ee76da35138a48376ae76a5cc63826c173d8bbeb561545f74d1e43f9127a272e96e0681abbfa950dee30;Geometric Constructions Game with Straightedge and Compass (euclidea.xyz);

Since the same nonce was used, the same keystream was used to encrypt
both messages. That is, the same value was XORed to the two plaintexts.
To decrypt our ciphertext, we can therefore:
1. XOR the know plaintext and ciphertext from the logs to get the keystream.
2. XOR this keystream to our ciphertext.

That's exactly what the program below is doing. (Note that in the logs,
ciphertexts appear encoded in hexadecimal, while plaintexts appear as
raw ASCII text):
"""

import binascii

def xor(s1,s2):
    return ''.join(chr(a ^ ord(b)) for a,b in zip(s1,s2))

known_ciphertext = 'b16c8dffb5e4fe9890eb387850f23c2e78c277c4347d2e3e8a25c76a6d3930ee76da35138a48376ae76a5cc63826c173d8bbeb561545f74d1e43f9127a272e96e0681abbfa950dee30'
known_plaintext = 'Geometric Constructions Game with Straightedge and Compass (euclidea.xyz)'

target_ciphertext = 'b84cb4d782b0deb4a38e3a431ecf07124ee4508d125d7d5d99168a42020a1cba51a8462eb6091f2ddc4a6be71e0ec151ff8f83502809'

def main(): 
    keystream = xor(binascii.unhexlify(known_ciphertext), known_plaintext)
    plaintext = xor(binascii.unhexlify(target_ciphertext), keystream)
    print(plaintext)

if __name__ == '__main__':
    main()

# The program should print "NEVER REPEAT NONCES IN CTR MODE OR IN A STREAM CIPHER!"

# PS: key was dc680fb244deea37efa5811d1d2efc57
