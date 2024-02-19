#!/usr/bin/env python3

import sys

n = 21787989770662496702037820206691309819292239152893746553676467506003380283299009054918975247785746750528694203190006394251886451374989240141529597580595378108389948405764933260880341932584794188729833072048646873745635770758479658968071460631971752872722485097316116484844594984187622310173901417409926204057
e = 0x10001
c = 7549162677747403096697675831128185199715456195701331870042620647295072520953007657208852935404062528303685706001581155926015824988937325246499512536666413018214587674066585166432231723728499332483862990693622686460629107873319691206360055223195249658396915429728661962987885106023391755536525737667080345652

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
    
"""
    We know from encrypt_pin() that the function takes a 6-digit PIN
    that contains only decimal numbers. There are only 10^6 such
    possible values, or about 2^20, which is small enough to bruteforce :)
"""
def solve():
    for pin in range(1000000):
        print(pin)
        p = str(pin)
        # add zeros if needed to get a 6-digit PIN
        p = '0'*(6-len(p)) + p
        cc = encrypt_pin(p)
        if cc == c:
            print('PIN FOUND: ', pin)
            return

if __name__ == '__main__':
    solve()
