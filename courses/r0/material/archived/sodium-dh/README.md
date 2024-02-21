# Sodium elliptic-curve Diffie-Hellman

The file ecdh.c implements an elliptic-curve Diffie-Hellman (ECDH) key
agreement using the Sodium C library. What can go wrong if the return
value of `crypto_scalarmult()` is not checked?

Hint: find the public key value that always gives the same shared
secret, regardless of the private key's value

Then, test whether the Rust bindings for Sodium (sodiumoxide) is
made vulnerable because of this... (see the source file ecdh.rs in the
ecdh-rust/ directory, executed by doing `cargo run`).
