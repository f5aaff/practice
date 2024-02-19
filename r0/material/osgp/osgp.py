#!/usr/bin/env python3

import binascii
import csv
import os

# Crypto functions of the open smart grid protocol 
def ROT8(x, c):
  return ((x%256 << c%8) | (x%256 >> -c%8)) % 256

def OMADigest(m,k):
  a = [0] * 8
  m = m[:] + [0] * (-len(m) % 144)
  for l in range(0, len(m), 144):
    b = m[l:l+144]
    for i in range(18):
      for j in range(7, -1, -1):
        if (k[i%12] >> (7 - j)) & 1:
          a[j] = (a[(j+1)%8] + b[8*i+7-j] + ROT8(~(a[j] + j), 1)) % 256
        else:
          a[j] = (a[(j+1)%8] + b[8*i+7-j] - ROT8(~(a[j] + j), -1)) % 256
  return a

def EN14908(r, m, k):
  mlen, a = len(m) - 1, r[:]
  while True:
    for i in range(6):
      for j in range(7, -1, -1):
        b = 0 if mlen < 0 else m[mlen]
        mlen -= 1
        if k[i] & (1 << (7 - j)):
          a[j] = a[(j+1)%8] + b + ROT8(~(a[j] + j), 1)
        else:
          a[j] = a[(j+1)%8] + b - ROT8(~(a[j] + j), -1)
    if mlen < 0:
      break
  return a

def RC4Encrypt(X,key):
    def RC4(key, b):
      B,S,i,j,l=[],[x for x in range(256)],0,0,len(key)
      while i < 256:
          j = (j + S[i] + key[i%l]) & 0xff
          S[i], S[j] = S[j], S[i]
          i += 1
      i, j = 1, 0
      while b:
          t = S[i]
          j = (j + S[i]) & 0xff
          S[i], S[j] = S[j], S[i]
          B += [S[(S[i]+S[j]) & 0xff]]
          b -= 1
          i = (i + 1) & 0xff
      return B
    S = RC4(key,len(X))
    for i in range(len(X)):
        X[i] ^= S[i]
    return X

def OSGPKeyDerive(k):
  k1 = EN14908([0x81, 0x3f, 0x52, 0x9a, 0x7b, 0xe3, 0x89, 0xba], [], k)
  k2 = EN14908([0x72, 0xb0, 0x91, 0x8d, 0x44, 0x05, 0xaa, 0x57], [], k)
  return k1 + k2

def OSGPEncrypt(m, k):
  k_ = OSGPKeyDerive(k)
  a  = OMADigest(m, k)
  for i in range(8):
    k_[i] ^= a[i]
  return RC4Encrypt(m, k_) + a

def OSGPDecrypt(c, k):
  assert(len(c) >= 8)
  k_ = k_ = OSGPKeyDerive(k)
  a  = c[-8:]
  for i in range(8):
    k_[i] ^= a[i]
  m = RC4Encrypt(c[:-8], k_)
  return OMADigest(m, k) == a, m

# Test vector
m = [0x02,0x02,0x00,0x30,0x00,
     0x03,0x7f,0x30,0xea,0x6d,
     0x00,0x00,0x00,0x0d,0x00,
     0x20,0x98,0x00,0x31,0xc3,
     0x00,0x08,0x00,0x00,0x00,
     0x00,0x00,0x11]
k = [0xDF] * 12
a = [0xdb, 0xe5, 0xcd, 0xe5, 0x07, 0xb1, 0xcb, 0x3d]
assert(OMADigest(m, k) == a)

# Utility functions
def OMABackward(a,m,k,n):
    a, m = a[:], m[:] + [0] * (-len(m) % 144)
    for l in range(n):
        i, j = l // 8, l % 8
        if (k[(17-i)%12] >> (7 - j)) & 1:
            x = ROT8(a[j] - a[(j+1)%8] - m[143-8*i-j], -1)
        else:
            x = ROT8(a[(j+1)%8] + m[143-8*i-j] - a[j], 1)
        a[j] = (~x - j) % 256
    return a

def OMAForward(a,m,k,n):
    a, m = a[:], m[:] + [0] * (-len(m) % 144)
    for l in range(n, 144):
        i, j = l // 8, 7 - l % 8
        if (k[i%12] >> (7 - j)) & 1:
            a[j] = (a[(j+1)%8] + m[8*i+7-j] + ROT8(~(a[j] + j), 1)) % 256
        else:
            a[j] = (a[(j+1)%8] + m[8*i+7-j] - ROT8(~(a[j] + j), -1)) % 256
    return a

def ByteToHex(m):
    return binascii.hexlify(bytearray(m))

def HexToByte(m):
    return list(binascii.unhexlify(m))

def RecoverKey(data):

    # Exercise: 
    #
    # 1. Implement the OSGP key recover function that takes a list of
    # (plaintext,tag) tuples as input. Exploit the fact that the OSGP message
    # authentication code is invertible and exhibits a slow propagation of
    # message differences. The OMAForward and OMABackward functions could be
    # helpful.

    k = [0x00] * 12

    return k

def BreakOSGP():

    # Exercise:
    #
    # 2. Reconstruct the key using the (plaintext,tag) data from 'data.txt' and
    #    the RecoverKey() function.
    # 3. Recover the flag by decrypting the OSGP ciphertext from 'challenge.txt'.

    data = []
    c = []

if __name__ == '__main__':
    BreakOSGP()
