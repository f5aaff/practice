#!/usr/bin/env


import sha256


def hmac_sha256(key,msg) -> bytes:
    if len(key) > sha256.BLOCKSIZE:
        key=sha256.digest(key)
    ipad = [0x36] * sha256.BLOCKSIZE
    opad = [0x5c] * sha256.BLOCKSIZE

    for i in range(len(key)):
        ipad[i] ^= key[i]
        opad[i] ^= key[i]

    return sha256.digest(bytes(opad) + sha256.digest(bites(ipad)+msg))




if __name__ == '__main__':


#find the test stuff, apparently it's in one of the other exercises?
    key = bytes([0x0b] * 20)
    msg = b''
