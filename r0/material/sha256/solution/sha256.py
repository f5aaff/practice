#!/usr/bin/env python3

BLOCKSIZE = 64
DIGESTSIZE = 32

# SHA-256 round constants
k = [0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
     0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
     0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
     0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
     0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
     0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
     0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
     0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
     0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
     0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
     0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
     0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
     0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
     0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
     0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
     0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2]

ROR = lambda x, y: (((x & 0xffffffff) >> (y & 31)) | (x << (32 - (y & 31)))) & 0xffffffff
Ch = lambda x, y, z: (z ^ (x & (y ^ z)))
Maj = lambda x, y, z: (((x | y) & z) | (x & y))
S = lambda x, n: ROR(x, n)
R = lambda x, n: (x & 0xffffffff) >> n
Sigma0 = lambda x: (S(x, 2) ^ S(x, 13) ^ S(x, 22)) # BUG1: replaced constant 13 with 17
Sigma1 = lambda x: (S(x, 6) ^ S(x, 11) ^ S(x, 25))
Gamma0 = lambda x: (S(x, 7) ^ S(x, 18) ^ R(x, 3))
Gamma1 = lambda x: (S(x, 17) ^ S(x, 19) ^ R(x, 10))

def init():
    return {
        'datalen': 0, # data length in bytes
        'bitlen': 0, # data length in bits
        'data': [0x00] * BLOCKSIZE, # current 64-byte data block
        'state': [0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                  0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19] # internal state
    }

def transform(state: list, data: bytes) -> list:
    w = [0] * BLOCKSIZE

    for i in range(0,16):
        w[i] = (data[4*i]<<24) + (data[4*i+1]<<16) + (data[4*i+2]<<8) + data[4*i+3]
    
    for i in range(16,64):
        w[i] = (Gamma1(w[i-2]) + w[i-7] + Gamma0(w[i-15]) + w[i-16]) & 0xffffffff 

    a = state[0] 
    b = state[1]  
    c = state[2] 
    d = state[3] 
    e = state[4]
    f = state[5]
    g = state[6]
    h = state[7]

    for i in range(0,64):
        t0 = h + Sigma1(e) + Ch(e, f, g) + k[i] + w[i]
        t1 = Sigma0(a) + Maj(a, b, c) 
        h = g
        g = f
        f = e
        e = (d + t0) & 0xffffffff
        d = c
        c = b
        b = a
        a = (t0 + t1) & 0xffffffff

    state[0] = (state[0] + a) & 0xffffffff
    state[1] = (state[1] + b) & 0xffffffff
    state[2] = (state[2] + c) & 0xffffffff
    state[3] = (state[3] + d) & 0xffffffff
    state[4] = (state[4] + e) & 0xffffffff
    state[5] = (state[5] + f) & 0xffffffff
    state[6] = (state[6] + g) & 0xffffffff
    state[7] = (state[7] + h) & 0xffffffff

    return state

def update(ctx: dict, data: bytes):
    # process data in chunks of 64 byte
    for i in range(len(data)):
        ctx['data'][ctx['datalen']] = data[i] # BUG2: zeroing data
        ctx['datalen'] += 1
        if ctx['datalen'] == BLOCKSIZE:
            ctx['state'] = transform(ctx['state'], ctx['data'])
            ctx['bitlen'] += 512
            ctx['datalen'] = 0

def final(ctx: dict) -> bytes:
    # process last block of less than 64 bytes
    i = ctx['datalen']

    if ctx['datalen'] < 56:
        # if the last block is less than 56 bytes, add padding directly
        ctx['data'][i] = 0x80
        i += 1
        while i < 56:
          ctx['data'][i] = 0x00
          i += 1
    else:
        # if the last block is larger than 56 bytes, add another full block for padding
        ctx['data'][i] = 0x80 # BUG3: wrong constant used, 0x88 instead of 0x80
        i += 1
        while i < 64:
          ctx['data'][i] = 0x00
          i += 1

        ctx['state'] = transform(ctx['state'], ctx['data'])
        for i in range(56):
            ctx['data'][i] = 0x00

    # store the data length in bits in the last 8 bytes of the expanded block
    ctx['bitlen'] += ctx['datalen'] * 8
    ctx['data'][63] = (ctx['bitlen'] >>  0) & 0xff
    ctx['data'][62] = (ctx['bitlen'] >>  8) & 0xff
    ctx['data'][61] = (ctx['bitlen'] >> 16) & 0xff
    ctx['data'][60] = (ctx['bitlen'] >> 24) & 0xff
    ctx['data'][59] = (ctx['bitlen'] >> 32) & 0xff
    ctx['data'][58] = (ctx['bitlen'] >> 40) & 0xff
    ctx['data'][57] = (ctx['bitlen'] >> 48) & 0xff
    ctx['data'][56] = (ctx['bitlen'] >> 56) & 0xff

    # finalize
    ctx['state'] = transform(ctx['state'], ctx['data'])

    h = [0x00] * DIGESTSIZE 
    for i in range(4):
        h[i]      = (ctx['state'][0] >> (24 - i * 8)) & 0xff
        h[i + 4]  = (ctx['state'][1] >> (24 - i * 8)) & 0xff
        h[i + 8]  = (ctx['state'][2] >> (24 - i * 8)) & 0xff
        h[i + 12] = (ctx['state'][3] >> (24 - i * 8)) & 0xff
        h[i + 16] = (ctx['state'][4] >> (24 - i * 8)) & 0xff
        h[i + 20] = (ctx['state'][5] >> (24 - i * 8)) & 0xff
        h[i + 24] = (ctx['state'][6] >> (24 - i * 8)) & 0xff
        h[i + 28] = (ctx['state'][7] >> (24 - i * 8)) & 0xff

    return bytes(h)

def digest(msg: bytes) -> bytes:
    ctx = init()
    update(ctx, msg)
    return final(ctx)

def hexdigest(digest: bytes) -> str:
    return ''.join(['%.2x' % i for i in digest])

if __name__ == '__main__':
    # message of size 0 bits
    msg = b''
    assert('e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855' == hexdigest(digest(msg)))

    # message of size 24 bits
    msg = b'abc'
    assert('ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad' == hexdigest(digest(msg)))

    # message of size 448 bits
    msg = b'abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq' 
    assert('248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1' == hexdigest(digest(msg)))

    # message of size 896 bits
    msg = b'abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu'
    assert('cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1' == hexdigest(digest(msg)))

    print('ok')
