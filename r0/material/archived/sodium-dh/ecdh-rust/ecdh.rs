extern crate sodiumoxide;

fn main() {
    sodiumoxide::init();
    let mut sk = [0u8; 32];

    // EXERCISE TODO: set the public key to a special value...
    // let pk = [ .. ; 32];

    // picks a random secret key
    sodiumoxide::randombytes::randombytes_into(&mut sk);

    // converts public and secret key to the right formats
    let p = sodiumoxide::crypto::scalarmult::GroupElement(pk);
    let s = sodiumoxide::crypto::scalarmult::Scalar(sk);

    // perform the ECDH operation (multiplies point p by number s)
    let h = sodiumoxide::crypto::scalarmult::scalarmult(&s, &p);

    // print everything
    println!("public key: {:?}", pk);
    println!("private key: {:?}", sk);
    println!("shared secret: {:?}", h);
}
