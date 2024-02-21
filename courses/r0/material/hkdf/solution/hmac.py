#!/usr/bin/env python3

import sha256

def hmac_sha256(key: bytes, msg: bytes) -> bytes:
    if len(key) > sha256.BLOCKSIZE:
        key = sha256.digest(key)
    ipad = [0x36] * sha256.BLOCKSIZE
    opad = [0x5c] * sha256.BLOCKSIZE
    for i in range(len(key)): 
        ipad[i] ^= key[i]
        opad[i] ^= key[i]
    return sha256.digest(bytes(opad) + sha256.digest(bytes(ipad) + msg))

if __name__ == '__main__':
    # RFC4231, test case 1
    key = bytes([0x0b] * 20)
    msg = b'Hi There'
    assert('b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7' == sha256.hexdigest(hmac_sha256(key, msg)))

    # RFC4231, test case 2
    key = b'Jefe'
    msg = b'what do ya want for nothing?'
    assert('5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843' == sha256.hexdigest(hmac_sha256(key, msg)))

    # RFC4231, test case 3
    key = bytes([0xaa] * 20)
    msg = bytes([0xdd] * 50)
    assert('773ea91e36800e46854db8ebd09181a72959098b3ef8c122d9635514ced565fe' == sha256.hexdigest(hmac_sha256(key, msg)))

    # RFC4231, test case 4
    key = bytes([i+1 for i in range(25)]) 
    msg = bytes([0xcd] * 50)
    assert('82558a389a443c0ea4cc819899f2083a85f0faa3e578f8077a2e3ff46729665b' == sha256.hexdigest(hmac_sha256(key, msg)))

    # RFC4231, test case 6
    key = bytes([0xaa] * 131)
    msg = b'Test Using Larger Than Block-Size Key - Hash Key First'
    assert('60e431591ee0b67f0d8a26aacbf5b77f8e0bc6213728c5140546040f0ee37f54' == sha256.hexdigest(hmac_sha256(key, msg)))

    # RFC4231, test case 7
    key = bytes([0xaa] * 131)
    msg = b'This is a test using a larger than block-size key and a larger than block-size data. The key needs to be hashed before being used by the HMAC algorithm.'
    assert('9b09ffa71b942fcb27635fbcd5b0e944bfdc63644f0713938a7f51535c3a35e2' == sha256.hexdigest(hmac_sha256(key, msg)))

    print('ok')
