#!/usr/bin/env python3 

import binascii
import csv
import os
from osgp import *

m = map(ord, os.urandom(144))
k = map(ord, os.urandom(12))
a = OMADigest(m, k)
assert( OMAForward([0]*8, m, k, 0) == OMADigest(m,k) )
assert( OMAForward(OMABackward(a,m,k,8),m,k,144-8) == a )

def TagGenOracle(m,init=[True]):
    if init[0]:
      print '[ORACLE] k = ' + str(k)
      init[0] = False
    return OMADigest(m,k)

def GenerateChallenge():
    data = []
    m_ = m[:]
    a_ = TagGenOracle(m_)
    data.append((m_,a_))
    for i in range(12):
        m_ = m[:]
        m_[128-8*i:] = map(ord, os.urandom(144-(128-8*i)))
        a_ = TagGenOracle(m_)
        data.append((m_,a_))
    if k == RecoverKey(data): # check that the key can actually be recovered (it fails sometimes)
        with open('data.txt', 'wb') as f:
            for d in data:
                f.write("{},{}\n".format(ByteToHex(d[0]),ByteToHex(d[1])))
            f.close()
        flag = map(ord,"Congratulations, you broke OSGP! For more attacks on OSGP see https://ia.cr/2015/428.")
        with open('challenge.txt', 'wb') as f:
            c = OSGPEncrypt(flag, k)
            f.write("{}\n".format(ByteToHex(c)))
            f.close()
    else:
        print("error, key not recoverable")

if __name__ == '__main__':
    GenerateChallenge()
