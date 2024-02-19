#!/usr/bin/env python3

import binascii
from Crypto.Hash import SHA1
from Crypto.Math.Numbers import Integer
from Crypto.PublicKey import DSA
from Crypto.Signature import DSS

# DSA signature scheme setup
def setup(key_size=1024):
    key = DSA.generate(key_size)
    dsa = DSS.new(key,'fips-186-3')
    return dsa

# DSA signing
def sign(dsa, msg_hash, k=None):
    if k == None:
        k = dsa._compute_nonce(msg_hash)
    z = Integer.from_bytes(msg_hash[:dsa._order_bytes])
    return list(dsa._key._sign(z, k)) # returns (r,s)

# DSA verification
def verify(dsa, signature, msg_hash):
    z = Integer.from_bytes(msg_hash[:dsa._order_bytes])
    return dsa._key._verify(z, signature)

# Compute t = a^{-1} mod n using the Extended Euclidean Algorithm
def invert(a, n):
    t, new_t = 0, 1
    r, new_r = n, a
    while new_r > 0:
        q = r // new_r
        t, new_t = new_t, t - q * new_t
        r, new_r = new_r, r - q * new_r
    if r > 1:
        raise Exception('Value not invertible')
    if t < 0:
        t = t + n
    return t

def generate_example():

    dsa = setup()

    h = SHA1.new(b"") # dummy message
    k = dsa._compute_nonce(h)

    print_parameters(dsa)

    m1 = b"Portal 2"
    h1 = SHA1.new(m1).digest()
    sig1 = sign(dsa, h1, k)
    r1, s1 = sig1

    print("h1:", int(binascii.hexlify(h1),16))
    print("sig1:", sig1)

    m2 = b"Minecraft"
    h2 = SHA1.new(m2).digest()
    sig2 = sign(dsa, h2, k)
    r2, s2 = sig2

    print("h2:", int(binascii.hexlify(h2),16))
    print("sig2:", sig2)

    # Shortcuts
    q = dsa._key.q
    p = dsa._key.p
    g = dsa._key.g
    y = dsa._key.y

    # Recover randomness k
    t = (s1 - s2) % q
    z = invert(t, q)
    lh1 = int(binascii.hexlify(h1), 16)
    lh2 = int(binascii.hexlify(h2), 16)
    k_rec = ((lh1 - lh2) * z) % q

    # Recover private keys
    x1 = (((s1 * k_rec) - lh1) * invert(r1, q)) % q
    x2 = (((s2 * k_rec) - lh2) * invert(r2, q)) % q

    # Verify recovered key
    y1 = pow(g, x1, p)
    y2 = pow(g, x2, p)

    print(y1 == y2 == y)

if __name__ == '__main__':

    #generate_example()

    p = 129570736374393280360874421749656618648472895056230507103725664902467039685265288356788849348109094493485563726402962659349904985061333051347927584106018898162627556951694292795222312739690798359920737769722657952741803795552012039797121453510564475423572772582236910544520714904123340454784221062180709970371
    q = 1049360825264211318919220172670632636101903709629
    g = 115271934155295135967017909883784743167921300687769147296561968554660095228818489111498338589055264694190233000831197774939357720436009350571413008316803869484747366634215788435542329479130266563635296047274272220155181263794719961032703028461664072190159357343034020368421893402721143616035668517846131507129
    y = 121258457743941400017236408162630895783227751147611045135427815590252004983819844481736214426794666857474074374577049730922004542469318392991434398700397904454512515188311373104852172276087658951677054863935090862409801461444587938565672574556260754384066265473847790319862679840743747348694368093320301550883
    h1 = 342333396831744928439207551062789552955421505219
    sig1 = (51548221150354323901248948200600122077764868202, 1006447649006919706259415719640254162540733497225)
    h2 = 1377325407270520690954972820750612362610474480861
    sig2 = (51548221150354323901248948200600122077764868202, 662361006561249566325910578250119038019330726281)

    r1 = sig1[0]
    s1 = sig1[1]
    r2 = sig2[0]
    s2 = sig2[1]

    # Recover randomness k
    t = (s1 - s2) % q
    z = invert(t, q)
    k_rec = ((h1 - h2) * z) % q

    # Recover private key x
    x_rec = (((s1 * k_rec) - h1) * invert(r1, q)) % q
    
    # Verify x
    y_rec = pow(g, x_rec, p)

    if y == y_rec:
            print('ok')
    else:
            print('recovery failed')
