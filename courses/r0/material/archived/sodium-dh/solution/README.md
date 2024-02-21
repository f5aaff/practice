
The point at infinity (the "zero" of elliptic curves) will trigger an
error in Sodium's C function, as it checks whether the result of ECDH is
zero:

```
int
crypto_scalarmult_curve25519(unsigned char *q, const unsigned char *n,
                             const unsigned char *p)
{
    size_t        i;
    unsigned char d = 0;

    if (implementation->mult(q, n, p) != 0) {
        return -1;
    }
    for (i = 0; i < crypto_scalarmult_curve25519_BYTES; i++) {
        d |= q[i];
    }
    return -(1 & ((d - 1) >> 8));
}
```

However, the Rust bindings to Sodium, sodiumoxide, omits to perform
this check, and will return the zero point when it receives a zero
public key.

The following source code sets the public key to the point at infinity
(0100..00, its correct encoding, but the code also works with 00..00):

```
extern crate sodiumoxide;

fn main() {
    sodiumoxide::init();
    let mut pk = [0u8; 32];
    let mut sk = [0u8; 32];
    pk[0]=1;  // as converted to curve25519
    sodiumoxide::randombytes::randombytes_into(&mut sk);
    let p = sodiumoxide::crypto::scalarmult::GroupElement(pk);
    let s = sodiumoxide::crypto::scalarmult::Scalar(sk);
    let h = sodiumoxide::crypto::scalarmult::scalarmult(&s, &p);
    println!("{:?}", pk);
    println!("{:?}", sk);
    println!("{:?}", h);
}
```

We get for example the following results, respectively showing the
public key, private key, and shared secret:

[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0]
[3, 175, 56, 61, 17, 196, 157, 192, 139, 234, 194, 103, 24, 68, 126, 3,
194, 113, 116, 154, 97, 201, 27, 130, 179, 33, 6, 45, 244, 72, 32, 243]
GroupElement([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
