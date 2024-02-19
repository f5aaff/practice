#!/usr/bin/env python3

import sys

n = 21787989770662496702037820206691309819292239152893746553676467506003380283299009054918975247785746750528694203190006394251886451374989240141529597580595378108389948405764933260880341932584794188729833072048646873745635770758479658968071460631971752872722485097316116484844594984187622310173901417409926204057
e = 0x10001

def encrypt_pin(pin):
    if type(pin) != str:
        print('error: expecting a string')
        return
    if len(pin) != 6:
        print('error: invalid PIN length')
        return
    try:
        m = int(pin) 
    except ValueError: 
        print('error: PIN should only contain numerical characters')
        return
    c = pow(m, e, n)
    return c

if __name__ == '__main__':
    try:
        p = sys.argv[1]
    except:
        print('usage: %s pin_code' % sys.argv[0])
        sys.exit(1)
    print(encrypt_pin(p))
