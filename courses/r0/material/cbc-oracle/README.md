# CBCoracle

This exercise is a simplified variant of the famous padding oracle
attack.

The program CBCoracle will encrypt or decrypt a message using AES in CBC
mode, given an IV, and with a hardcoded key. For example, the following
command encrypts the 23-byte hex string "aaaa...aa" using the all-zero
IV:

$ ./CBCoracle e 00000000000000000000000000000000 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
5597b93a63947b072e67ee2454148547ac28008edd1f5fcf65ec2d6d0a0a9e8f

Note the first argument "e", to tell the program that we want to
encrypt. To decrypt the above ciphertext, replace "e" with "d" and
provide the ciphertext in addition to the IV:

$ ./CBCoracle d 00000000000000000000000000000000 5597b93a63947b072e67ee2454148547ac28008edd1f5fcf65ec2d6d0a0a9e8f
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

Note that CBCoracle implements PKCS7 padding, and decryption checks that
the padding is valid in the message obtained. For example, if we replace
the final "f" in the above ciphertext with a "c", the padding will be
invalid:

$ ./encrypt d 00000000000000000000000000000000 5597b93a63947b072e67ee2454148547ac28008edd1f5fcf65ec2d6d0a0a9e8c
INVALID PADDING

Your goal is to use the CBC oracle to decrypt the following encrypted
block:
8f5fc4678ae5de69cc987d0c1207acbe

Good luck!
