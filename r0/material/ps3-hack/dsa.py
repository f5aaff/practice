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

def print_parameters(dsa):
    print("DSA parameters:")
    print("p:", dsa._key.p) # modulus
    print("q:", dsa._key.q) # subgroup order
    print("g:", dsa._key.g) # generator
    print("y:", dsa._key.y) # public key
    print("x:", dsa._key.x) # private key

if __name__ == '__main__':

    verbose = False

    # Setup DSA signature scheme
    dsa = setup()

    if verbose:
        print_paramters(dsa)

    # Hash message
    m = b"Bioshock"
    h = SHA1.new(m).digest()

    # Create DSA signature
    sig = sign(dsa, h)

    # Verify DSA signature
    if verify(dsa, sig, h):
        print("OK")
    else:
        print("Signature invalid")

