// gcc -lsodium ecdh.c -o ecdh

#include <sodium.h>
#include <string.h>
#include <stdio.h>

int main() {

    // all keys are 32-byte
    unsigned char client_publickey[crypto_box_PUBLICKEYBYTES];
    unsigned char client_secretkey[crypto_box_SECRETKEYBYTES];
    unsigned char server_publickey[crypto_box_PUBLICKEYBYTES];
    unsigned char server_secretkey[crypto_box_SECRETKEYBYTES];
    unsigned char shared_secret[crypto_scalarmult_BYTES];
    int i;

    /* Create client's secret and public keys */
    randombytes_buf(client_secretkey, sizeof client_secretkey);
    crypto_scalarmult_base(client_publickey, client_secretkey);

    /* Create server's secret and public keys */
    randombytes_buf(server_secretkey, sizeof server_secretkey);
    crypto_scalarmult_base(server_publickey, server_secretkey);

    /* EXERCISE TODO: modify server public key to a malicious value */
    // memset(server_publickey, ..., 32);
    // server_publickey[...] = ...;

    /* The client gets a shared secret from its secret key and the server's public key */
    if (crypto_scalarmult(shared_secret, client_secretkey, server_publickey) != 0) {
        fprintf(stderr, "something went wrong\n");
        return 1;
    }
    for(i=0; i<crypto_scalarmult_BYTES; ++i) {
        printf("%02x ", shared_secret[i]);
    }
    printf("\n");

    return 0;
}
